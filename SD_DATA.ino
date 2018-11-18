void SD_checking(){
	lcd_qSprint("SD.....",2,0);
	if (!SD.begin(chipSelect)) {
		Serial.println(F("SD Devive error"));
		SD_alive = false;
	} else {
	}
//		Serial.println("Setup Complete");
}




void do_SD(){                      //序列埠輸出資料(日期、tsys01溫度、tsd305溫度、tsd305目標溫度、CO2、緯度、經度、高度)-----------------

	lcd.setCursor(18,0);
	lcd.print("S");
	delay(10);
//	lcd.write(9);
	
	if(last_day != day){
		last_day = day;
		getFilename(filename);
		File_check_exists();
	}
	myFile = SD.open(filename, FILE_WRITE);
	if (myFile) {
		myFile.print(device_ID);
		myFile.print(",");
		myFile.print(year, DEC);
		myFile.print('/');
		myFile.print(month, DEC);
		myFile.print('/');
		myFile.print(day, DEC);
		myFile.print(',');
		myFile.print(hour, DEC);
		myFile.print(':');
		myFile.print(minute, DEC);
		myFile.print(':');
		myFile.print(second, DEC);
		myFile.print(",");
		data_write_in(temperature,2);
		data_write_in(K_temperature,2);
		data_write_in(pressure,2);
		myFile.print(humidity);
		myFile.print(",");
		myFile.print(valCO2);
		myFile.print(",");
		data_write_in(flat,6);
		data_write_in(flon,6);
//		data_write_in(alti,2);
		data_write_in(gps_number,0);
		if(GPS_check){
			myFile.print("V,");
			GPS_check = false;
		}else{
			myFile.print(",");
		}
		data_write_in(EC_f,2);
		data_write_in(TDS_f,2);
		data_write_in(SAL_f,2);
		data_write_in(GRAV_f,2);
		data_write_in(pH,2);
		myFile.println();
		myFile.close();
	} else {
		Serial.println(F("Unable To Access SD Card"));
		waring();
		SD_alive = false;
	} 
//	lcd.setCursor(18,0);
//	lcd.print(" ");
}
void getFilename(char *filename) {      //File Name Set As : IDYYMMDD.csv !!Warning!! Filename should alway be "8digits".csv
  int temp = (year%100-year%10)/10;
  int ID_10 = device_ID/10;
  int ID_1  = device_ID%10;
  filename[0]  = ID_10		 + '0';
  filename[1]  = ID_1		 + '0';
  filename[2]  = temp		 + '0';
  filename[3]  = year % 10	 + '0';
  filename[4]  = month / 10	 + '0';
  filename[5]  = month % 10	 + '0';
  filename[6]  = day / 10	 + '0';
  filename[7]  = day % 10	 + '0';
  filename[8]  = '.' ;
  filename[9]  = 'c' ;
  filename[10] = 's' ;
  filename[11] = 'v' ;
  return;
}
void File_check_exists(){               //Check wether there is already the same filename's file exsit. If not, creat new one.=======
  if(!SD.exists(filename)){
    myFile = SD.open(filename, FILE_WRITE);
    myFile.println("Device ID,Date,Time,Temperature,K_Temp,Pressure,Humidity,CO2,flat,flon,GPS_number,GPS_Avalibal,Conductivity,TDS,SAL,GRAV,pH");
    myFile.println("ID,YY/MM/DD,HH/MM/SS,Celsius,Celsius,Pa,%,ppm,degree,degree,-,-,µS/cm,ppm,PSU,-,-");
    myFile.close();
  }
}
void data_write_in(float datalog,int num){      //Write in float type data into SD Card=======================================
	if(datalog == 8888){
		myFile.print("Not_Connecting");
	}
	else if(datalog == 9999){
		myFile.print("-9999");
	}
	else{
		myFile.print(datalog,num);
	}
	myFile.print(",");
}
