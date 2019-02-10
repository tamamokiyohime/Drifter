void serial_print_data(){                      //摨��撓�鞈��(����sys01皞怠漲�sd305皞怠漲�sd305�璅澈摨艾�O2�楝摨艾��漲��漲)-----------------
    char serialDATE[8];
    
    sprintf(serialDATE,"%02d/%02d/%02d",year,month,day);
    Serial.print(serialDATE);
    delay(50);
    Serial.print("\t");
    sprintf(serialDATE,"%02d:%02d:%02d",hour,minute,second);
    Serial.print(serialDATE);
    delay(50);
  	Serial.print("\t");
	data_serial_out(temperature,2);
	data_serial_out(K_temperature,2);
	data_serial_out(pressure,2);
	Serial.print(humidity);
	delay(7);
	Serial.print(F("\t"));
	delay(2);
	Serial.print(valCO2);
	delay(8);
	Serial.print(F("\t"));
	delay(2);
	data_serial_out(flat,6);
	data_serial_out(flon,6);
	data_serial_out(alti,2);
	data_serial_out(EC_f,2);
	data_serial_out(TDS_f,2);
	data_serial_out(SAL_f,2);
	data_serial_out(GRAV_f,2);
	data_serial_out(pH,3);
	Serial.println();
   
}


void data_serial_out(float datalog, int num){    //摨��撓�(float�)===================================================
	if(datalog == 8888){
		Serial.print("-----");
	}
	else if(datalog == 9999){
		Serial.print(F("ERROR"));
	}
	else{
		Serial.print(datalog,num);
	}
	delay(50);
	Serial.print(F("\t"));
	delay(1);
}

