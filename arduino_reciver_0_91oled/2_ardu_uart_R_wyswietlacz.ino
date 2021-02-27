#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#define glosnik 9
//char mystr[40]; //Initialized variable to store recieved data
//char odczyt[5];

String recived = "";

//======= 1 - piec,  2 - stol 1, 3 - stol 2, 4 - stol 3======
String temp1="11.1";
String temp2="11.1";
String temp3="11.1";
String temp4="11.1";

String miejsce1="Piec: ";
String miejsce2="St.1: ";
String miejsce3="St.2: ";
String miejsce4="St.3: ";

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 
void setup() {
  //======== predkosc przesylu ===================
  Serial.begin(1200);  // domyslnie dziala na 9600 
  //======== timeout =============================
  Serial.setTimeout(1000); // 1000ms
  //======== inicializacja wyswietlacza ==========
  u8g2.begin();
  
}

void loop() {
  //============= odczyt z uart ==================
  recived = Serial.readString();
  Serial.println(recived);
  temp1=recived.substring(0,4);
  temp2=recived.substring(5,9);
  temp3=recived.substring(10,14);
  temp4=recived.substring(15,19);
 //============= wywolanie wyswietlania =========
  wyswietlanie(miejsce1,temp1);
  delay(2000);
  wyswietlanie(miejsce2,temp2);
  delay(2000);
  wyswietlanie(miejsce3,temp3);
  delay(2000);
  wyswietlanie(miejsce4,temp4);
  delay(2000);

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
   alarm(temp1,temp2,temp3,temp4);
   delay(2000);
}

//=== funkcja wyswietlajaca na OLED 0.91 =========
void wyswietlanie(String miejsce, String temp){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_gb24st_t_2);
  u8g2.setCursor(0, 14);
  u8g2.print(miejsce);
  u8g2.setCursor(55, 25);
  u8g2.setFont(u8g2_font_fub17_tf);
  u8g2.print(temp);
  u8g2.setFont(u8g2_font_gb24st_t_2);
  u8g2.setCursor(104, 12);
  u8g2.print("o"); 
  u8g2.setFont(u8g2_font_fub17_tf);
  u8g2.setCursor(114, 25);
  u8g2.print("C");
  u8g2.sendBuffer();         
}

//==== alerty ================================
void alarm(String temp1,String temp2, String temp3, String temp4){
  float piec_min=35;
  float piec_max=75;
  float stol_min=12;  
  float stol_max=40;
  float t1=temp1.toFloat();
  float t2=temp2.toFloat();
  float t3=temp3.toFloat();
  float t4=temp4.toFloat();

  //=== sprawdzenie skrajnych temperatur =====
  
  if(t1<piec_min || t1>piec_max || t2<stol_min || t3<stol_min || t3<stol_min || t2>stol_max || t3>stol_max || t4>stol_max){
  tone(glosnik, 1000);
    digitalWrite(glosnik, HIGH); 
    Serial.println("tak");
  }else{
    noTone(glosnik);
    Serial.println("nie");
  }
}
