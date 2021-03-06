// Display Library example for SPI e-paper panels from Dalian Good Display and boards from Waveshare.
// Requires HW SPI and Adafruit_GFX. Caution: the e-paper panels require 3.3V supply AND data lines!
//
// Display Library based on Demo Example from Good Display: http://www.e-paper-display.com/download_list/downloadcategoryid=34&isMode=false.html
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2

// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
// Good Display ePaper for Arduino: https://forum.arduino.cc/index.php?topic=436411.0

// select the display class (only one), matching the kind of display panel
#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
//#define GxEPD2_DISPLAY_CLASS GxEPD2_3C
//#define GxEPD2_DISPLAY_CLASS GxEPD2_7C

// select the display driver class (only one) for your  panel
//#define GxEPD2_DRIVER_CLASS GxEPD2_154     // GDEP015OC1  200x200, no longer available
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_D67 // GDEH0154D67 200x200
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_T8  // GDEW0154T8  152x152
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_M09 // GDEW0154M09 200x200
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_M10 // GDEW0154M10 152x152
//#define GxEPD2_DRIVER_CLASS GxEPD2_213     // GDE0213B1   128x250, phased out
//#define GxEPD2_DRIVER_CLASS GxEPD2_213_B72 // GDEH0213B72 128x250
#define GxEPD2_DRIVER_CLASS GxEPD2_213_B74 // GDEH0213B73 128x250
//#define GxEPD2_DRIVER_CLASS GxEPD2_213_flex // GDEW0213I5F 128x250
//#define GxEPD2_DRIVER_CLASS GxEPD2_213_M21 // GDEW0213M21 128x250
//#define GxEPD2_DRIVER_CLASS GxEPD2_290     // GDEH029A1   128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_290_T5  // GDEW029T5   128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_290_T94 // GDEM029T94  128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_290_M06 // GDEW029M06  128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_260     // GDEW026T0   152x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_260_M01 // GDEW026M01  152x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_270     // GDEW027W3   176x264
//#define GxEPD2_DRIVER_CLASS GxEPD2_371     // GDEW0371W7  240x416
//#define GxEPD2_DRIVER_CLASS GxEPD2_420     // GDEW042T2   400x300
//#define GxEPD2_DRIVER_CLASS GxEPD2_420_M01 // GDEW042M01  400x300
//#define GxEPD2_DRIVER_CLASS GxEPD2_583     // GDEW0583T7  600x448
//#define GxEPD2_DRIVER_CLASS GxEPD2_583_T8  // GDEW0583T8  648x480
//#define GxEPD2_DRIVER_CLASS GxEPD2_750     // GDEW075T8   640x384
//#define GxEPD2_DRIVER_CLASS GxEPD2_750_T7  // GDEW075T7   800x480
// 3-color e-papers
//#define GxEPD2_DRIVER_CLASS GxEPD2_154c     // GDEW0154Z04 200x200, no longer available
//#define GxEPD2_DRIVER_CLASS GxEPD2_154_Z90c // GDEH0154Z90 200x200
//#define GxEPD2_DRIVER_CLASS GxEPD2_213c     // GDEW0213Z16 104x212
//#define GxEPD2_DRIVER_CLASS GxEPD2_290c     // GDEW029Z10  128x296
//#define GxEPD2_DRIVER_CLASS GxEPD2_270c     // GDEW027C44  176x264
//#define GxEPD2_DRIVER_CLASS GxEPD2_420c     // GDEW042Z15  400x300
//#define GxEPD2_DRIVER_CLASS GxEPD2_583c     // GDEW0583Z21 600x448
//#define GxEPD2_DRIVER_CLASS GxEPD2_750c     // GDEW075Z09  600x384
//#define GxEPD2_DRIVER_CLASS GxEPD2_750c_Z08 // GDEW075Z08  800x480
//#define GxEPD2_DRIVER_CLASS GxEPD2_750c_Z90 // GDEH075Z90  880x528
//#define GxEPD2_DRIVER_CLASS GxEPD2_1248     // GDEW1248T3  1303x984
// 7-color e-paper
//#define GxEPD2_DRIVER_CLASS GxEPD2_565c // Waveshare 5.65" 7-color (3C graphics)
// grey levels parallel IF e-papers on Waveshare e-Paper IT8951 Driver HAT
//#define GxEPD2_DRIVER_CLASS GxEPD2_it60           // ED060SCT 800x600
//#define GxEPD2_DRIVER_CLASS GxEPD2_it60_1448x1072 // ED060KC1 1448x1072

// SS is usually used for CS. define here for easy change
#ifndef EPD_CS
#define EPD_CS SS
#endif

#if defined(GxEPD2_DISPLAY_CLASS) && defined(GxEPD2_DRIVER_CLASS)




#if defined(ARDUINO_ARCH_SAMD)
#define MAX_DISPLAY_BUFFER_SIZE 15000ul // ~15k is a good compromise
#if GxEPD2_DISPLAY_CLASS == GxEPD2_BW
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
#elif GxEPD2_DISPLAY_CLASS == GxEPD2_3C
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
#elif GxEPD2_DISPLAY_CLASS == GxEPD2_7C
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2))
#endif
// adapt the constructor parameters to your wiring
//GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=4*/ 4, /*DC=*/ 7, /*RST=*/ 6, /*BUSY=*/ 5));
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=4*/ 9, /*DC=*/ 10, /*RST=*/ -1, /*BUSY=*/ -1));
#endif

#endif
