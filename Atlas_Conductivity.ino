
void measurement_EC(){
	
	while (Atlas_EC.available() > 0) { 
		Atlas_EC.read();
		delay(1);
	}
	
	Atlas_EC.print("R\r");
	
	while(!Atlas_EC.available()){
		delay(1);
	}
	
	while (Atlas_EC.available() > 0) {					//if we see that the Atlas Scientific product has sent a character
		char inchar = (char)Atlas_EC.read();              //get the char we just received
		sensorstring += inchar;								//add the char to the var called sensorstring
		if (inchar == '\r') {								//if the incoming character is a <CR>
		  sensor_string_complete = true;					//set the flag
		}
		delay(1);
//		Serial.println(sensorstring);
	}
	
	
	if (sensor_string_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
		if (isdigit(sensorstring[0]) == false) {          //if the first character in the string is a digit
//			Serial.println(sensorstring);                   //send that string to the PC's serial monitor
	}else{                                             //if the first character in the string is NOT a digit
	  print_EC_data();                                //then call this function 
	}
//	Serial.println(sensorstring);
	sensorstring = "";                                //clear the string
	sensor_string_complete = false;                   //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
	}
}



void print_EC_data(void) {                            //this function will pars the string  

  char sensorstring_array[30];                        //we make a char array
  char *EC;                                           //char pointer used in string parsing
  char *TDS;                                          //char pointer used in string parsing
  char *SAL;                                          //char pointer used in string parsing
  char *GRAV;                                         //char pointer used in string parsing
//  float f_ec;                                         //used to hold a floating point number that is the EC
  
  sensorstring.toCharArray(sensorstring_array, 30);     //convert the string to a char array 
  EC   = strtok(sensorstring_array, ",");               //let's pars the array at each comma
  TDS  = strtok(NULL, ",");                             //let's pars the array at each comma
  SAL  = strtok(NULL, ",");                             //let's pars the array at each comma
  GRAV = strtok(NULL, ",");                             //let's pars the array at each comma
/*
  Serial.print("EC:");                                //we now print each value we parsed separately
  Serial.println(EC);                                 //this is the EC value

  Serial.print("TDS:");                               //we now print each value we parsed separately
  Serial.println(TDS);                                //this is the TDS value

  Serial.print("SAL:");                               //we now print each value we parsed separately
  Serial.println(SAL);                                //this is the salinity value

  Serial.print("GRAV:");                              //we now print each value we parsed separately
  Serial.println(GRAV);                               //this is the specific gravity
  Serial.println();                                   //this just makes the output easier to read
 */ 
    EC_f = atof(EC);                                     //uncomment this line to convert the char to a float
   TDS_f = atof(TDS);
   SAL_f = atof(SAL);
  GRAV_f = atof(GRAV);
}


void flush_EC_serial(){
	while (Atlas_EC.available() > 0) { 
    Atlas_EC.read();
    delay(1);
	}
}


