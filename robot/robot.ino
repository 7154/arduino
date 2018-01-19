//led d13
//fotr a1
//sens a0

void setup(){
		Serial.begin(9600);
		pinMode(13,OUTPUT);
}

void loop(){
		Serial.print(":");
		Serial.print(analogRead(0));
		Serial.print(":");
		Serial.println(analogRead(1));
		if(analogRead(0)<300){
				digitalWrite(13,LOW);
		}else{
				if(analogRead(1)<243){
						digitalWrite(13,HIGH);
				}if(analogRead(1)>243){
						digitalWrite(13,LOW);
				}
		}
		delay (50);
}
