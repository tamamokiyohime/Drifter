

void gps_new_get(){
  

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 100;)
//if(millis() - start >1000)
  {
    while (ss.available())
    {
      char c = ss.read();
//      Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    gps.f_get_position(&flat, &flon, &age);
    alti = gps.f_altitude();
    gps_number = gps.satellites();
    GPS_check = true;
  }
  
  gps.stats(&chars, &sentences, &failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
}
