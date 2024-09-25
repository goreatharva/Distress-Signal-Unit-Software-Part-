#include<Wire.h>
#include <SoftwareSerial.h>
const int MPU6050_addr=0x68;
int16_t GyroX,GyroY,GyroZ;
int buzzerPin = 10;
SoftwareSerial mySerial(8,7);
void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  digitalWrite(5,LOW);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  Serial.println("Initializing..."); 
  delay(5000);
}
void loop()
{
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();
  Serial.print(" || GyroX = "); Serial.print(GyroX);
  Serial.print(" || GyroY = "); Serial.print(GyroY);
  Serial.print(" || GyroZ = "); Serial.println(GyroZ);
  
  if(GyroX>10000)
  {
  
    mySerial.begin(9600);

  
    Serial.println("Initializing..."); 
    delay(1000);

    mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
    updateSerial();

    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CMGS=\"+919106114583\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    mySerial.print("https://www.google.com/maps/place/18.464233,73.867752"); //text content
    updateSerial();
    mySerial.write(26);
    Serial.begin(9600);
    digitalWrite(buzzerPin, HIGH);
    delay(10000);
    digitalWrite(buzzerPin, LOW);
    delay(500);  
    delay(60000);
  }                                                   
  else
  {
    Serial.println("Body Movement detected");
  }
      
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}


