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

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

float x = 160, y = 110, x1 = 109, y1 = 70, x2 = 213, y2 = 70, x3 = 264, y3 = 105,
x4 = 194, y4 = 155, x5 = 123, y5 = 156, x6 = 54, y6 = 106;
int angle = 0;
int frameRateCount = 1;
float lastTime = 0;
boolean switchFigure = true;
boolean switchDrawFPS = true;

void setup() {
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);

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
  tft.println("Touch the screen to start test");
  waitOneTouch();
  //delay(5000);

  //Main screen
  tft.fillScreen(BLACK);
}

TSPoint waitOneTouch() {
  // wait 1 touch to exit function
  TSPoint p;
  do {
    p = ts.getPoint(); 
    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT); 
  } while((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));
  return p;
}

void drawFigure(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4,
                int x5, int y5, int x6, int y6, int color){
  tft.drawLine(x1, y1, x2, y2, color);
  tft.drawLine(x2, y2, x3, y3, color);
  tft.drawLine(x3, y3, x4, y4, color);
  tft.drawLine(x4, y4, x5, y5, color);
  tft.drawLine(x5, y5, x6, y6, color);
  tft.drawLine(x6, y6, x1, y1, color);
}

void rotate(){
  float a1, b1, a2, b2, a3, b3, a4, b4, a5, b5, a6, b6;
  
  //Рисуем фигуру
  float Ang = (angle * 3.14) / 180;
  a1 = x + (x1 - x) * cos(Ang) - (y1 - y) * sin(Ang);
  b1 = y + (x1 - x) * sin(Ang) + (y1 - y) * cos(Ang);
  a2 = x + (x2 - x) * cos(Ang) - (y2 - y) * sin(Ang);
  b2 = y + (x2 - x) * sin(Ang) + (y2 - y) * cos(Ang);
  a3 = x + (x3 - x) * cos(Ang) - (y3 - y) * sin(Ang);
  b3 = y + (x3 - x) * sin(Ang) + (y3 - y) * cos(Ang);
  a4 = x + (x4 - x) * cos(Ang) - (y4 - y) * sin(Ang);
  b4 = y + (x4 - x) * sin(Ang) + (y4 - y) * cos(Ang);
  a5 = x + (x5 - x) * cos(Ang) - (y5 - y) * sin(Ang);
  b5 = y + (x5 - x) * sin(Ang) + (y5 - y) * cos(Ang);
  a6 = x + (x6 - x) * cos(Ang) - (y6 - y) * sin(Ang);
  b6 = y + (x6 - x) * sin(Ang) + (y6 - y) * cos(Ang);
  drawFigure(a1, b1, a2, b2, a3, b3, a4, b4, a5, b5, a6, b6, WHITE);
  
  //Очищаем экран от прошлой фигуры
  Ang = ((angle - 3) * 3.14) / 180;
  a1 = x + (x1 - x) * cos(Ang) - (y1 - y) * sin(Ang);
  b1 = y + (x1 - x) * sin(Ang) + (y1 - y) * cos(Ang);
  a2 = x + (x2 - x) * cos(Ang) - (y2 - y) * sin(Ang);
  b2 = y + (x2 - x) * sin(Ang) + (y2 - y) * cos(Ang);
  a3 = x + (x3 - x) * cos(Ang) - (y3 - y) * sin(Ang);
  b3 = y + (x3 - x) * sin(Ang) + (y3 - y) * cos(Ang);
  a4 = x + (x4 - x) * cos(Ang) - (y4 - y) * sin(Ang);
  b4 = y + (x4 - x) * sin(Ang) + (y4 - y) * cos(Ang);
  a5 = x + (x5 - x) * cos(Ang) - (y5 - y) * sin(Ang);
  b5 = y + (x5 - x) * sin(Ang) + (y5 - y) * cos(Ang);
  a6 = x + (x6 - x) * cos(Ang) - (y6 - y) * sin(Ang);
  b6 = y + (x6 - x) * sin(Ang) + (y6 - y) * cos(Ang);
  drawFigure(a1, b1, a2, b2, a3, b3, a4, b4, a5, b5, a6, b6, BLACK);
}

void drawFPS(){
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(2);
  tft.print("FPS: ");
}

void loop() {
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    switchDrawFPS = true;
    tft.fillScreen(BLACK);
    switchFigure = !switchFigure;
   }
  if(switchFigure){
    float currentTime = millis();
    ++frameRateCount;
    if (currentTime - lastTime >= 1000){
      if (switchDrawFPS){
        switchDrawFPS = !switchDrawFPS;
        drawFPS();
      }
      tft.setCursor(50, 0);
      tft.print(String(frameRateCount));
      frameRateCount = 1;
      lastTime = currentTime;
    }
    rotate();
    //delay(100);
    angle += 3;
   }
   if (!switchFigure){
      do {
        drawFigure(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, BLACK);
        x1 > 160 ? --x1 : ++x1;
        y1 > 120 ? --y1 : ++y1;
        x2 > 160 ? --x2 : ++x2;
        y2 > 120 ? --y2 : ++y2;
        x3 > 160 ? --x3 : ++x3;
        y3 > 120 ? --y3 : ++y3;
        x4 > 160 ? --x4 : ++x4;
        y4 > 120 ? --y4 : ++y4;
        x5 > 160 ? --x5 : ++x5;
        y5 > 120 ? --y5 : ++y5;
        x6 > 160 ? --x6 : ++x6;
        y6 > 120 ? --y6 : ++y6;
        drawFigure(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, WHITE);
      } while (x1 != 160 && y1 != 160 && x2 != 160 && y2 != 160 && x3 != 160 && y3 != 160 && 
               x4 != 160 && y4 != 160 && x5 != 160 && y5 != 160 && x6 != 160 && y6 != 160);
      //tft.print("DELO SDELANO");
      //delay(20);
   }
}
