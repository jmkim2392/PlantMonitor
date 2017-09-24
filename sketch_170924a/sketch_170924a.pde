import processing.serial.*;

Serial myPort;
String val;
PrintWriter output;

void setup() {
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  output = createWriter("sensorData.txt");
}

void draw() {
  if (myPort.available() > 0) {
    val = myPort.readStringUntil('\n');
    output.println(val);
  }
  println(val);
  delay(10000);
}

void keyPressed() {
  output.flush();
  output.close();
  exit();
}