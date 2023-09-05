#include <Keypad.h>
#include <LiquidCrystal.h>
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
int speakerPin = 11;
int melody[] = {
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4,
  NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, 0,
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4,
  NOTE_GS4, NOTE_GS4, NOTE_B4, NOTE_GS4, NOTE_A4, 0 };
float noteDurations[] = {
  2,2,2,2,1,2,
  2,2,2,2,1,1,
  2,2,2,2,1,2,
  2,4,4,2,2,2};
const int redPin = 0;
const int greenPin = 1;
const int bluePin = 2;

const byte ROWS = 4; 
const byte COLS = 4; 

byte rowPins[ROWS] = {10,9,8,7};
byte colPins[COLS] = {6,5,4,3}; 

char keymap[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, 
                         colPins, ROWS, COLS);

int position=0;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int in1=0, in2=0, in3=0, in4=0, int1=0, int2=0, i =0;
int kqg[] = {0, 0, 0, 0};
int kqp[] = {0, 0, 0, 0};
int tmp=0; 

int divs(int a, int b) {
  int kq=0;
  while (a >= b) {
    a = a - b;
    kq++;
  }
  return kq;
}
int h=10,m=30,s=5;
int alarmh=0,alarmm=0,alarms=0;
int alarmseth=0,alarmsetm=0,alarmsets=0;
int mode=0;
char btnA = 'A';
char btnB = 'B';
char btnC = 'C';
char btnD = 'D';
char btnStar = '*';
char btnHashTag = '#';

