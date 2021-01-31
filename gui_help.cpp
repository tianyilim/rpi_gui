#include "gui_help.hpp"

fb_display::fb_display(const char* path){
    fb_path = path;
    fbfd = open(path, O_RDWR);
    if (fbfd == -1) {
        fprintf(stderr,"Error: cannot open framebuffer device.\n");
        throw;
        // make it return some value
    } else {
        fprintf(stderr, "The framebuffer device opened.\n");

        // Get variable screen information
        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info)) {
            fprintf(stderr, "Error reading variable screen info.\n");
            throw;
        }
        // Get fixed screen information
        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info)) {
            fprintf(stderr, "Error reading fixed screen information.\n");
            throw;
        }

        // Store for reset (copy vinfo to vinfo_orig)
        memcpy(&orig_vinfo, &var_info, sizeof(struct fb_var_screeninfo));

        // var_info.bits_per_pixel = 8; 
        // this didn't work somehow so just work in 16bpp for now

        // if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &var_info)) {
        //     fprintf(stderr, "Error setting variable information.\n");
        //     // reset to original before throwing!
        //     ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo);
        //     throw;
        // }

        fprintf(stderr, "Display info %dx%d, %d bpp\n",
            var_info.xres, var_info.yres,
            var_info.bits_per_pixel );

        // map framebuffer to user memory 
        screensize = fix_info.smem_len;
        fprintf(stderr, "screensize is %ld\n", screensize);

        fbp = (char*)mmap(0, screensize, 
                    PROT_READ | PROT_WRITE, 
                    MAP_SHARED, 
                    fbfd, 0);

        if ((int)fbp == -1) {
            fprintf(stderr, "Failed to mmap.\n");
            throw;
        }
    }
}

fb_display::~fb_display(){
    munmap(fbp, screensize);
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo)) {
        fprintf(stderr, "Error re-setting variable information.\n");
    }
    close(fbfd);
    fprintf(stderr, "fb_display instance destroyed\n");
}

uint32_t fb_display::get_framex(){
    return var_info.xres;
}
uint32_t fb_display::get_framey(){
    return var_info.yres;
}
uint32_t fb_display::get_framebpp(){
    return var_info.bits_per_pixel;
}

void fb_display::draw_rectangle(uint32_t startx, uint32_t starty, 
                uint32_t width, uint32_t height, 
                uint8_t red, uint8_t green, uint8_t blue)
{
    unsigned int x, y;
    unsigned int pix_offset;

    // if it overflows to more than allocated, then too bad.
    unsigned int endx = (startx+width < var_info.xres) ? startx+width : var_info.xres;
    unsigned int endy = (starty+height < var_info.yres) ? starty+height : var_info.yres;

    for (y=starty; y < endy; y++) {
        for (x = startx; x < endx; x++) {
        // calculate the pixel's byte offset inside the buffer
        pix_offset = (2*x) + y * fix_info.line_length;

        // Assign color value to pixels; 5-6-5 method
        // first = {red[4:0]; green[5:3]}
        // second = {green[2:0]; blue[4:0]}
        uint8_t first, second;
        first = red << 3 | green >> 3;
        second = (green & 0x08) << 5 | blue;

        *((char*)(fbp + pix_offset)) = first;
        *((char*)(fbp + pix_offset + 1)) = second;

        }
    }

    return;
}