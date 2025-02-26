/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/Mohamed/Documents/SFG/NEWFOL~1/project_code.ino"
// This #include statement was automatically added by the Particle IDE.
#include <Grove_LCD_RGB_Backlight.h>

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
void setup();
void loop();
int temp_reading();
int soil_reading();
#line 8 "c:/Users/Mohamed/Documents/SFG/NEWFOL~1/project_code.ino"
SYSTEM_MODE(AUTOMATIC);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

rgb_lcd lcd;

const int colorR = 0;
const int colorG = 0;
const int colorB = 0;

//For the Temperature Sensor
int tempPin = A0;
double tempC = 0.0; 
double targetTemp = 0.0;
double curr_temp = 0.0;

//moisture Sensor
int moistSensor = D7;
int analog_sensor = A5;
int data;
int moisture_reading;


// setup() runs once, when the device is first turned on
void setup() {
      // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("Temp:");
    
    lcd.setCursor(0, 1);
    
    lcd.print("Water:");
    //other temperature sensor setup
    pinMode(tempPin, INPUT);

    //Moistrue Sensor
    pinMode(moistSensor, OUTPUT);
    
    Serial.begin(9600);
    
    //these connect the functions to the cloud
    Particle.variable("CF_temp", curr_temp);
    Particle.variable("CF_soil_reading", moisture_reading);
    
    
    delay(1000);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(6, 0);
    // print the number of seconds since reset:
    lcd.print(temp_reading());

    lcd.setCursor(7, 1);
    lcd.print(soil_reading());
    Serial.print(moisture_reading);

    delay(1000);



}

int temp_reading(){
    double tempDAC = analogRead(tempPin);
    tempC = (tempDAC-620)/12.4;
    curr_temp = tempC ;
    return curr_temp;
}
int soil_reading() {
    digitalWrite(moistSensor, HIGH);
    delay(10);
    moisture_reading = analogRead(analog_sensor);
    digitalWrite(moistSensor, LOW);
    return moisture_reading;
}