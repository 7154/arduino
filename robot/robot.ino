//led d13　デジタル13番がLED
//fotr a1　アナログ1番がフォトリフレクタ
//sens a0　アナログ0番が光センサ

void setup(){
		Serial.begin(9600);\\シリアル通信の設定
		pinMode(13,OUTPUT);\\デジタルピン13使用の宣言
}

void loop(){

		Serial.print(":");
		Serial.print(analogRead(0));
		Serial.print(":");
		Serial.println(analogRead(1));
		\\シリアル通信でセンサの値を送信

		if(analogRead(0)<300){\\もし光センサがしきい値以下なら
				digitalWrite(13,LOW);\\LEDを点灯
		}else{
				if(analogRead(1)<243){\\もしフォトリフレクタがしきい値以下なら
						digitalWrite(13,HIGH);\\LEDを点灯
				}if(analogRead(1)>243){\\もしフォトリフレクタがしきい値以上なら
						digitalWrite(13,LOW);\\LEDを消灯
				}
		}
		delay (50);//50msごとに繰り返す
}
