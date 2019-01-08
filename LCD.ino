void lcd_qSprint(String s, int column ,int row){
  lcd.setCursor(column,row);
  lcd.print(s);
}

void lcd_qFprint(float k ,float num, int column, int row){
  lcd.setCursor(column,row);
  lcd.print(k,num);
}


void LCD_update_main(){

	lcd.clear();
//	char data[10];
	
{/*Row 0*/
    update_time_info();

	lcd.setCursor(17,0);
    if(!RTC_alive)		{	lcd.write(3);	}

    lcd.setCursor(18,0);
    if(!SD_alive)		{	lcd.write(2);	}
    
	lcd.setCursor(19,0);
	if(GPS_check)		{	lcd.print("G");	GPS_check = false;}
		else			{	lcd.print("-");	}
}
{/*Row 1*/
    lcd.setCursor(17,1);
    lcd.write(7);
    char humi_data[2];
    sprintf(humi_data,"%02d%",humidity);
    lcd_qSprint(humi_data,18,1);
}
{/*Row 2*/
	
    lcd.setCursor(0,2);
//    lcd.write(16);
    char co2_data[5];
    sprintf(co2_data,"%05d",valCO2);
    lcd_qSprint(co2_data,0,2);

    lcd.setCursor(7,2);
    lcd.write(6);
    lcd_qFprint(pressure_in_atm,3,8,2);

	lcd.setCursor(14,2);
    lcd.write(4);
    lcd_qFprint(temperature,2,15,2);
}
{/*ROW 3*/
	lcd.setCursor(0,3);
    lcd.write(byte(0));
    lcd_qFprint(SAL_f,2,1,3);

    lcd.setCursor(7,3);
    lcd.write(1);
    lcd_qFprint(pH,3,8,3);

    lcd.setCursor(14,3);
    lcd.write(5);
    lcd_qFprint(K_temperature,2,15,3);

}
  }

