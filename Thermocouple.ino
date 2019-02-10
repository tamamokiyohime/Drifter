void update_K_temp(){
	
//	float k_temp = 0;
	
//	for(int i = 0; i < sample_times; i++){
//		k_temp += max.readThermocoupleTemperature() - k_cal;
//	}
//
//	K_temperature = k_temp/sample_times;
	
  K_temperature = max.readThermocoupleTemperature();
  K_temperature = K_temperature + k_cal;    //calabration
//  K_temperature = 25.0;
}


void send_temperature(){
	String s = "";
	s+="T,";
	s+=K_temperature;
	s+="\r";
	
	
	while(Atlas_EC.available()){
	    Atlas_EC.read();
	    delay(1);
	}
	Atlas_EC.print(s);
	  
	while(Atlas_pH.available()){
	    Atlas_pH.read();
	    delay(1);
	}
	  
	Atlas_pH.print(s);
  
}


