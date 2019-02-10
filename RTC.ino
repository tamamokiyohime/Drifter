void RTC_check(){
//  boolean pass_check = true;
  if (!RTC.begin()) {
    Serial.println(F("RTC Not Found"));
//    pass_check = false;
    RTC_alive = false;
    waring();
  }
  if (RTC.lostPower()){
    Serial.println(F("!!!RTC TIME ERROW!!!.... Connect to PC to Reset"));
//    pass_check = false;
    RTC_alive = false;
    waring();
    //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));         //<<<<Uncomment to Set Time Via PC
  }
  if(RTC_alive){
  }
}


void update_time_info(){
	DateTime now = RTC.now();
	year = now.year();  month = now.month();   day = now.day();
	hour = now.hour();  minute = now.minute(); second = now.second();
	char time_format[18];
	int temp_year = year %100;
	sprintf(time_format,"%02d/%02d/%02d %02d:%02d:%02d",temp_year,month,day,hour,minute,second);
	lcd_qSprint(time_format,0,0);
	lcd.setCursor(18,0);
	if(!SD_alive)		{	lcd.write(2);	}
	else {lcd.print(" ");}
}


