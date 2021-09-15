// based on GxEPD2_213_mono_partialRefresh_huzzah32_osc_sd_6
// Library: https://github.com/ZinggJM/GxEPD2
// see GxEPD2_wiring_examples.h for wiring suggestions and examples

// Stephan Schulz Sept 2021
// meant to be used with Adafruit Huzzah32 not Huzzah8266
// here some tests towards partially refreshing the ePaper display
// https://github.com/antimodular/ePaper_displays


//---------------ePaper display-----------
#include <GxEPD2_3C.h>
#include <GxEPD2_BW.h>

// or select the display class and display driver class in the following file
// (new style):
#include "GxEPD2_display_selection_new_style.h"

//-----------sd card-----------
// #include "FS.h"
// #include "SdFat.h"
#include "SPI.h"
#include "SdFat.h"
#include "sdios.h"
SdFat SD;

bool bSD_card_present = false;
bool SD_card_readSuccess = false;
unsigned long sdCard_timer;

//-------general----
String current_text = "";
String new_text = "Anfang";
String old_text = "";

unsigned long lastTextTimer = 0;
bool isFirst = true;

bool isBlackOnWhite = true;

unsigned long blinkTimer;
int LED_red = 13;
bool LED_RED_STATE = false;
// int LED_blue = 2;
// bool LED_BLUE_STATE = false;

int fontIndex = 0;

int updateDuration = 3000;
int rotation90_index = 3;

void setup() {
  int baudrate = 115200;
  Serial.begin(baudrate);  // since display.init also used 115200 let's never
  // chaange Serial.begin(115200) baudrate, otherwise
  // serial monitor prints garbage
  Serial.println();

  //-----sd card
  sdCard_setup();
  SD_card_readSuccess = false;

  delay(1000);


  pinMode(LED_red, OUTPUT);
  // pinMode(LED_blue, OUTPUT);
  digitalWrite(LED_red, HIGH);  //on ESP32 LOW == off
  // digitalWrite(LED_blue, LOW);


  setup_ePaper(baudrate);

  lastTextTimer = millis();

  digitalWrite(LED_red, LOW);
}


void loop() {

  if (millis() - lastTextTimer > updateDuration) {
    //    clock_test();

    if (bSD_card_present == true) {
      int temp_r = random(9999); //my text file has 10k lines
      Serial.println("**********************");
      Serial.print("pick random SDCARD line: ");
      Serial.print(temp_r);
      Serial.println();
      new_text = readOneLineFromFile("myFile.txt", temp_r);
      if (new_text == "FAILED!") {
        SD_card_readSuccess = false;
      } else {
        SD_card_readSuccess = true;
      }
    }

    Serial.print(bSD_card_present);
    Serial.print(", ");
    Serial.print(SD_card_readSuccess);
    Serial.println();

  }

  if (current_text != new_text) {
    current_text = new_text;
    lastTextTimer = millis();

    update_ePaper();

    display.powerOff();
  }


  if (bSD_card_present == false && millis() - sdCard_timer > 10000) {
    // SD.end();
    sdCard_setup();
    sdCard_timer = millis();
  }

}
