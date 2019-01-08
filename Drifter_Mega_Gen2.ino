/*
   Drifter Mega2560 Version
   Last Modify 18/12/10
    Adding:Watch Dog
   To Test:Watch Dog
*/



#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <SD.h>
#include <Wire.h>
#include "Seeed_BME280.h"
#include "RTClib.h"
#include <tsys01.h>
#include <Adafruit_MAX31856.h>
#include <Button.h>
#include <EEPROM.h>
#include <Adafruit_SleepyDog.h>

#define SERIAL_BAUD 115200          	//Baud Rate
#define LCD_I2C_ADDRESS 0x27       	//LCD I2C Address
#define initial_data 8888
#define GPS_SERIAL 9600
#define ESP_BAUD 115200


/*========================Things You Should Change================================*/
/**/#define interval 10000           	//Interval								/**/
/**/#define CO2_cali_coeff 1          	//CO2 Calibration Coefficient			/**/
/**/#define valMultiplier 1;			//CO2 Coffiect							/**/
/**/#define sample_times 3.000			//Sample Times For Average				/**/
/*================================================================================*/

unsigned long last_time = 0;		//For Timed Action Group 1
unsigned long last_time2 = 0;		//For Timed Action Group 2
//unsigned long lcd_update_last = 0;

//GPS DATA Parameter=================================================================================
TinyGPS gps;
HardwareSerial &ss = Serial1;							//GPS Using UART Port1
boolean GPS_check = false;
boolean newData   = false;
unsigned short sentences, failed;
float 			flat = initial_data, flon = initial_data, alti = initial_data;
unsigned long    age = initial_data/*, date = initial_data, time = initial_data*/;
unsigned long 	chars;
//unsigned long	start = 0;
int gps_number = 0;
static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void gps_printout();
//GPS DATA Parameter END=============================================================================

//K Type Thermocouple Data Parameter=================================================================
#define MAX31856Select 5								//Max31856 CS pin
float K_temperature = initial_data;
Adafruit_MAX31856 max = Adafruit_MAX31856(MAX31856Select);
//K Type Thermocouple Data Parameter END=============================================================

//Tsys01 Data Parameter==============================================================================
static tsys01 m_tsys01;
float temperature;
boolean connected;
//Tsys01 Data Parameter END==========================================================================

//Atlas Conductivity Data Parameter==================================================================
HardwareSerial &Atlas_EC = Serial2;						//Atlas EC Using UART Port2
//String  inputstring  = "";								//a string to hold incoming data from the PC
String  sensorstring = ""; 								//a string to hold the data from the Atlas Scientific product
//boolean input_string_complete  = false;					//have we received all the data from the PC
boolean sensor_string_complete = false;					//have we received all the data from the Atlas Scientific product
float EC_f , TDS_f, SAL_f, GRAV_f;
//Atlas Conductivity Data Parameter END===============================================================

//Atlas pH Data Parameter=============================================================================
SoftwareSerial Atlas_pH(10, 11);						//Atlas pH Using pin 10,11
//String  inputstring_pH  = "";							//a string to hold incoming data from the PC
String  sensorstring_pH = "";							//a string to hold the data from the Atlas Scientific product
//boolean input_string_pH_complete  = false;				//have we received all the data from the PC
boolean sensor_string_pH_complete = false;				//have we received all the data from the Atlas Scientific product
float pH;
//Atlas pH Data Parameter END=========================================================================

//SD Moudle Data Parameter============================================================================
#define chipSelect 4									//SD Moudle CS pin
File myFile;
char filename[] = "00000000.csv";
boolean SD_alive = true;
const int logger_size = 100;
char event_logger[logger_size];
int current_pos = 0;
//SD Moudle Data Parameter END========================================================================

//CO2 Data Parameter==================================================================================
HardwareSerial &K_30_Serial = Serial3;					//CO2 Using UART Port3
int valCO2 = initial_data;
byte  readCO2[] = {0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25};
byte response[] = {0, 0, 0, 0, 0, 0, 0};
//CO2 Data Parameter END==============================================================================

//RTC Data Parameter==================================================================================
RTC_DS3231 RTC;
int year, month, day, last_day;
int hour, minute, second;
//RTC Data Parameter END==============================================================================

//BME280 Data Parameter===============================================================================
BME280 bme280;
float pressure;
int humidity;
float pressure_in_atm;
//BME280 Data Parameter END===========================================================================

