#ifndef GUI_HELP_H
#define GUI_HELP_H

#include <unistd.h>
#include <stdint.h> // for uint32_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


/*  Defines a display class that allows for easier read/write actions
    based on the excellent tutorial series at 
    http://raspberrycompote.blogspot.com/2012/12/low-level-graphics-on-raspberry-pi-part_9509.html

    Assumes, so far, that the bpp value of the screen is 16 (color palette used)
*/

class fb_display{
    private:
        const char* fb_path;  // which framebuffer to output to?
        int fbfd; // framebuffer file descriptor
        struct fb_var_screeninfo orig_vinfo;    // to restore screen info on destruct
        struct fb_var_screeninfo var_info;      // variable screen info
        struct fb_fix_screeninfo fix_info;      // fixed screen info

        long int screensize = 0;
        char* fbp = 0;  // framebuffer pointer

    public:
        // Constructor opens up the framebuffer
        fb_display(const char* path);

        // Destructor
        ~fb_display();

        uint32_t get_framex();
        uint32_t get_framey();
        uint32_t get_framebpp();

        // Draw a pixel at specified (x,y); 16 bit color depth.
        // draw pixel is small, made inline; should be faster...
        void draw_pixel(uint32_t x, uint32_t y, 
                        uint8_t red, uint8_t green, uint8_t blue);

        // Draw a rectangle of specified area and color
        // use memset for this? :P
        void draw_rectangle(uint32_t startx, uint32_t starty, 
                            uint32_t height, uint32_t width, 
                            uint8_t red, uint8_t green, uint8_t blue);

        // memset the whole screen to be black.
        void clear_screen();

        // memset the whole screen to be <COLOR>
        void fill_screen(uint8_t red, uint8_t green, uint8_t blue);

        void draw_circle();
        void draw_line();
        void draw_fill();

};

#endif