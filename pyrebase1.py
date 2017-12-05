import pyrebase
import serial
import datetime
import re
import time

config = {
    "apiKey": "AIzaSyDQsG8ujA02UXqD87t0FPZDal5DBa6YlGk",
    "authDomain": "plant-monitor-9e424.firebaseapp.com",
    "databaseURL": "https://plant-monitor-9e424.firebaseio.com/",
    "storageBucket": "plant-monitor-9e424.appspot.com"
    }

firebase = pyrebase.initialize_app(config)
db = firebase.database()

humidity= 0
temperature = 0
ser = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1) 
#port name, connect rate, waittime to receive data


humCheck = False
tempCheck = False
var = 1
while var == 1 :
	#store data in to years and months
	#check year
	year = datetime.date.today().strftime("%Y")
	#check month
	month = datetime.date.today().strftime("%B")
	#store date and Time
	timestamp = datetime.datetime.now().strftime("%d | %H:%M")
	minute = int(datetime.datetime.now().strftime("%M"))
	
	if minute % 10 == 0 :
	
		#read arduino data
		arduinoData = ser.readline().decode('ascii')
		if arduinoData != "":
			print(arduinoData)
		
			#check if humidity reading
			if "H" in arduinoData:
				match = re.search(r"([0-9]+(?:\.[0-9]+)?)(?:\s)", arduinoData)
				if match:
					humidity = match.group()
					humidity = humidity.replace('\r', "")
					db.child(year).child(month).child("Humidity").update({
					timestamp : humidity
				})
				humCheck = True
			
			#check if temperature reading
			elif "T" in arduinoData:
				match = re.search(r"([0-9]+(?:\.[0-9]+)?)(?:\s)", arduinoData)
				if match:
					temperature = match.group()
					temperature = temperature.replace('\r', "")
					db.child(year).child(month).child("Temperature").update({
					timestamp :temperature
				})
				tempCheck = True
			
			#check if both read and wait 10 minutes to read again
			if humCheck and tempCheck:
				humCheck = False
				tempCheck = False
	
		
		




