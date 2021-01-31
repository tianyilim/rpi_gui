#include "gui_help.hpp"

int main (){
    char const *fbpath = "/dev/fb1";    // string-to-char* conversion requrires this
    fb_display mydisplay(fbpath);

    // get info about screen parameters in main()
    uint32_t screenx = mydisplay.get_framex();
    uint32_t screeny = mydisplay.get_framey();

    // uint16_t r, g, b;   // stuff was overflowing before...
    mydisplay.clear_screen();
    // split screen into 4
    // upp left
    mydisplay.draw_rectangle(0, 0, screenx/2, screeny/2, 0, 0, 0xFF);                   // Blue
    // upp right
    mydisplay.draw_rectangle(screenx/2, 0, screenx/2, screeny/2, 0, 0xFF, 0);           // Green
    // lower left
    mydisplay.draw_rectangle(0, screeny/2, screenx/2, screeny/2, 0xFF, 0, 0);           // Red
    // lower right
    mydisplay.draw_rectangle(screenx/2, screeny/2, screenx/2, screeny/2, 0xFF, 0, 0xFF);    // Purple

    sleep(3);   // shows what happens

    return 0;
}