//Button Data Parameter===============================================================================
Button EC_dry_cali   = Button(24);
Button EC_low_cali   = Button(25);
Button EC_high_cali  = Button(26);
Button pH_4_cali	 = Button(27);
Button pH_7_cali	 = Button(28);
Button pH_10_cali	 = Button(29);
Button k_cali_btn	 = Button(30);
int btn_command = 0;
//Button Data Parameter END===========================================================================


//EEPROM Data Parameter================================================================================
int device_ID = 0 ;
float k_cal = 0.00f;
int IDAddress = 0;
int k_cal_addr = sizeof(int);
//int device_ID_temp = 1 ;
//float k_cal_temp = 0.30;
//EEPROM Data Parameter END============================================================================

//LCD Data Parameter===================================================================================
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, 21, 4);
boolean lcd_backlight_status = false;
boolean RTC_alive = true;

byte EC_Stand[8] = {
  0b11100,
  0b10000,
  0b11100,
  0b10000,
  0b11100,
  0b00111,
  0b00100,
  0b00111
};
byte pH_Stand[8] = {
  0b11100,
  0b10100,
  0b11100,
  0b10000,
  0b10101,
  0b00111,
  0b00101,
  0b00101
};
byte SD_Fatal[8] = {
  0b00101,
  0b00010,
  0b00101,
  0b01100,
  0b10000,
  0b01000,
  0b00100,
  0b11000
};
byte RTC_Fatal[8] = {
  0b00101,
  0b00010,
  0b00101,
  0b00000,
  0b11100,
  0b01000,
  0b01000,
  0b01000
};
byte tsys01_icon[8] = {
  0b00001,
  0b11111,
  0b00001,
  0b00000,
  0b10010,
  0b10101,
  0b10101,
  0b01001
};
byte k_icon[8] = {
  0b11111,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00001,
  0b11111,
  0b00001
};
byte ATM_icon[8] = {
  0b11110,
  0b01001,
  0b01001,
  0b11110,
  0b00000,
  0b00001,
  0b11111,
  0b00001
};
byte RH_icon[8] = {
  0b11111,
  0b00101,
  0b01101,
  0b10010,
  0b00000,
  0b11111,
  0b00100,
  0b11111
};
//LCD Data Parameter END===============================================================================


//tone Data Parameter===================================================================================
#define buzzerpin 44
#define notice_freq 50
#define notice_duri 100
#define waring_freq 50
#define waring_duri 1000
//Buzzer Data Parameter END===============================================================================


//Watch Dog============================
int watchdogTimer = 5000;
//Watch Dog End========================

//ESP 8266=============================
SoftwareSerial ESP8266(12, 13);
int ESP_times = 0;
//=====================================

