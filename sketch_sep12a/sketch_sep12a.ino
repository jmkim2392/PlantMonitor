

//Libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>

//Light sensor
int lightPin = 0;  //define a pin for Photo resistor
int ledPin = 13;
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
    pinMode( ledPin, OUTPUT );
    dht.begin();
}

void loop()
{
    Serial.println(analogRead(lightPin)); //Write the value of the photoresistor to the serial monitor.
    analogWrite(ledPin, analogRead(lightPin)/4);  //send the value to the ledPin. Depending on value of resistor 
                                                //you have  to divide the value. for example, 
                                                //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
   delay(1000); //short delay for faster response to light.

   delay(2000);
   //Read data and store it to vriables humidity and temp
   humidity = dht.readHumidity();
   temp = dht.readTemperature();
   //Print temp and humidity values to serial monitor
   Serial.print("Humidity: ");
   Serial.print(humidity);
   Serial.print(" %, Temp: ");
   Serial.print(temp);
   Serial.println(" Celsius");
   delay(10000); //Delay 2 sec.

   
}
