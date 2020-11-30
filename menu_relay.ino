#include <Wire.h>                     // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 2004 I2C용 라이브러리
LiquidCrystal_I2C lcd(0x27,20,4);     // 접근주소: 0x3F or 0x27

//int pins[] = { 0, 9, 10 };
//int pushButton[] = {8, 9, 10, 11, 12, 13};

const int relayPin01 = 8;
const int relayPin02 = 9;
const int relayPin03 = 10;
const int relayPin04 = 11;

const int btnSELECT = 3; 
const int btnBACK = 4; 
const int btnUP = 5; 
const int btnDOWN = 6; 
const int btnNONE = 6; 


int btnSELECTstate = 1;
int btnBACKstate = 1;
int btnUPstate = 1;
int btnDOWNstate = 1;
int cursor = 1;
 
void setup()
{
  Serial.begin(9600);

  // relay  
  pinMode(relayPin01, OUTPUT); 
  pinMode(relayPin02, OUTPUT); 
  pinMode(relayPin03, OUTPUT); 
  pinMode(relayPin04, OUTPUT); 

  // button
  pinMode(btnSELECT, INPUT); 
  pinMode(btnBACK, INPUT); 
  pinMode(btnUP, INPUT); 
  pinMode(btnDOWN, INPUT); 

//  for (int i = 0; i <= 3; i++) {
//       pinMode(pins[i], INPUT);
//  }
  
  lcd.init();                      // LCD 초기화
  lcd.backlight();                // 백라이트 켜기
  menu();
}

void setPin() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PIN SETTING");
  delay(3000);
}

void menuBack() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("#SETTING");
  lcd.setCursor(0, 1);
  lcd.print("Back");
}

void menu() {
  lcd.clear();
  cursor = 1;
  lcd.setCursor(0, 1); 
  lcd.print("1*");
  lcd.setCursor(2, 1); 
  lcd.print("2");
  lcd.setCursor(4, 1); 
  lcd.print("3");
  lcd.setCursor(6, 1); 
  lcd.print("4");
}
 
void loop()
{ 
  lcd.setCursor(0, 0);          // 첫번째 줄 문자열 출력
  lcd.print("Hello, world!");
  
//  for(int i=0; i<4; i++){   // 오른쪽으로 4칸 움직이기
//    lcd.scrollDisplayRight();
//    delay(500);
//  }
//  for(int j=0; j<4; j++){   // 왼쪽으로 4칸 움직이기
//    lcd.scrollDisplayLeft();
//    delay(500);
//  }

   if (digitalRead(btnSELECT) == LOW) {
       while (digitalRead(btnSELECT) == LOW);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("#SETTING");
       lcd.setCursor(0, 1);
       lcd.print(cursor);
       lcd.setCursor(0, 2);
       lcd.print("Disable *");
       lcd.setCursor(0, 3);
       lcd.print("Enable  ");

       while(1) {
         if (digitalRead(btnUP) == LOW) {
           while (digitalRead(btnUP) == LOW);
              lcd.setCursor(0, 2);
              lcd.print("Disable  ");
              lcd.setCursor(0, 3);
              lcd.print("Enable *");

              while(1) {
                if (digitalRead(btnSELECT) == LOW) {
                    while (digitalRead(btnSELECT) == LOW);
                    delay(1000);
                    switch (cursor) {
                      case 1:
                           digitalWrite(relayPin01, HIGH);
                           break;
                      case 3:
                           digitalWrite(relayPin02, HIGH);
                           break;
                      case 5:
                           digitalWrite(relayPin03, HIGH);
                           break;
                      case 7:
                           digitalWrite(relayPin04, HIGH);
                           break;
                      default:
                           digitalWrite(relayPin01, HIGH);
                           break;
                    }
                    menuBack();
                    break;
                    
                } else if (digitalRead(btnDOWN) == LOW) {
                    while (digitalRead(btnDOWN) == LOW);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("#SETTING");
                    lcd.setCursor(0, 1);
                    lcd.print(cursor);
                    lcd.setCursor(0, 2);
                    lcd.print("Disable *");
                    lcd.setCursor(0, 3);
                    lcd.print("Enable  ");

                    while(1) {
                      if (digitalRead(btnSELECT) == LOW) {
                          while (digitalRead(btnSELECT) == LOW);

                          digitalWrite(relayPin04, HIGH);
                          break;
                      } else if (digitalRead(btnBACK) == LOW) {
                          while (digitalRead(btnBACK) == LOW);
                          break;
                      } else if (digitalRead(btnBACK) == LOW) {
                          while (digitalRead(btnBACK) == LOW);
                          break;
                      }                 
                      break;
                    }
                    
                } else if (digitalRead(btnUP) == LOW) {
                    while (digitalRead(btnUP) == LOW);
                    break;
                }
              }
            
          } else if (digitalRead(btnBACK) == LOW) {
            while (digitalRead(btnBACK) == LOW);
            menu();
            break;
          } else if (digitalRead(btnSELECT) == LOW) {
            while (digitalRead(btnSELECT) == LOW);

            delay(1000);

            switch (cursor) {
               case 1:
                    digitalWrite(relayPin01, LOW);
                    delay(3000);
                    break;
               case 3:
                    digitalWrite(relayPin02, LOW);
                    delay(3000);
                    break;
               case 5:
                    digitalWrite(relayPin03, LOW);
                    delay(3000);
                    break;
               case 7:
                    digitalWrite(relayPin04, LOW);
                    delay(3000);
                    break;
               default:
                    digitalWrite(relayPin01, LOW);
                    delay(3000);
                    break;
            }
            menuBack();
          }
       }

   }
   else if (digitalRead(btnUP) == LOW) {
       while (digitalRead(btnUP) == LOW);
       lcd.setCursor(cursor, 1);
       lcd.print(" ");
       cursor = cursor + 2;
       if (cursor > 8 ) cursor = 1;
       lcd.setCursor(cursor, 1);
       lcd.print("*");
       Serial.println(cursor);
   }
   else if (digitalRead(btnDOWN) == LOW) {
       while (digitalRead(btnDOWN) == LOW);
       lcd.setCursor(cursor, 1);
       lcd.print(" ");
       cursor = cursor - 2;
       if (cursor < 0 ) cursor = 7;
       lcd.setCursor(cursor, 1);
       lcd.print("*");
       Serial.println(cursor);
   }
}
