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
double left = 0;//0
double right = 0;//1
double centor = 0;//2

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
double PWM_pow = 75;

//int pri = 0;

void flash(){
		en2 = en1;
		en1 = en;
		en = pad;
		dMv = ((Kp*(en-en1))+(Ki*en)+(Kd*((en-en1)-(en1-en2))));
		Mv = Mv + dMv;
		/*if(pri == 100){
				Serial.print("left:");
				Serial.print(left);
				Serial.print("right:");
				Serial.print(right);
				Serial.print("centor:");
				Serial.println(centor);
				pri = 0;
		}else{
				pri++;
		}*/
}

void setup(){
		//Serial.begin(9600);
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
  	left = analogRead(0);
  	right = analogRead(2);
  	centor = analogRead(1);
    noInterrupts();
    pad=0;
		if(right<alpha){
				pad = 1*(alpha-right);
		}if(left<alpha){
				pad = -1*(alpha-left);
		}
                if(right<alpha && left<alpha){
                                pad = 0;
                }
interrupts();

		digitalWrite(motorA1,HIGH);
		digitalWrite(motorA2,LOW);
		analogWrite(PWM_motA,PWM_pow+(Mv*PWM_pow));
		digitalWrite(motorB1,HIGH);
		digitalWrite(motorB2,LOW);
		analogWrite(PWM_motB,PWM_pow-(Mv*PWM_pow));

}
