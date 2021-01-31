## Raspberry Pi Graphics class

This repo contains a C++ class wrapping a low-level memory-mapped graphics driver. The contents are taken from the tutorial in http://raspberrycompote.blogspot.com/2012/12/low-level-graphics-on-raspberry-pi-part_9509.html, but wrapped up into a class.

(please don't stone me for mixing C code with C++ objects!)

The aim is to be able to control the display on an RPi without needing to install the overhead of a full desktop environment.

In progress:
- adding primitive drawing functions (rectangles, circles) 
- adding geometry (lines, fill)
- adding settings for changing the color depth of the display
- better error handling

With the due course of time, the hope is to be able to create a lightweight headless calendar app that syncs off Google Calendar and is able to display a live schedule somewhere in the home.