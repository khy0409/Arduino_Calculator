#include <LiquidCrystal.h> //라이브러리 추가
#include <Keypad.h>

#define ROWS 4 //row값에 들어갈 배열 길이(가로)
#define COLS 4 //col값에 들어갈 배열 길이(세로)

LiquidCrystal lcd{13, 12, 11, 10, 9, 8}; //lcd 판 핀 번호 설정

char customKey; //costomKey라는 이름의 캐릭터형 변수 설정(받아지는 값 넣을 변수)

char keys[ROWS][COLS] = { //keys라는 배열과 안에 들어가는 값 설정(4*4)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {14, 15, 7, 6}; //keypad row 핀 값 설정
byte colPins[COLS] = {5, 4, 3, 2}; //keypad col 핀 값 설정

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

double NUM1 = 0; //첫번째 숫자 변수 선언
double NUM2 = 0; //두번째 숫자 변수 선언
double RESULT = 0; //결과값 변수 선언
char cal;

void setup() {
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);

  Serial.begin(9600); //포트 속소 9600으로 설정
  lcd.begin(16, 2); //lcd 화면 크기 설정(16*2)
  lcd.clear(); //lcd 화면 지우기
  lcd.setCursor(0, 0); //0번째 줄 0번째 셀부터 입력
}

void loop() {
  customKey = customKeypad.getKey(); //customKeypad 변수를 customKey에 저장
  //키 입력받음
  operation1(); //첫번째 수 입력받는 함수
  Operator(); //연산기호 출력하는 함수
  operation2(); //두번째 수 입력받는 함수
  Calculate(); //실질적으로 연산하는 함수

  if(customKey == '#') {
    lcd.setCursor(0, 2);
    lcd.print("= ");
    lcd.print(RESULT);
  }
}

void Cleaning() {
  NUM1 = 0;
  NUM2 = 0;
  RESULT = 0;
  lcd.clear();
  cal = NULL;
}

long operation1() {
  while(1) {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9') {
      NUM1 = NUM1 * 10 + (customKey - '0');
      lcd.print(customKey);
    }

    if(customKey == 'A') break;
    else if(customKey == 'B') break;
    else if(customKey == 'C') break;
    else if(customKey == 'D') break;
    else if(customKey == '*') Cleaning();
  }
  return NUM1;
}

long operation2() {
  while(1) {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9') {
      NUM2 = NUM2 * 10 + (customKey - '0');
      lcd.print(customKey);
    }
    
    if(customKey == '#') break;
    else if(customKey == '*') Cleaning();
  }
  return NUM2;
}

void Calculate() {
  switch(cal) {
    case 'A' :
    RESULT = NUM1 + NUM2;
    break;
    case 'B' :
    RESULT = NUM1 - NUM2;
    break;
    case 'C' :
    RESULT = NUM1 * NUM2;
    break;
    case 'D' :
    RESULT = NUM1 / NUM2;
    break;
  }
}

void Operator() {
  switch(customKey) {
    customKey = customKeypad.getKey();
    case 'A' :
    lcd.print("+");
    cal = 'A';
    break;
    case 'B' :
    lcd.print("-");
    cal = 'B';
    break;
    case 'C':
    lcd.print("*");
    cal = 'C';
    break;
    case 'D':
    lcd.print("/");
    cal = 'D';
    break;
  }
}