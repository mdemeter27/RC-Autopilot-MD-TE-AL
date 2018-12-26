
#include <TinyGPS.h>
TinyGPS gps;


void GPSsetup()
{
  Serial1.begin(9600);

}

void GPSloop() {
  while (Serial1.available()) {
    int c = Serial1.read();
    gps.encode(c);
  }
  unsigned long fix_age;
  long latitude, longitude;
  float alt, MPH;
  gps.get_position(&latitude, &longitude, &fix_age);
  alt = gps.f_altitude();
  MPH = gps.f_speed_mph();
  float tens =10000.0; 
  double flat=double(latitude);
  flat=flat/1000000.0;
  Serial.print("Latitude:  "); Serial.println(flat);
  Serial.print("Longitude:  "); Serial.println(longitude);
  Serial.print("Alt:  "); Serial.println(alt);
  Serial.print("MPH:  "); Serial.println(MPH);





}
