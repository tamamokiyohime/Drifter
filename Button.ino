void button_action(){
	
	if(EC_dry_cali.pressed())	{		btn_command = 1;	}
	if(EC_low_cali.pressed())	{		btn_command = 2;	}
	if(EC_high_cali.pressed())	{		btn_command = 3;	}
	if(pH_4_cali.pressed())		{		btn_command = 4;	}
	if(pH_7_cali.pressed())		{		btn_command = 5;	}
	if(pH_10_cali.pressed())	{		btn_command = 6;	}
	if(k_cali_btn.pressed())	{		btn_command = 7;	}
	
	if(btn_command > 0){
		update_K_temp();
		send_temperature();
		lcd.setCursor(0,1);
		lcd.print("                 ");
		notice();
				
		switch(btn_command){
			case 1:
			flush_EC_serial();
			Atlas_EC.print("Cal,dry\r");
			Serial.println("Atlas EC \"Dry\" Calibration");
			lcd.setCursor(1,3);
			lcd.print("-Dry ");
			lcd.setCursor(0,1);
			lcd.print("EC Dry Cal");
//			event_write("Cal-EC Dry");
			break;
			
			case 2:
			flush_EC_serial();
			Atlas_EC.print("Cal,low,12880\r");
			Serial.println("Atlas EC \"LOW\" Calibration (12880)");
			lcd.setCursor(1,3);
			lcd.print("-Low ");
			lcd.setCursor(0,1);
			lcd.print("EC Low Cal 12.8k");
//			event_write("Cal-EC Low");
			break;
			
			case 3:
			flush_EC_serial();
			Atlas_EC.print("Cal,high,80000\r");
			Serial.println("Atlas EC \"HIGH\" Calibration (80000)");
			lcd.setCursor(1,3);
			lcd.print("-High");
			lcd.setCursor(0,1);
			lcd.print("EC High Cal 80k");
//			event_write("Cal-EC High");
			break;
			
			case 4:
			flush_pH_serial();
			Atlas_pH.print("Cal,mid,7.0\r");
			Serial.println("Atlas pH \"MID\" Calibration (7.0)");
			lcd.setCursor(8,3);
			lcd.print("-Mid ");
			lcd.setCursor(0,1);
			lcd.print("pH7.0 Mid Cal");
//			event_write("Cal-pH Mid");
			break;
			
			case 5:
			flush_pH_serial();
			Atlas_pH.print("Cal,low,4.0\r");
			Serial.println("Atlas pH \"LOW\" Calibration (4.0)");
			lcd.setCursor(8,3);
			lcd.print("-Low ");
			lcd.setCursor(0,1);
			lcd.print("pH4.0 Low Cal");
//			event_write("Cal-pH Low");
			break;
			
			case 6:
			flush_pH_serial();
			Atlas_pH.print("Cal,high,10.0\r");
			Serial.println("Atlas pH \"HIGH\" Calibration (10.0)");
			lcd.setCursor(8,3);
			lcd.print("-High");
			lcd.setCursor(0,1);
			lcd.print("pH10.0 High Cal");
//			event_write("Cal-pH High");
			break;
			
			case 7:
			K_temperature = max.readThermocoupleTemperature();
			k_cal = 25.00 - K_temperature;
			EEPROM.put(k_cal_addr, k_cal);
			Serial.print("Thermocouple Temperature Calibration, Value = ");
			Serial.println(k_cal);
			lcd.setCursor(15,3);
			lcd.print("-S25.");
			lcd.setCursor(0,1);
			lcd.print("K Cal to ");
			lcd_qFprint(k_cal,2,9,1);
//			event_write("Cal-k");
			break;
		}
		delay(50);
		
	}
	btn_command = 0;
}