void setup() {
  Wire.begin();
  Serial.begin(SERIAL_BAUD);
  ss.begin(GPS_SERIAL);
  ESP8266.begin(ESP_BAUD);
  max.begin();
  max.setThermocoupleType(MAX31856_TCTYPE_K);		//Set the type of Thermocouple

  //	  EEPROM.put(IDAddress, device_ID_temp);
  //	  EEPROM.put(k_cal_addr, k_cal_temp);

  EEPROM.get(IDAddress, device_ID);					//Get Device ID from EEPROM
  EEPROM.get(k_cal_addr, k_cal);					//Get Thermocouple Calibration Data from EEPROM

  Serial.print("Device ID = ");
  Serial.println(device_ID, 2);
  Serial.print("K Calibrate = ");
  Serial.println(k_cal, 2);

  EC_dry_cali.begin();
  EC_low_cali.begin();
  EC_high_cali.begin();
  pH_4_cali.begin();
  pH_7_cali.begin();
  pH_10_cali.begin();
  k_cali_btn.begin();
  pinMode(buzzerpin, OUTPUT);

  Atlas_EC.begin(9600);                	            //set baud rate for the software serial port to 9600
  //inputstring.reserve(10);                            //set aside some bytes for receiving data from the PC
  sensorstring.reserve(30);                           //set aside some bytes for receiving data from Atlas Scientific product

  Atlas_pH.begin(9600);                               //set baud rate for the software serial port to 9600
  //inputstring_pH.reserve(10);                         //set aside some bytes for receiving data from the PC
  sensorstring_pH.reserve(30);                        //set aside some bytes for receiving data from Atlas Scientific product

  m_tsys01.begin();

  K_30_Serial.begin(9600);
  //	cln_event_logger();

  lcd.init();
  { /*LCD Create Custom Char==============================================================*/

    lcd.createChar(0, EC_Stand);
    lcd.createChar(1, pH_Stand);
    lcd.createChar(2, SD_Fatal);
    lcd.createChar(3, RTC_Fatal);
    lcd.createChar(4, tsys01_icon);
    lcd.createChar(5, k_icon);
    lcd.createChar(6, ATM_icon);
    lcd.createChar(7, RH_icon);
  }

  { /*Initial LCD Output==========================================================*/
    lcd.backlight();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Multi-Function Water");
    lcd.setCursor(0, 1);
    lcd.print("Data Collecting Syst");
    lcd.setCursor(0, 3);
    lcd.print("Device ID = ");
    lcd.print(device_ID);
    delay(5000);
    lcd.clear();

    /*Watch Dog Init*/
    Watchdog.enable(watchdogTimer);
    Watchdog.reset();

    /*Start Checking BME280*/
    if (!bme280.init()) {
      Serial.println("BME280 Device error!");
    }

    //    /*Start Checking RTC*/
    //    Serial.println("RTC Checking...");
    RTC_check();
    //    /*Start Checking SD Module*/
    //    Serial.print("SD Card Checking.....\t");
    SD_checking();

    if (SD_alive && RTC_alive) {
      Serial.println("SD, RTC Pass. System Start");
    }
      //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  /*Initial Parameter==================================================*/
  update_time_info();
  getFilename(filename);
  File_check_exists();
  last_day   = day;
  last_time  = millis();
  last_time2 = millis();
  //  lcd_update_last = millis();
  tsys01_get();					//Get TSYS01 Data								 [TSYS01]				(temperature)
  measure_BME280();				//Get BME280 Data								 [BME280]				(pressure,humidity)
  measure_CO2();				//Get CO2 Data									 [CO2_READ]				(valCO2)
  update_K_temp();				//Get Thermacouple Temperature  				 [Thermocouple]			(K_temperature)
  send_temperature();			//Set K_Temperature to Atlas EZO and pH			 [Thermocouple]
  measurement_EC();				//Get Conductivity 								 [Atlas_ECuctivity]		(EC_f,TDS_f,SAL_f,GRAV_f)
  measurement_pH();				//Get pH Data									 [Atlas_pH]				(pH)
  LCD_update_main();			//Update LCD Data								 [LCD]
  do_SD();						//Write Data into SD Card						 [SD_DATA]
  serial_print_data();			//Print Data Out to The Serial					 [SERIAL_PRINT]
}

void loop() {
  { /*Reset Watchdog Timer=======================================*/
    Watchdog.reset();
  }

  { /*Call in Every Loop ====================================================================*/
    //gps_new_get();					//GPS Function									 [GPS_DATA]
    button_action();				//Check weather button is pressed				 [Button]
  }

  { /*Update By Interval Set in "interval" ==================================================*/
    while (millis() - last_time >= interval)
    {
      /*========================*/
      last_time  = millis();		//Set Time for Time Action
      last_time2 = millis();		//Set Time for Time Action
      /*========================*/
      tsys01_get();					//Get TSYS01 Data								 [TSYS01]				(temperature)
      measure_BME280();				//Get BME280 Data								 [BME280]				(pressure,humidity)
      measure_CO2();				//Get CO2 Data									 [CO2_READ]				(valCO2)
      update_K_temp();				//Get Thermacouple Temperature  				 [Thermocouple]			(K_temperature)
      send_temperature();			//Set K_Temperature to Atlas EZO and pH			 [Thermocouple]
      measurement_EC();				//Get Conductivity 								 [Atlas_ECuctivity]		(EC_f,TDS_f,SAL_f,GRAV_f)
      measurement_pH();				//Get pH Data									 [Atlas_pH]				(pH)
      LCD_update_main();			//Update LCD Data								 [LCD]
      do_SD();						//Write Data into SD Card						 [SD_DATA]
      serial_print_data();			//Print Data Out to The Serial					 [SERIAL_PRINT]

      ESP_times ++;
      if(ESP_times == 3 && RTC_alive){
        upload_ESP();
        ESP_times = 0;
      }
      
    }
  }
  { /*Update By Interval of 1s ==============================================================*/
    while (millis() - last_time2 >= 1000)
    {
      /*========================*/
      last_time2 = millis();		//Set Time for Time Action
      /*========================*/
      gps_new_get();          //GPS Function                   [GPS_DATA]
      update_time_info();			//Get New Time  								 [RTC]
      //      tsys01_get();					//Get TSYS01 Data								 [TSYS01]				(temperature)
      //      measure_BME280();				//Get BME280 Data								 [BME280]				(pressure,humidity)
      //      update_K_temp();				//Get Thermacouple Temperature  				 [Thermocouple]			(K_temperature)
      //      LCD_update_main();			//Update LCD Data								 [LCD]

    }
  }
}
