// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// TMP100
// This code is designed to work with the TMP100_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=TMP100_I2CS#tabs-0-product_tabset-2

#include<Wire.h>

// TMP100 I2C address is 0x4F(79)
#define Addr 0x4F

void setup() 
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // Set continuous conversion, comparator mode, 12-bit resolution
  Wire.write(0x60);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);  
}

void loop()
{
  unsigned int data[2];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // cTemp msb, cTemp lsb
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
    
  // Convert the data
  float cTemp = (((data[0] * 256) + (data[1] & 0xF0)) / 16) * 0.0625;
  float fTemp = cTemp * 1.8 + 32;
  
  // Output data to serial monitor
  Serial.print("Temperature in Celsius : ");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit : ");
  Serial.print(fTemp);
  Serial.println(" F");
  delay(500);
}
