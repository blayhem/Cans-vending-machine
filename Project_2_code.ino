
// INCLUDE LIBRARIES NECESSARY TO MAKE USE OF THE DIFFERENT DEVICES NEEDED.
#include <LiquidCrystal.h>
#include <Servo.h> 

//CREATE INSTANCES OF LCD SCREEN AND SERVO
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo myservo;

//CONNECTION POINTS TO THE SENSOR AND SERVO MOTOR
const int FLEX_PIN = A0;
const int servoinput = 9;

//SERVO MOTOR POSTIONS
const int pos0 = 0;
const int pos1 = 90;
const int pos2 = 180;

//FLEXOR CONSTANTS
const float VCC = 4.98;
const float R_DIV = 10000.0;
const float STRAIGHT_RESISTANCE = 37300.0; 
const float BEND_RESISTANCE = 90000.0;

const float COIN_FLEX = 35000.00;

// SET UP DEVICE
void setup() {
  myservo.attach(servoinput);
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
  
  //CONFIG. LCD SCREEN 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

// THE FLEX SENSOR ANALYSES IF A COIN WAS INSERTED AND RETURNS IF TRUE OR FALSE
bool coinInserted(){
  int flexADC = analogRead(FLEX_PIN);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  Serial.println("Resistance: " + String(flexR) + " ohms");
  
  // money_in
  return flexR >= COIN_FLEX
}

//INITIAL DISPLAY MESSAGE
void initDisplay(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INTRODUCE 1 EURO");
  lcd.setCursor(0, 1);
  lcd.print("FOR 1 COCA-COLA");
  delay(2000);
}

void giveCan() {
  // PREPARE PRODUCT
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PREPARING");
  lcd.setCursor(0, 1);
  lcd.print("PRODUCT");
 
  myservo.write(pos1);
  delay(1000);
  myservo.write(pos2);
  delay(2500);
  myservo.write(pos0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("THANK YOU FOR");
  lcd.setCursor(0, 1);
  lcd.print("YOUR PURCHASE");
  delay(3500);
}

void loop() {
  
  //RUN PROGRAM
  while (coinInserted() == false){
    initDisplay();
  }

  giveCan();
  delay(500);
}
