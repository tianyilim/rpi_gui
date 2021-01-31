#include "gui_help.hpp"

int main (){
    char const *fbpath = "/dev/fb1";    // string-to-char* conversion requrires this
    fb_display mydisplay(fbpath);

    // get info about screen parameters in main()
    uint32_t screenx = mydisplay.get_framex();
    uint32_t screeny = mydisplay.get_framey();

    // split screen into 4
    // upp left
    mydisplay.draw_rectangle(0, 0, screenx/2, screeny/2, 0, 0, 0b11111);
    // upp right
    mydisplay.draw_rectangle(screenx/2, 0, screenx/2, screeny/2, 0, 0b1111111, 0);
    // lower left
    mydisplay.draw_rectangle(0, screeny/2, screenx/2, screeny/2, 0b11111, 0, 0);
    // lower right
    mydisplay.draw_rectangle(screenx/2, screeny/2, screenx/2, screeny/2, 0b11111, 0b111111, 0b11111);

    sleep(5);

    return 0;
}