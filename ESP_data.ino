void upload_ESP(){
  char INSERT_DATA[] = "%02d/%02d/%02d,%02d:%02d:%02d,%s,%s,%s,%d,%d,%s,%s,%s,%s,%s,%d\r";
  char query[256];
  char temp1[10], temp2[10], temp3[10], temp4[10], temp5[10], temp6[10], temp7[10], temp8[10], temp9[10], temp10[10], temp11[10];
  
  dtostrf(temperature,2,2,temp1);
  dtostrf(K_temperature,2,2,temp2);
  dtostrf(pressure,2,2,temp3);
//  dtostrf(flat,1,2,temp4);
//  dtostrf(flon,1,2,temp5);
//  dtostrf(alti,1,2,temp6);
  dtostrf(EC_f,1,2,temp7);
  dtostrf(TDS_f,1,2,temp8);
  dtostrf(SAL_f,1,2,temp9);
  dtostrf(GRAV_f,1,2,temp10);
  dtostrf(pH,1,3,temp11);
  sprintf(query, INSERT_DATA, year, month, day, hour, minute, second, temp1, temp2, temp3, humidity, valCO2, temp7, temp8, temp9, temp10, temp11,device_ID);
  Serial.print("query = ");
  Serial.println(query);
  ESP8266.print(query);
}

