// sudo chmod a+rw /dev/ttyACM0

//TZ_adjust=5.5; d=$(date+%s);t=$(echo "60*60*$TZ_adjust/1"|bc);echo T$(echo $d +$t|bc)>/dev/ttyACM0

//Libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Time.h>

#define TIME_MSG_LEN 11 //time sync to PC is HEADER and unix time_t as ten ascii digits 
////#define TIME_HEADER 255 // Header tag for serial time sync message
//#define TIME_REQUEST 7 // ASCII bell character requests a time sync message

//Temperature & Humidity
#define DHTPIN 2  //define a pin for DHT-22 Humidity & Temperature Sensor
#define DHTTYPE DHT22 //define DHT type
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT Sensor

int chk;
float humidity; //Stores humidity value
float temp; //Stores temperature value


void setup()
{
  Serial.begin(9600);  //Begin serial communcation
  dht.begin();        //Begin dht22 sensor read
}

void loop()
{
  // DHT22 Sensor
  delay(1000);
  //int delayHour = 1000 * 60 * 60;
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
    Serial.print("H");
    Serial.println(humidity);
    Serial.print("T");
    Serial.println(temp);
  }
  delay(60000);
  //delay(60000);
  //delay(delayHour); //Delay 1 Hour.
}