void setup()
{
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Sleepy 3 Friends");
  lcd.setCursor(3, 1);
  lcd.print("Welcome <3");
  delay(5000);
  lcd.clear();
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop(){
  if(mode == 0) clock();
  else if(mode == 4) goldenSleepTimer();
  else if (mode == 3) Alarmornot();
  else if (mode == 2) choicewhat();
  else if (mode == 1) {
    setAlarm();
    clock();
  }
}

//////////****************CHECK STATE***************//////////
void checkState(){
  char key = myKeypad.getKey();
  if (key) {
    Serial.println(key);
    if (key == btnD) {
      Serial.println(key);
      lcd.clear();
      mode = 4;
    }
    else if (key == btnHashTag){ 
      Serial.println(key);
      lcd.clear();
      mode = 0; 
    }
  }
}

void checkAB(){
  char keyAB = myKeypad.getKey();
  if (keyAB) {
    if (keyAB == btnA) {
      lcd.clear();
      mode = 2;
    } else if (keyAB == btnB) {
      lcd.clear();
      mode = 0;
    }
  }
}

//////////****************CLOCK***************//////////
void clock(){
  delay(1000);
  s++;
  if(s == 60)
  {
    m++;
    s = 0;
  }
  
  if(m == 60)
  {
    m = 0;
    h++;
  }

  if(h == 24)
  {
    h = 0;
  }
  
  if(h >=0 && h <=9)
  {
   lcd.setCursor(2,0);
   lcd.print("0");
   lcd.setCursor(3,0);
   lcd.print(h);
  }
  else
  {
   lcd.setCursor(2,0);
   lcd.print(h);
  }
  
  lcd.setCursor(5,0);
  lcd.print(":");
  
  if (m >=0 && m <=9)
  {
   lcd.setCursor(7,0);
   lcd.print("0");
   lcd.print(m);
  }
  else
  {
   lcd.setCursor(8,0);
   lcd.print(" ");
   lcd.setCursor(7,0);
   lcd.print(m);
  }
  
  lcd.setCursor(10,0);
  lcd.print(":");
  
  if(s >=0 && s <=9)
  {
   lcd.setCursor(12,0);
   lcd.print("0");
   lcd.print(s);
  }
  else
  {
   lcd.setCursor(13,0);
   lcd.print(" ");
   lcd.setCursor(12,0);
   lcd.print(s);
  }
  checkState();
}

//////////****************GOLDEN SLEEP TIMER***************//////////
void goldenSleepTimer() {
  char key1 = myKeypad.getKey();
  lcd.setCursor(1,0);    
  	lcd.print("Nhap Gio, Phut");
  if (key1)
    if (key1 != 'A' && key1 != 'B' 
        && key1 != 'C' && key1 != 'D' 
        && key1 != '#' && key1 != '*')
  {
    lcd.setCursor(5 + position,1);
    Serial.println(key1); 
    position++;
    key1 = key1-48;
    
    switch(position){
    case 1: in1 = key1;
      lcd.print(in1);
    break;
    case 2: in2 = key1;
      lcd.print(in2);
      lcd.print("h");
      position++;
      break;
    case 4: in3 = key1;
      lcd.print(in3);
      break;
    case 5: in4 = key1; 
      lcd.print(in4);
      delay(1000);
      lcd.clear(); 
      int1 = in1*10 + in2;
      int2 = in3*10 + in4;
      int1 = (int1 + divs(int2,60)) % 24;
      int2 = int2 % 60;
      position = 0;
      delay(1000);
      lcd.clear();
      lcd.print("Da nhap : ");
      lcd.setCursor(1,1);    
      lcd.print(int1);
      lcd.print(" Gio ");
      lcd.print(int2);
      lcd.print(" Phut");
      position = 0;
      delay(3000);
      lcd.clear();

      lcd.setCursor(1,0);
      char meg[] ="4 thoi gian nen";
      for(int i=0;i<15;i++){
        lcd.print(meg[i]);
        delay(200);
      }
      lcd.setCursor(16, 0);
      lcd.autoscroll();
      char megw[] =" thuc";
      for(int i=0;i<5;i++){
        lcd.print(megw[i]);
        delay(200);
      }
      delay(2000);
      lcd.noAutoscroll();
      lcd.clear();
      
      for (i=0; i <= 3; i++) {
        lcd.setCursor(0,0);
        lcd.print(i+1);
        lcd.print(">");
       	kqp[i] = 90*(i+3) + int2 + 14; 
        kqg[i] = (int1 + divs(kqp[i], 60)) % 24;
        kqp[i] = kqp[i] % 60;
        lcd.print(kqg[i]);
        lcd.print(" Gio ");
        lcd.print(kqp[i]);
        lcd.print(" Phut");
        delay(3000);
        if (i < 3) {
          lcd.setCursor(5,1);
          lcd.print("Hoac");
          delay(2000);
        }
        lcd.clear();
      }
      mode = 3;
    } 
  }
}

void Alarmornot() {
  lcd.setCursor(1,0);
  lcd.print("Alarm or not?");
  lcd.setCursor(1,1);
  lcd.print("A. YES || B. NO");
  checkAB();
}

void choicewhat() {
  char key = myKeypad.getKey();
  lcd.setCursor(1,0);
  lcd.print("Press 1 - 4");
  lcd.setCursor(1,1);
  lcd.print("Enter: ");
  if (key) {
    if (key == '1') {
      alarmsetm = kqp[0] - m;
      if (alarmsetm < 0) {
        alarmsetm += 60;
        kqg[0] -= 1;
      }
      alarmseth = kqg[0] - h;
      if (alarmseth < 0)
        alarmseth = alarmseth + 24;
      alarmsets = 0;
      lcd.clear();
      mode = 1;
    }
    else if (key == '2') {
      alarmsetm = kqp[1] - m;
      if (alarmsetm < 0) {
        alarmsetm += 60;
        kqg[1] -= 1;
      }
      alarmseth = kqg[1] - h;
      if (alarmseth < 0)
        alarmseth = alarmseth + 24;
      alarmsets = 0;
      lcd.clear();
      mode = 1;
    }
    else if (key == '3') {
      alarmsetm = kqp[2] - m;
      if (alarmsetm < 0) {
        alarmsetm += 60;
        kqg[2] -= 1;
      }
      alarmseth = kqg[2] - h;
      if (alarmseth < 0)
        alarmseth = alarmseth + 24;
      alarmsets = 0;
      lcd.clear();
      mode = 1;
    }
    else if (key == '4') {
      alarmsetm = kqp[3] - m;
      if (alarmsetm < 0) {
        alarmsetm += 60;
        kqg[3] -= 1;
      }
      alarmseth = kqg[3] - h;
      if (alarmseth < 0)
        alarmseth = alarmseth + 24;
      alarmsets = 0;
      lcd.clear();
      mode = 1;
    }
    else {
      lcd.clear();
      mode = 0;
    }
  }
}

void setAlarm() {
  lcd.setCursor(0,1);
  lcd.print("Alarm:");
  
  if(alarmseth == alarmh)
  {
    if(alarmsetm == alarmm)
    {
      if(alarmsets == alarms)
      {
        music();
        alarmsets = -2; 
      }
    }
  }
 
  if(alarmsets >= -1)
  {
    delay(1000);
  	alarmsets--;
  }
  if(alarmsets == -1)
  {
    delay(1000);
    alarmsetm--;
   	alarmsets = 59;
  }
  
  if(alarmsetm == -1)
  {
    if(alarmseth >= 1)
    {
      	delay(1000);
    	alarmseth--;
    }
    alarmsetm = 59;
  }
  
  if(alarmseth >=0 && alarmseth <=9)
  {
    lcd.setCursor(7,1);
    lcd.print("0");
    lcd.setCursor(8,1);
    lcd.print(alarmseth);
  }
  else
  {
    lcd.setCursor(7,1);
    lcd.print(alarmseth);
  }
  
  lcd.setCursor(9,1);
  lcd.print(":");
 
  if (alarmsetm >=0 && alarmsetm <=9)
  {
    lcd.setCursor(10,1);
    lcd.print("0");
    lcd.setCursor(11,1);
    lcd.print(alarmsetm);
  }
  else
  {
    lcd.setCursor(10,1);
    lcd.print(alarmsetm);
  }
  
  lcd.setCursor(12,1);
  lcd.print(":");
  
  if(alarmsets >=0 && alarmsets <=9)
  {
    lcd.setCursor(13,1);
    lcd.print("0");
    if(alarmsets >= -1)
    {
      lcd.setCursor(14,1);
      lcd.print(alarmsets);
    }
  }
  else
  {
    if(alarmsets >= -1) 
    {
   	  lcd.setCursor(13,1);
   	  lcd.print(alarmsets);
    }
  }
}

void music() {
  s= s+20;
  for (int j=0; j <2; j++) {
  	for (int thisNote = 0; thisNote < 24; thisNote++) {
      ledRGB();
      float noteDuration = 500/noteDurations[thisNote];
      tone(speakerPin, melody[thisNote],noteDuration);

      float pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      noTone(speakerPin);
  	}
    delay(1000);
  }
}

void ledRGB() {
  analogWrite(redPin, random(255));
  analogWrite(greenPin, random(255));
  analogWrite(bluePin, random(255));
}
