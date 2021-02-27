#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#define glosnik 9

  
#include <TM1637Display.h>

#define CLK 3
#define DIO 4
//Create object
TM1637Display display(CLK, DIO);

String recived = "";

//======= 1 - piec,  2 - stol 1, 3 - stol 2, 4 - stol 3======
String temp1="11";
String temp2="11";
String temp3="11";
String temp4="11";
int tempe1;
int tempe2;
int tempe3;
int tempe4;

uint8_t piec[]={
  SEG_A|SEG_B|SEG_G|SEG_E|SEG_F,
  SEG_C|SEG_B,
  SEG_A|SEG_D|SEG_G|SEG_E|SEG_F,
  SEG_A|SEG_D|SEG_E|SEG_F,
};
uint8_t st1[]={
  SEG_A|SEG_F|SEG_G|SEG_C|SEG_D,
  SEG_F|SEG_G|SEG_E|SEG_D,
  SEG_D,
  SEG_B|SEG_C,
};
uint8_t st2[]={
  SEG_A|SEG_F|SEG_G|SEG_C|SEG_D,
  SEG_F|SEG_G|SEG_E|SEG_D,
  SEG_D,
  SEG_A|SEG_B|SEG_G|SEG_E|SEG_D,
};
uint8_t st3[]={
  SEG_A|SEG_F|SEG_G|SEG_C|SEG_D,
  SEG_F|SEG_G|SEG_E|SEG_D,
  SEG_D,
  SEG_A|SEG_B|SEG_G|SEG_C|SEG_D,
};

void setup() {
  //======== predkosc przesylu ===================
  Serial.begin(1200);  // domyslnie dziala na 9600 
  //======== timeout =============================
  Serial.setTimeout(1000); // 1000ms
  //======== inicializacja wyswietlacza ==========
  display.setBrightness(0x0A);
  
}

void loop() {
  //============= odczyt z uart ==================
  recived = Serial.readString();
  Serial.println(recived);
  temp1=recived.substring(0,2);
  temp2=recived.substring(5,7);
  temp3=recived.substring(10,12);
  temp4=recived.substring(15,17);
  tempe1=temp1.toInt();
  tempe2=temp2.toInt();
  tempe3=temp3.toInt();
  tempe4=temp4.toInt();
 //============= wywolanie wyswietlania =========
  display.setSegments(piec, 4, 0);  
  delay(2000);
  display.showNumberDec(tempe1); 
  delay(3000);
  
  display.setSegments(st1, 4, 0);  
  delay(2000);
  display.showNumberDec(tempe2); 
  delay(3000);
  
  display.setSegments(st2, 4, 0);  
  delay(2000);
  display.showNumberDec(tempe3); 
  delay(3000);
  
  display.setSegments(st3, 4, 0);  
  delay(2000);
  display.showNumberDec(tempe4); 
  delay(3000);
  //============= wysyl na usb =================
  Serial.print("piec:   ");
  Serial.println(temp1);
  Serial.print("stol 1: ");
  Serial.println(temp2);
  Serial.print("stol 2: ");
  Serial.println(temp3);
  Serial.print("stol 3: ");
  Serial.println(temp4);
  //====
  // alarm(temp1,temp2,temp3,temp4);
  // delay(2000);
}


//==== alerty ================================
//void alarm(String temp1,String temp2, String temp3, String temp4){
//  float piec_min=35;
//  float piec_max=75;
//  float stol_min=12;  
//  float stol_max=40;
//  float t1=temp1.toFloat();
//  float t2=temp2.toFloat();
//  float t3=temp3.toFloat();
//  float t4=temp4.toFloat();
//
//  //=== sprawdzenie skrajnych temperatur =====
//  
//  if(t1<piec_min || t1>piec_max || t2<stol_min || t3<stol_min || t3<stol_min || t2>stol_max || t3>stol_max || t4>stol_max){
//  tone(glosnik, 1000);
//    digitalWrite(glosnik, HIGH); 
//    Serial.println("tak");
//  }else{
//    noTone(glosnik);
//    Serial.println("nie");
//  }
//}
