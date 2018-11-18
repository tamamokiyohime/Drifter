void measure_BME280(){
	float press_temp = 0;
	float humid_temp = 0;
	for(int i = 0; i<sample_times; i++){
		press_temp += bme280.getPressure();
		humid_temp += bme280.getHumidity();
	}
	
	pressure = press_temp/sample_times;
	humidity = humid_temp/sample_times;
	
//  pressure = bme280.getPressure();
//  humidity = bme280.getHumidity();
  pressure_in_atm = pressure/101325.000;
}

