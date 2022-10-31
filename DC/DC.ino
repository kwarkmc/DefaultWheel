#include <SoftwareSerial.h>
//BLUETOOTH 모듈 RXD, TXD 설정
#define BT_RXD 8
#define BT_TXD 7

//DC MOTOR 설정
#define ENABLE_B  4  
#define IN3_B  6   
#define IN4_B  5   

//모터 스피드 PWM 설정
byte speedDC = 255;
 
//모터 엔코더 핀 설정
const int encoderPinA = 2;
const int encoderPinB = 3;

int encoderPos = 0;


SoftwareSerial bluetooth(BT_RXD, BT_TXD);

//모터 엔코더 회전 방향 설정
void doEncoderA(){ // 빨녹일 때
//  if(digitalRead(encoderPinA)==digitalRead(encoderPinB)) // 같으면
//    encoderPos++; // 정회전
//  else // 다르면
//    encoderPos--; // 역회전
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;
  Serial.print("A   ");
  Serial.println(encoderPos);
}

void doEncoderB(){ // 보파일 때
//  if(digitalRead(encoderPinA)==digitalRead(encoderPinB)) // 같으면
//    encoderPos--; // 역회전
//  else // 다르면
//    encoderPos++; // 정회전
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;
  Serial.print("B   ");
  Serial.println(encoderPos);
}


void setup(){
  //블루투스 통신 보드레이트 설정
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  //모터 핀모드 설정
  pinMode(ENABLE_B,OUTPUT);  
  pinMode(IN3_B,OUTPUT);  
  pinMode(IN4_B,OUTPUT);  

}

//모터 스피트 제어 함수
void motor_speed(int spd)  
{  
  analogWrite(ENABLE_B,spd);  
}  

//모터 행동 제어 함수
void motor_dir(int dir)  
{  
  if ( dir == 0 ) {  // forward   
     digitalWrite(IN3_B,HIGH);  
     digitalWrite(IN4_B,LOW);  
     analogWrite(ENABLE_B, speedDC);
  }  
  /*else if ( dir == 1 ) { // turn right  
     digitalWrite(IN3_B,LOW);  
     digitalWrite(IN4_B,HIGH);  
  }  
  else if ( dir == 2 ) { // turn left  
     digitalWrite(IN3_B,HIGH);  
     digitalWrite(IN4_B,LOW);  
  }    */
  else if ( dir == 4 ) { // backward  
     digitalWrite(IN3_B,LOW);  
     digitalWrite(IN4_B,HIGH);  
     analogWrite(ENABLE_B, speedDC);
  }     
  
  else if (dir == 10) { //stop
    digitalWrite(IN3_B, LOW);
    digitalWrite(IN4_B, LOW);
  }
  
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
 
  Serial.begin(115200);

}  


void loop(){
  
    if(bluetooth.available()){
      Serial.write(bluetooth.read());
      }
      
    if(Serial.available()){
      bluetooth.write(Serial.read());
    }
    
    //char val = bluetooth.read(); 
    char val = '1';
    if(val == '1') //go_forward
    {
      motor_dir(0);
      Serial.println(10);
    }
    if(val == '2') //go_back
    {
      motor_dir(4);
      Serial.println(100);
    }

    if(val == '3') // stop
    {
      motor_dir(10);
      Serial.println(0);
    }
    
  }
 
