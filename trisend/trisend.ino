#include <MsTimer2.h>
//モータの出力設定
//モータ1
const double motorA1 = 8;
const double motorA2 = 7;
const double PWM_motA = 10;
//モータ2
const double motorB1 = 4;
const double motorB2 = 5;
const double PWM_motB = 9;

//　フォトトランジスタの入力設定
const int sensorA = 0;//2;左この値がおかしい
const int sensorB = 1;//3;右
const int sensorC = 2;//;中この値がおかしい
//　センサから読み取った値（analog）
double valA = 0;
double valB = 0;
double valC = 0;

//　閾値
//センサの閾値
double alpha = 500;//100;

//制御の目標値
double target = 0;
//PID制御値
//Kp
double Kp = 0.7;
//Ki
double Ki = 0.0001;
//Kd
double Kd = 0.7;
//前回と前々回の操作量
double Mv = 0;
//今回操作量偏差
double dMv = 0;
//今回、前回、前々回の偏差
double en = 0;
double en1 = 0;
double en2 = 0;
//判定
double pad = 0;

//PWMの出力(255が最大,130〜200程度が調度良い)
double PWM_pow = 100;

int pri = 0;

void flash(){
		en2 = en1;
		en1 = en;
		en = pad;
		dMv = ((Kp*(en-en1))+(Ki*en)+(Kd*((en-en1)-(en1-en2))));
		Mv = Mv + dMv;
		if(pri == 10){
				Serial.print("A:");
				Serial.print(valA);
				Serial.print("B:");
				Serial.print(valB);
				Serial.print("C");
				Serial.println(valC);
				pri = 0;
		}else{
				pri++;
		}
}

void setup(){
		Serial.begin(9600);
		pinMode(motorA1,OUTPUT);
		pinMode(motorA2,OUTPUT);
		pinMode(motorB1,OUTPUT);
		pinMode(motorB2,OUTPUT);
		pinMode(PWM_motA,OUTPUT);
		pinMode(PWM_motB,OUTPUT);
		MsTimer2::set(5,flash);
		MsTimer2::start();
}

void loop(){
  	valA = analogRead(sensorA);
  	valB = analogRead(sensorB);
  	valC = analogRead(sensorC);
    noInterrupts();
    pad=0;
		if(valB<alpha){
				pad = 1;
		}if(valA<alpha){
				pad = -1;
		}if(valB<alpha && valA<alpha){
        pad = 0;
    }if(valC<alpha){
				pad = pad*1.5;
		}
interrupts();

double Mvv = 0;
if(Mv>1){
  Mvv=1;
}else if(Mv<-1){
  Mvv=-1;
}else{
  Mvv=Mv;
}
		digitalWrite(motorA1,HIGH);
		digitalWrite(motorA2,LOW);
		analogWrite(PWM_motA,PWM_pow+(Mvv*PWM_pow));
		digitalWrite(motorB1,HIGH);
		digitalWrite(motorB2,LOW);
		analogWrite(PWM_motB,PWM_pow-(Mvv*PWM_pow));
}
