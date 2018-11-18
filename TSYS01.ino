void tsys01_get(){
  connected = m_tsys01.is_connected();
  float tsys01_temp = 0.00;
  
  if (connected) {
    for(int i = 0; i < sample_times; i++){
    	m_tsys01.read_temperature(&temperature);
    	tsys01_temp += temperature;
    }

    temperature = tsys01_temp/sample_times;

  } else {
    temperature = 99.99;
  }
}

