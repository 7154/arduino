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
double alpha = 400;//100;

//PWMの出力(255が最大,130〜200程度が調度良い)
double PWM_pow = 200;


void setup(){
		pinMode(motorA1,OUTPUT);
		pinMode(motorA2,OUTPUT);
		pinMode(motorB1,OUTPUT);
		pinMode(motorB2,OUTPUT);
		pinMode(PWM_motA,OUTPUT);
		pinMode(PWM_motB,OUTPUT);
}

void loop(){
  	left = analogRead(0);
  	right = analogRead(1);
  	centor = analogRead(2);
		if(left<alpha){
				if(right>alpha){
						digitalWrite(motorA1,HIGH);
						digitalWrite(motorA2,LOW);
						digitalWrite(motorB1,LOW);
						digitalWrite(motorB2,LOW);
						analogWrite(PWM_motA,PWM_pow);
						analogWrite(PWM_motB,PWM_pow);
				}
				if(right<alpha){
						digitalWrite(motorA1,HIGH);
						digitalWrite(motorA2,LOW);
						digitalWrite(motorB1,HIGH);
						digitalWrite(motorB2,LOW);
						analogWrite(PWM_motA,PWM_pow);
						analogWrite(PWM_motB,PWM_pow);
				}
		}
		if(left>alpha){
				if(right<alpha){
						digitalWrite(motorA1,LOW);
						digitalWrite(motorA2,LOW);
						digitalWrite(motorB1,HIGH);
						digitalWrite(motorB2,LOW);
						analogWrite(PWM_motA,PWM_pow);
						analogWrite(PWM_motB,PWM_pow);
				}
		}
		if(left>alpha){
				if(right>alpha){
						digitalWrite(motorA1,HIGH);
						digitalWrite(motorA2,LOW);
						digitalWrite(motorB1,HIGH);
						digitalWrite(motorB2,LOW);
						analogWrite(PWM_motA,PWM_pow);
						analogWrite(PWM_motB,PWM_pow);
				}
		}
}
