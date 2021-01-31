#include "gui_help.hpp"

int main (){
    char const *fbpath = "/dev/fb1";    // string-to-char* conversion requrires this
    fb_display mydisplay(fbpath);

    // get info about screen parameters in main()
    uint32_t screenx = mydisplay.get_framex();
    uint32_t screeny = mydisplay.get_framey();

    // mydisplay.clear_screen();
    // // split screen into 4
    // // upp left
    // mydisplay.draw_rectangle(0, 0, screenx/2, screeny/2, 0, 0, 0xFF);                   // Blue
    // // upp right
    // mydisplay.draw_rectangle(screenx/2, 0, screenx/2, screeny/2, 0, 0xFF, 0);           // Green
    // // lower left
    // mydisplay.draw_rectangle(0, screeny/2, screenx/2, screeny/2, 0xFF, 0, 0);           // Red
    // // lower right
    // mydisplay.draw_rectangle(screenx/2, screeny/2, screenx/2, screeny/2, 0xFF, 0, 0xFF);    // Purple

    // colorful fullscreen display
    // avoid screen tearing?
    uint32_t i, j, k;
    for(k=0; k<255; k+=8){
    
        for(i=0; i<screenx; i++){
            for(j=0; j<screeny; j++){
                // Scale
                uint8_t curr_red, curr_green;
                curr_red = (i << 8) / screenx;    // red changes with screenx (rightmost=reddest)
                curr_green = (j << 8) / screeny;  // green changes with screeny (bottom=greenest)
                mydisplay.draw_pixel(i, j, curr_red, curr_green, k);
            }
        }
    
        usleep(100000); // 100ms
    }

    // sleep(3);   // shows what happens

    return 0;
}