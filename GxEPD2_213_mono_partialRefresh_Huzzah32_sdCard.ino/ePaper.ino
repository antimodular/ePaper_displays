//------FONTS--------------
#include "fonts/URW_Palladio_L_Roman_29.h"
#include "fonts/URW_Palladio_L_Roman_49.h"
#include "fonts/URW_Palladio_L_Roman_69.h"


void setup_ePaper(int _baudrate) {
  display.init(_baudrate);

  full_white();
  delay(500);
}

void drawWord_ePaper(String _word, bool _inverted) {

  static int16_t bbx = 400;
  static int16_t bby = 300;
  static uint16_t bbw = 0;
  static uint16_t bbh = 0;
  Serial.println("-------------------");
  Serial.print("draw(): word ");
  Serial.print(_word);
  Serial.println();

  Serial.print("display res: ");
  Serial.print(display.width());
  Serial.print(" * ");
  Serial.print(display.height());
  Serial.println();

  Serial.print("display.epd2 res: ");
  Serial.print(display.epd2.WIDTH);
  Serial.print(" * ");
  Serial.print(display.epd2.HEIGHT);
  Serial.println();

  //------show old text in white in order to erase it from screen
  display.setRotation(rotation90_index);

  display.setFont(&URW_Palladio_L_Roman_49);

  if (_inverted == true) {
    if (isBlackOnWhite == true) {
      display.setTextColor(GxEPD_WHITE);
    } else {
      display.setTextColor(GxEPD_BLACK);
    }
  } else {
    if (isBlackOnWhite == true) {
      display.setTextColor(GxEPD_BLACK);
    } else {
      display.setTextColor(GxEPD_WHITE);
    }
  }
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(_word, 0, 0, &tbx, &tby, &tbw, &tbh);

  Serial.print("getTextBounds ");
  Serial.print(tbw);
  Serial.print(", ");
  Serial.println(tbh);

  if (tbh >= 90) {
    display.setFont(&URW_Palladio_L_Roman_29);
    display.getTextBounds(_word, 0, 0, &tbx, &tby, &tbw, &tbh);
  } else if (tbw <= 140) {
    display.setFont(&URW_Palladio_L_Roman_69);
    display.getTextBounds(_word, 0, 0, &tbx, &tby, &tbw, &tbh);
  }

  Serial.print("getTextBounds ");
  Serial.print(tbw);
  Serial.print(", ");
  Serial.println(tbh);

  // place the bounding box, cover any previous ones
  int16_t tx = max(0, ((display.width() - tbw) / 2));
  int16_t ty = max(0, ((display.height() - tbh) / 2));
  bbx = min(bbx, tx);
  bby = min(bby, ty);
  bbw = max(bbw, tbw);
  bbh = max(bbh, tbh);

  //  if (bbw >= 250) {
  //  }
  // calculate the cursor
  // int16_t  cx = bbx - tbx;
  int16_t cy = 75;  // bby - tby;

  int16_t cx = display.width() / 2 - tbw / 2;  // bbx - tbx;
  //  y = display.height()/2 - tbh/2; //bby - tby;

  Serial.print("Cursor pos: x ");
  Serial.print(cx);
  Serial.print(" y ");
  Serial.print(cy);
  Serial.println();

  Serial.print("window: ");
  Serial.print(bbx);
  Serial.print(", ");
  Serial.print(bby);
  Serial.print(", ");
  Serial.print(bbw);
  Serial.print(", ");
  Serial.print(bbh);
  Serial.println();

  //  display.setPartialWindow(bbx, bby, bbw, bbh);
  //  display.setPartialWindow(bbx, 0, bbw, cy + bbh);
  display.setPartialWindow(0, 5, 250, cy + bbh);
  display.firstPage();

  do {

    // if (isBlackOnWhite == true)
    //   display.fillScreen(GxEPD_WHITE);
    // else
    //   display.fillScreen(GxEPD_BLACK);
    // display.drawRect(0, 5, 250, cy + bbh, GxEPD_BLACK); //frame
    display.setCursor(cx, cy);
    display.print(_word);

    
      if (isBlackOnWhite == true) {
        if(bSD_card_present == false) display.fillRect(250/2, 0, 3, 3, GxEPD_BLACK);
      } else {
        if(bSD_card_present == false) display.fillRect(250/2, 0, 3, 3, GxEPD_WHITE);
      }
  

    

  } while (display.nextPage());

  delay(100);
}

void update_ePaper() {
  drawWord_ePaper(old_text, true);
  drawWord_ePaper(current_text, false);
  old_text = current_text;
}

