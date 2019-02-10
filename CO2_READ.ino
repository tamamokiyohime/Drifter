void measure_CO2(){     //CO2鞈���撘�---------------------------------------------------------------------------------------------
  sendRequestment(readCO2);
  valCO2 = getValue(response);
 }
void sendRequestment(byte packet[]){        //CO2鞈���撘�-------------------------------------------------------------------------
  while (!K_30_Serial.available()) //keep sending request until we start to get a response
  {
    K_30_Serial.write(readCO2, 7);
    delay(50);
  }

  int timeout = 0; //set a timeoute counter
  while (K_30_Serial.available() < 7 ) //Wait to get a 7 byte response
  {
    timeout++;
    if (timeout > 10) //if it takes to long there was probably an error
    {
      while (K_30_Serial.available()) //flush whatever we have
        K_30_Serial.read();

      break; //exit and try again
    }
    delay(50);
  }

  for (int i = 0; i < 7; i++)
  {
    response[i] = K_30_Serial.read();
  }
}
unsigned long getValue(byte packet[]){      //CO2鞈���撘�-------------------------------------------------------------------------
  int high = packet[3]; //high byte for value is 4th byte in packet in the packet
  int low = packet[4]; //low byte for value is 5th byte in the packet
  unsigned long val = high * 256 + low; //Combine high byte and low byte with this formula to get value
  return val * valMultiplier;
}

