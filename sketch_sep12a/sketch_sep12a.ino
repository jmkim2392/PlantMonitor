// sudo chmod a+rw /dev/ttyACM0

//Libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DateTime.h>

#define TIME_MSG_LEN 11 //time sync to PC is HEADER and unix time_t as ten ascii digits 
#define TIME_HEADER 255 // Header tag for serial time sync message

//Light sensor
//int lightPin = 0;  //define a pin for Photo resistor
//int ledPin = 13;

//Temperature & Humidity
#define DHTPIN 2  //define a pin for DHT-22 Humidity & Temperature Sensor
#define DHTTYPE DHT22 //define DHT type
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT Sensor

int chk;
float humidity; //Stores humidity value
float temp; //Stores temperature value


void setup()
{
  Serial.begin(19200);  //Begin serial communcation
  //pinMode( ledPin, OUTPUT );
  dht.begin();
}

void loop()
{
  //Serial.println(analogRead(lightPin)); //Write the value of the photoresistor to the serial monitor.
  //analogWrite(ledPin, analogRead(lightPin)/4);  //send the value to the ledPin. Depending on value of resistor
  //you have  to divide the value. for example,
  //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
  //delay(1000); //short delay for faster response to light.

  // DateTime
  getPCtime(); // sync time from pc
  if (DateTime.available()) {
    unsigned long prevtime = DateTime.now();
    while (prevtime == DateTime.now());
    DateTime.available(); //refresh the date and time properties
    digitalClockDisplay(); //update digital clock

    // send time to an app listening on the serial port
    Serial.print(TIME_HEADER, BYTE); //the header for the current time
    Serial.println(DateTime.now());
  }

  // DHT22 Sensor
  //delay(2000);
  int delayHour = 1000 * 60 * 60;
  //Read data and store it to variables humidity and temp
  humidity = dht.readHumidity();
  temp = dht.readTemperature();
  //Check if read failed
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Error, sensor read failure");
  }
  else {
    delay(1000); //
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
  }

  delay(10000); //delay 10 sec for testing
  //delay(delayHour); //Delay 1 Hour.
}

void getPCtime() {
  // if time available from serial port, sync the DateTime library
  while (Serial.available() >=  TIME_MSG_LEN ) { // time message
    if ( Serial.read() == TIME_HEADER ) {
      time_t pctime = 0;
      for (int i = 0; i < TIME_MSG_LEN - 1; i++) {
        char c = Serial.read();
        if ( c >= '0' && c <= '9')
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number
      }
      DateTime.sync(pctime);   // Sync DateTime clock to the time received on the serial port
    }
  }
}

void digitalClockDisplay() {
  // digital clock display of current time
  Serial.print(DateTime.Hour, DEC);
  printDigits(DateTime.Minute);
  printDigits(DateTime.Second);
  Serial.print(" ");
  Serial.print(DateTimeStrings.dayStr(DateTime.DayofWeek));
  Serial.print(" ");
  Serial.print(DateTimeStrings.monthStr(DateTime.Month));
  Serial.print(" ");
  Serial.println(DateTime.Day, DEC);
}

void printDigits(byte digits) {
  // utility function for digital clock display: prints colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits, DEC);
}
