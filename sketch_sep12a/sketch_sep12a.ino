// sudo chmod a+rw /dev/ttyACM0

//Libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>

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
    Serial.begin(9600);  //Begin serial communcation
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

   //delay(2000);
   int delayHour = 1000*60*60;
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
   Import processing.serial.*;
   Serial mySerial;
   PrintWriter output;
   void setup() {
    mySerial = new Serial(this, Serial.list()[0],9600);
    output = createWriter("data.txt");
   }
   void draw() {
    if(mySerial.available() >0) {
      String value = mySerial.readString();
      if (value != null) {
        output.println(value);
        
      }
    }
   }
   void keyPressed(){
    output.flush(); //Writes the reminaing data to the file
    output.close();// Finishes the file
    exit();//Stops the program
   }

   delay(10000); //delay 10 sec for testing
   //delay(delayHour); //Delay 1 Hour.

   
}
