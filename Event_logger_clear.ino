void cln_event_logger(){
	if(current_pos > 0){
		for(int i = 0; i < logger_size; i++){
			event_logger[i] = "";
		}
		current_pos = 0;
		Serial.println("Ecent Cls = 0");
	}
	Serial.println("event cls");
}

void event_write(String S){
	Serial.print("s.lenghth = ");
	Serial.println(S.length());
//	if(current_pos + S.length() < logger_size){
//		for(int k = 0 ; k <= S.length(); k++){
//			event_logger[current_pos + k] += S[k];
//			Serial.print(event_logger[current_pos + k]);
//		}
//		current_pos += S.length() + 1;
//	}
}

