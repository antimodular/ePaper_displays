void full_white()
{
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
  }
  while (display.nextPage());
}

void full_black()
{
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_BLACK);
  }
  while (display.nextPage());
}

void partial_white()
{
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
  }
  while (display.nextPage());
}

void partial_black()
{
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_BLACK);
  }
  while (display.nextPage());
}

void draw_square(uint16_t _x, uint16_t _y, uint16_t _w, uint16_t _h)
{

  display.setPartialWindow(0, 0, display.width(), display.height());
  display.firstPage();
  do
  {
    if (isBlackOnWhite == true)  display.fillRect(_x, _y, _w, _h, GxEPD_BLACK);
    else  display.fillRect(_x, _y, _w, _h, GxEPD_WHITE);
  }
  while (display.nextPage());
}

void horizontal_stripes(uint16_t nr)
{
  uint16_t h = display.height() / nr;
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.firstPage();
  do
  {
    uint16_t y = 0;
    do
    {
      display.fillRect(0, y, display.width(), h, GxEPD_BLACK);
      y += h;
      if (y >= display.height()) break;
      display.fillRect(0, y, display.width(), h, GxEPD_WHITE);
      y += h;
    } while (y < display.height());
  }
  while (display.nextPage());
}

void vertical_stripes(uint16_t nr)
{
  uint16_t w = display.width() / nr;
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.firstPage();
  do
  {
    uint16_t x = 0;
    do
    {
      display.fillRect(x, 0, w, display.height(), GxEPD_BLACK);
      x += w;
      if (x >= display.width()) break;
      display.fillRect(x, 0, w, display.height(), GxEPD_WHITE);
      x += w;
    } while (x < display.width());
  }
  while (display.nextPage());
}
