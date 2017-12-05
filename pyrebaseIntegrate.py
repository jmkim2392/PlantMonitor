import pyrebase
import serial


config = {
    "apiKey": "AIzaSyDQsG8ujA02UXqD87t0FPZDal5DBa6YlGk",
    "authDomain": "plant-monitor-9e424.firebaseapp.com",
    "databaseURL": "https://plant-monitor-9e424.firebaseio.com/",
    "storageBucket": "plant-monitor-9e424.appspot.com"
    }

firebase = pyrebase.initialize_app(config)

db = firebase.database()
db.child("users").child("Morty")


data = {"name": "Mortimer ' Morty' Smith" }
db.child("users").push(data)



ser = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1) #port name, connect rate, waittime to receive data
var = 1
while var == 1 :
    arduinoData = ser.readline().decode('ascii')
    if arduinoData != "":
        print(arduinoData)
    db.child("Humidity").push(arduinoData)
