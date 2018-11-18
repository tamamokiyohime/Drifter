void measurement_pH(){
	
	while (Atlas_pH.available() > 0) { 
		Atlas_pH.read();
		delay(1);
	}
	
	Atlas_pH.print("R\r");
	
	while(!Atlas_pH.available()){
		delay(1);
	}
	
	while (Atlas_pH.available() > 0) {					//if we see that the Atlas Scientific product has sent a character
		char inchar = (char)Atlas_pH.read();				//get the char we just received
		sensorstring_pH += inchar;							//add the char to the var called sensorstring_pH
		if (inchar == '\r') {								//if the incoming character is a <CR>
		  sensor_string_pH_complete = true;					//set the flag
		}
		delay(1);
	}
	
	
	if (sensor_string_pH_complete == true) {            //if a string from the Atlas Scientific product has been received in its entirety
		if (isdigit(sensorstring_pH[0])) { 
			pH = sensorstring_pH.toFloat();}
			sensorstring_pH = "";                       //clear the string
			sensor_string_pH_complete = false;          //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
	}

}




void flush_pH_serial(){
	while (Atlas_pH.available() > 0) { 
    Atlas_pH.read();
    delay(1);
	}
}

