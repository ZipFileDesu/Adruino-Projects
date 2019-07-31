// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

// Modified for SPFD5408 Library by Joao Lopes
// Version 0.9.2 - Rotation for Mega and screen initial

// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
// *** SPFD5408 change -- End

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

// Modified for SPFD5408 Library by Joao Lopes
// Version 0.9.2 - Rotation for Mega and screen initial

// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
// *** SPFD5408 change -- End

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//int COLOR[8] = {0x001F, 0xF800, 0x07E0, 0x07FF, 0xF81F, 0xFFE0, 0xFFE0, 0xFFFF};
int Angle = 0;
int x1 = 139, y1 = 55, x2 = 193, y2 = 103, x3 = 109, y3 = 94, p = 147, q = 83;
float COORD_X1[60];
float COORD_Y1[60];
float COORD_X2[60];
float COORD_Y2[60];
float COORD_X3[60];
float COORD_Y3[60];
int frameRateCount = 1;
float lastTime = 0;

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup(void) {
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);

  //Заполняем массив координатами, чтобы лишний раз не загружать процессор
  for (int i; i < 60; ++i){
    float Ang = ((i * 6) * 3.14) / 180;
    COORD_X1[i] = p + (x1 - p) * cos(Ang) - (y1 - q) * sin(Ang);
    COORD_Y1[i] = q + (x1 - p) * sin(Ang) + (y1 - q) * cos(Ang);
    COORD_X2[i] = p + (x2 - p) * cos(Ang) - (y2 - q) * sin(Ang);
    COORD_Y2[i] = q + (x2 - p) * sin(Ang) + (y2 - q) * cos(Ang);
    COORD_X3[i] = p + (x3 - p) * cos(Ang) - (y3 - q) * sin(Ang);
    COORD_Y3[i] = q + (x3 - p) * sin(Ang) + (y3 - q) * cos(Ang);
  }
  //Title screen
  tft.fillScreen(BLACK);
  tft.fillRect(20, 20, 280, 200, WHITE);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.setCursor(60, 60);
  tft.print("2D triangle ");
  tft.setCursor(40, 90);
  tft.print("graphics test");
  tft.setCursor(35, 120);
  tft.print("by ZipFileDesu");
  tft.setTextSize(1);
  tft.setCursor(50, 160);
  tft.println("The test will start after 5 seconds");
  delay(5000);

  //Main screen
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(2);
  tft.print("FPS: ");
}

void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3, int COLOR){
  tft.drawTriangle(x1, y1, x2, y2, x3, y3, COLOR);
  /*tft.drawLine(x1, y1, x2, y2, COLOR);
  tft.drawLine(x2, y2, x3, y3, COLOR);
  tft.drawLine(x3, y3, x1, y1, COLOR);*/
}

void undrawTriangle(int x1,int y1,int x2,int y2,int x3,int y3){
  tft.drawTriangle(x1, y1, x2, y2, x3, y3, BLACK);
  /*tft.drawLine(x1, y1, x2, y2, BLACK);
  tft.drawLine(x2, y2, x3, y3, BLACK);
  tft.drawLine(x3, y3, x1, y1, BLACK);*/
}

/*void Rotate(int x1,int y1,int x2,int y2,int x3,int y3, int Angle)
{
    int x,y,a1,b1,a2,b2,a3,b3;
    float Ang;

    Ang=((Angle-4)*3.14)/180;
    a1=p+(x1-p)*cos(Ang)-(y1-q)*sin(Ang);
    b1=q+(x1-p)*sin(Ang)+(y1-q)*cos(Ang);
    a2=p+(x2-p)*cos(Ang)-(y2-q)*sin(Ang);
    b2=q+(x2-p)*sin(Ang)+(y2-q)*cos(Ang);
    a3=p+(x3-p)*cos(Ang)-(y3-q)*sin(Ang);
    b3=q+(x3-p)*sin(Ang)+(y3-q)*cos(Ang);
    undrawTriangle(a1,b1,a2,b2,a3,b3);
    
    Ang=(Angle*3.14)/180;
    a1=p+(x1-p)*cos(Ang)-(y1-q)*sin(Ang);
    b1=q+(x1-p)*sin(Ang)+(y1-q)*cos(Ang);
    a2=p+(x2-p)*cos(Ang)-(y2-q)*sin(Ang);
    b2=q+(x2-p)*sin(Ang)+(y2-q)*cos(Ang);
    a3=p+(x3-p)*cos(Ang)-(y3-q)*sin(Ang);
    b3=q+(x3-p)*sin(Ang)+(y3-q)*cos(Ang);
    drawTriangle(a1,b1,a2,b2,a3,b3, GREEN);
}*/

void loop(void) {
  //tft.setTextColor(WHITE, BLACK);
  float currentTime = millis();
  ++frameRateCount;
  if (currentTime - lastTime >= 1000){
    tft.setCursor(50, 0);
    tft.print(frameRateCount);
    frameRateCount = 1;
    lastTime = currentTime;
  }
  
  Angle < 59 ? ++Angle : Angle = 0;
  //Angle += 1;
  //Rotate(x1, y1, x2, y2, x3, y3, Angle);
  drawTriangle(COORD_X1[Angle],COORD_Y1[Angle],COORD_X2[Angle],COORD_Y2[Angle],COORD_X3[Angle],COORD_Y3[Angle], GREEN);
  if (Angle != 0){
    undrawTriangle(COORD_X1[Angle - 1],COORD_Y1[Angle - 1],COORD_X2[Angle - 1],COORD_Y2[Angle - 1],
      COORD_X3[Angle - 1],COORD_Y3[Angle - 1]);
  }
  else{
    undrawTriangle(COORD_X1[59],COORD_Y1[59],COORD_X2[59],COORD_Y2[59],
      COORD_X3[59],COORD_Y3[59]);
  }
  //delay(20); 
}
