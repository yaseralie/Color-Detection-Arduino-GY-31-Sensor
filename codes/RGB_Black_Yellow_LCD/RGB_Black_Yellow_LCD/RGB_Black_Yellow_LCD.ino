/*
  For UNO, use SDA = A4, SCL = A5
  For MEGA, use SDA = 20, SCL = 21
*/
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

const int s0 = A8;
const int s1 = A9;
const int s2 = A10;
const int s3 = A11;
const int out = A12;
// values
int red = 0;
int green = 0;
int blue = 0;

String color_detection;

void setup()
{
  Serial.begin(9600);
  //LCD
  lcd.init();                      // initialize the lcd
  lcd.backlight();

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
}

void loop()
{
  color();
  Serial.println("RED");
  Serial.println(red, DEC);
  Serial.println(" GREEN ");
  Serial.println(green, DEC);
  Serial.println(" BLUE ");
  Serial.println(blue, DEC);
  delay(1000);
  if (red < blue && green < blue && green < 10 && blue >= 9)
  {
    color_detection = "YELLOW";
    Serial.println(" - (Yellow Color)");
  }
  else if (red < blue && red < green && red < 20 && green >= 10)
  {
    color_detection = "RED";
    Serial.println(" - (Red Color)");
  }
  else if (blue < red && blue < green)
  {
    color_detection = "BLUE";
    Serial.println(" - (Blue Color)");
  }
  else if (green < red && green < blue)
  {
    color_detection = "GREEN";
    Serial.println(" - (Green Color)");
  }
  else if (red >= 20 && green >= 20 && blue >= 20) {
    color_detection = "BLACK";
    Serial.println(" - (Black Color)");
  }
  else {
    Serial.println();
  }
  lcd.setCursor(0, 0);
  lcd.print("Color detection");
  lcd.setCursor(0, 1);
  lcd.print(color_detection + "   ");
}

void color()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
