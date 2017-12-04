import pyrebase
import serial
import datetime

config = {
    "apiKey": "AIzaSyDQsG8ujA02UXqD87t0FPZDal5DBa6YlGk",
    "authDomain": "plant-monitor-9e424.firebaseapp.com",
    "databaseURL": "https://plant-monitor-9e424.firebaseio.com/",
    "storageBucket": "plant-monitor-9e424.appspot.com"
    }

firebase = pyrebase.initialize_app(config)

humidity= 0
temperature = 0
ser = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1) 
#port name, connect rate, waittime to receive data
var = 1
while var == 1 :
    
    arduinoData = ser.readline().decode('ascii')
    if arduinoData != "":
        print(arduinoData)
timestamp = datetime.datetime.now().strftime("%Y-%m-%d | %H:%M")

int(filter(arduinoData.isdigit, humidity))
int(filter(arduinoData.isdigit, temperature))
#store data in to years and months
#check year
year = datetime.date.today().strftime("%Y")
#check month
month = datetime.date.today().strftime("%B")
#store date and Time
timestamp = datetime.datetime.now().strftime("%d | %H:%M")
db.child(year).child(month).set({
	'Humidity' :{
		timestamp : humidity
	},
	'Temperature' :{
		timestamp :temperature
	}
})



