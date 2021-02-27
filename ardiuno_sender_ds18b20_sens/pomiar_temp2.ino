// Program odczytuje temperaturę z czujnika

#include <OneWire.h>
#include <DS18B20.h>

// Numer pinu do którego podłaczasz czujnik
#define ONEWIRE_PIN 2
OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);
// Adres czujnika
byte address1[8] = {0x28, 0xFF, 0xA8, 0x41, 0x84, 0x16, 0x3, 0x72};
byte address2[8] = {0x28, 0xFF, 0x45, 0xA0, 0x84, 0x16, 0x4, 0x1};
byte address4[8] = {0x28, 0xFF, 0x40, 0x5F, 0x85, 0x16, 0x5, 0xCD};
byte address5[8] = {0x28, 0xFF, 0x78, 0xA4, 0x85, 0x16, 0x5, 0x92};
//byte address6[8] = {0x28, 0xFF, 0xB1, 0x60, 0x85, 0x16, 0x5, 0x74};
//byte address7[8] = {0x28, 0xFF, 0x5C, 0x7E, 0x85, 0x16, 0x4, 0x31};
//byte address8[8] = {0x28, 0xFF, 0x17, 0x2C, 0x86, 0x16, 0x5, 0xCD};

long temp1;
long temp2;
long temp4;
long temp5;
//long temp6;
//long temp7;
//long temp8;
float minim=10.0;
float maxim=99.9;


void setup() {
  while(!Serial);
  Serial.begin(1200);
  sensors.begin();
  sensors.request(address1);
  sensors.request(address2);
  sensors.request(address4);
  sensors.request(address5);
//  sensors.request(address6);
//  sensors.request(address7);
//  sensors.request(address8);
}

void loop() {
  if (sensors.available())
  {
   // 0,437532051  0,655480769 0,114797009 -0,03392094 -0,124262821  -0,055630342  -0,689049145  -0,304946581
// odczyt i kalibracja
    float temperature1 = sensors.readTemperature(address1); temperature1=(temperature1+0.44); temp1=(long)(temperature1*10L); temperature1 = (float) temp1 / 10.0; 
    float temperature2 = sensors.readTemperature(address2); temperature2=temperature2+0.66;   temp2=(long)(temperature2*10L); temperature2 = (float) temp2 / 10.0; 
    float temperature4 = sensors.readTemperature(address4); temperature4=temperature4-0.03;   temp4=(long)(temperature4*10L); temperature4 = (float) temp4 / 10.0; 
    float temperature5 = sensors.readTemperature(address5); temperature5=temperature5-0.12;   temp5=(long)(temperature5*10L); temperature5 = (float) temp5 / 10.0; 
//    float temperature6 = sensors.readTemperature(address6); temperature6=temperature6-0.06;   temp6=(long)(temperature6*10L); temperature6 = (float) temp6 / 10.0; 
//    float temperature7 = sensors.readTemperature(address7); temperature7=temperature7-0.69;   temp7=(long)(temperature7*10L); temperature7 = (float) temp7 / 10.0; 
//    float temperature8 = sensors.readTemperature(address8); temperature8=temperature8-0.3;    temp8=(long)(temperature8*10L); temperature8 = (float) temp8 / 10.0; 
// warunki graniczne
    if (temperature1<minim || temperature1>maxim){ temperature1=99.9;}
    if (temperature2<minim || temperature2>maxim){ temperature2=99.9;}
    if (temperature4<minim || temperature4>maxim){ temperature4=99.9;}
    if (temperature5<minim || temperature5>maxim){ temperature5=99.9;}
//    if (temperature6<minim || temperature6>maxim){ temperature6=99.9;}
//    if (temperature7<minim || temperature7>maxim){ temperature7=99.9;}
//    if (temperature8<minim || temperature8>maxim){ temperature8=99.9;}

// wysyl danych po serialu
    Serial.print(temperature1,1);
    Serial.print(",");  
    Serial.print(temperature2,1);
    Serial.print(",");  
    Serial.print(temperature4,1);
    Serial.print(",");  
  //  Serial.print(temperature5,1);
    Serial.println(temperature5,1);
  //  Serial.print(",");  
  //  Serial.print(temperature6,1);
  //  Serial.print(",");  
  //  Serial.print(temperature7,1);
  //  Serial.print(",");  
  //  Serial.println(temperature8,1);
    

    sensors.request(address1);
    sensors.request(address2);
    sensors.request(address4);
    sensors.request(address5);
 //   sensors.request(address6);
 //   sensors.request(address7);
 //   sensors.request(address8);

      

    
  }

  
  delay(2000);
}
