#include <LiquidCrystal.h>
const int button=1;
volatile byte st = LOW;
int state=0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int adc_key_in  = 0;
#define btnUP     1
int A[8];
int f=0;
int f2=0;
int s=0;
int t=400;
#define led 2
const int buzzer = 3;

byte player[8] = {
  B01110,
  B01110,
  B00100,
  B11111,
  B01110,
  B01010,
  B01010,
};

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);
 if (adc_key_in > 10)   return btnUP;
 else {return 0;}
}

void setup() {
  pinMode(button,INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
  tone(buzzer, 6000);
  delay(200);
  tone(buzzer, 10000);
  delay(600);
  noTone(buzzer);
  lcd.createChar(0, player);
  lcd.begin(16, 2);
  lcd.print("GAME STARTS IN!");
  delay(500);
  lcd.clear();
  lcd.print("3");
  delay(500);
  lcd.clear();
  lcd.print("2");
  delay(500);
  lcd.clear();
  lcd.print("1");
  delay(500);
  lcd.clear();
  lcd.print("GO!");
  delay(500);
  lcd.clear();
  digitalWrite(led,LOW);
  Serial.begin(9600);
}

void loop() {
  if (f==1) {while (1){}}
  for (int i=0; i<8; ++i){
    A[i]=random(6)+2;
    lcd.setCursor(2*A[i], A[i]%2);
    lcd.print('#');
  }
  lcd.setCursor(15, state);
  lcd.print(' ');
  for(int i=0; i<16; ++i){
    digitalWrite(led,HIGH);
    int state=read_LCD_buttons();
    lcd.setCursor(i, state);
    for (int k=0;k<8;k++){
      if (i==A[k]*2){
        if (A[k]%2==state){
          digitalWrite(led,HIGH);
          f=1;
          f2=1;
          tone(buzzer, 2000);
          delay(500);
          tone(buzzer, 4500);
          delay(500);
          tone(buzzer, 6000);
          delay(500);
          noTone(buzzer);
          lcd.clear();
          lcd.print("GAME OVER!");
          lcd.setCursor(0,1);
          lcd.print("SCORE: ");
          lcd.print(s);
          break;
      }
      }
    }
    if (f2==1) {break;}
    lcd.write(byte(0));
    if (i==0){
    lcd.setCursor(15, state);
    lcd.print(' ');
    lcd.setCursor(15, (state+1)%2);
    lcd.print(' ');
    }
    else{
      lcd.setCursor((i-1), state);
      lcd.print(' ');
      lcd.setCursor((i-1), (state+1)%2);
      lcd.print(' ');
      }
    s=s+1;
    tone(buzzer, 13000);
    delay(100);
    noTone(buzzer);
    delay(t/2);
    digitalWrite(led,LOW);
    delay(t/2);
    }
    t=t-20;
    if (t<100){t=100;}
}
