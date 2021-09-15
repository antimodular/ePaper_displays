
//HUZZAH32 == 14 //Feather M4 Express == 5
#define SD_CHIP_SELECT 14  //SS
#define SPI_SPEED SD_SCK_MHZ(20)

bool sd_debug = false;

cid_t m_cid;
csd_t m_csd;
uint32_t m_eraseSize;
uint32_t m_ocr;

void sdCard_setup() {

  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);

  Serial.println("sdCard_setup()");


  int sdCard_attempts = 0;
  // while (!SD.begin(SD_CHIP_SELECT) && sdCard_attempts < 10) {
  if (!SD.begin(SD_CHIP_SELECT, SPI_SPEED)) {
    sdCard_attempts++;
    Serial.print("Card Mount Failed: ");
    Serial.print(sdCard_attempts);
    Serial.println();

    bSD_card_present = false;
    errorPrint();
    delay(500);
  } else {
    bSD_card_present = true;
  }
  printCardType();


  if (SD.exists("main.txt")) {
    //        isMain = true;
    Serial.print("isMain: ");
    // Serial.println(isMain);
  }
  // listDir("/", 0);

  readFile("myFile.txt", 100);

  Serial.println();
}



void listDir(const char* dirname, uint8_t levels) {
  /*
   
  */
}



void readFile(String path, int _maxChars) {
  Serial.printf("Reading file: %s\n", path);

  // File file = fs.open(path);
  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  // Rewind the file for read.
  file.seek(0);

  int charCounter = 0;
  Serial.print("Read from file: ");
  while (file.available() && charCounter < _maxChars) {
    Serial.write(file.read());  //writes each char one at a time
    //    Serial.print(lineCounter);
    //    Serial.print(":");
    //    Serial.print(file.read());
    //    Serial.println();
    charCounter++;
  }
  file.close();
}


String readOneLineFromFile(String path, int _lineNumber) {

  if (sd_debug) {
    Serial.printf("Reading line from : %s\n", path);
    Serial.print("_lineNumber ");
    Serial.print(_lineNumber);
    Serial.println();
  }

  // File file = fs.open(path);
  File file = SD.open(path, FILE_READ);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return "FAILED!";
  }

  int lineCounter = 0;

  String myStr = "";
  char cr;
  while (file.available()) {

    cr = file.read();
    if (cr == '\n') {
      lineCounter++;
      cr = file.read();  //to not use the line break

      if (lineCounter == _lineNumber) {
        if (sd_debug) {
          Serial.print("found line ");
          Serial.print(lineCounter);
          Serial.println();
        }
      } else if (lineCounter > _lineNumber) {
        break;
      }
    }



    if (lineCounter == _lineNumber) {
      if (sd_debug) Serial.write(cr);
      myStr += cr;
      //      Serial.write(file.read());
      //      Serial.print(lineCounter);
      //      Serial.print(":");
      //      Serial.print(file.read());
      //      Serial.println();
    }
  }
  //  Serial.println();
  //  Serial.print(lineCounter);
  if (sd_debug) {
    Serial.println();
    Serial.println("++++++");
    Serial.print(myStr);
    Serial.println();
    Serial.println("-----");
  }
  file.close();

  return myStr;
}


//------------------------------------------------------------------------------
void printCardType() {

  Serial.print("\nCard type: ");

  switch (SD.card()->type()) {
    case SD_CARD_TYPE_SD1:
      Serial.print("SD1\n");
      break;

    case SD_CARD_TYPE_SD2:
      Serial.print("SD2\n");
      break;

    case SD_CARD_TYPE_SDHC:
      if (sdCardCapacity(&m_csd) < 70000000) {
        Serial.print("SDHC\n");
      } else {
        Serial.print("SDXC\n");
      }
      break;

    default:
      Serial.print("Unknown\n");
  }
}

//------------------------------------------------------------------------------
void errorPrint() {
  if (SD.sdErrorCode()) {
    // Serial.print("SD errorCode: ");
    // Serial.print(showbase,HEX);
    printSdErrorSymbol(&Serial, SD.sdErrorCode());
    Serial.print(" = ");
    Serial.println(SD.sdErrorCode());
    Serial.print("SD errorData = ");
    Serial.println(SD.sdErrorData());
  }
}
