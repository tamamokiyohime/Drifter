void buzzer_check(){
	if(buzzer_act && millis() - buzzertime > duration){
		
			buzzer_act = false;
			duration = 0;
			digitalWrite(buzzerpin, LOW);
		
	}
}

void buzzer(int buzzer_duration){
//	if(!buzzer_act){
		buzzertime = millis();
		duration = buzzer_duration;
		buzzer_act = true;
		digitalWrite(buzzerpin, HIGH);
//	}
}

