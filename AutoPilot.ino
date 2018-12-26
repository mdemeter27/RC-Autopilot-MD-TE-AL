void setup() {
  Serial.begin(115200);
  //servoSetup();
  GPSsetup();
  accelSetup();
}

void loop() {
  //servoLoop();
  GPSloop();
 accelLoop();
}
