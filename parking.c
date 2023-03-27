//code for counter


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_TEMPLATE_ID "TMPLXWoEHJId"
#define BLYNK_DEVICE_NAME "sensors"
#define BLYNK_AUTH_TOKEN "hfN7c3vPqamTfYoTg9Oc-iMmCBZ-ttkS"

char auth[] = "hfN7c3vPqamTfYoTg9Oc-iMmCBZ-ttkS"; //enter auth code
char ssid[] = "bha"; //enter wifi name
char pass[] = "12345678"; //enter wifi password

int IR_sensor1 = D0;
int IR_sensor2 = D1;
int IR_sensor3 = D2;
int IR_sensor4 = D3;
int IR_sensor5 = D4;
int IR_sensor6 = D5;

int LED = D7;

WidgetLED led1(V1);// Virtual Pin V1
WidgetLED led2(V2);// Virtual Pin V2
WidgetLED led3(V3);
WidgetLED led4(V4);
WidgetLED led5(V5);
WidgetLED led6(V6);

BlynkTimer timer;

void sensor1(){
  int value = digitalRead(IR_sensor1);
  if(value == HIGH){
    led1.on();
    digitalWrite(LED,HIGH);
  }
  else{
    led1.off();
    digitalWrite(LED,LOW);
  }  
}
void sensor2(){
  int value = digitalRead(IR_sensor2);
  if(value == HIGH){
    led2.on();
    digitalWrite(LED,HIGH);
  }
  else{
    led2.off();
    digitalWrite(LED,LOW);
  }  
}
void sensor3(){
  int value = digitalRead(IR_sensor3);
  if(value == HIGH){
    led3.on();
    digitalWrite(LED,HIGH);
  }
  else{
    led3.off();
    digitalWrite(LED,LOW);
  }  
}
void sensor4(){
  int value = digitalRead(IR_sensor4);
  if(value == HIGH){
    led4.on();
    digitalWrite(LED,HIGH);
  }
  else{
    led4.off();
    digitalWrite(LED,LOW);
  }  
}
void sensor5(){
  int value = digitalRead(IR_sensor5);
  if(value == HIGH){
    led5.on();
    digitalWrite(LED,HIGH);
  }
  else{
    led5.off();
    digitalWrite(LED,LOW);
  }  
}
void sensor6(){
  int value = digitalRead(IR_sensor6);
  if(value == HIGH){
    led6.on();
    digitalWrite(LED,HIGH);
  }
  else{
    led6.off();
    digitalWrite(LED,LOW);
  }  
}
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(IR_sensor1,INPUT);
  pinMode(IR_sensor2,INPUT);
  pinMode(IR_sensor3,INPUT);
  pinMode(IR_sensor4,INPUT);
  pinMode(IR_sensor5,INPUT);
  pinMode(IR_sensor6,INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(300L,sensor1);
  timer.setInterval(300L,sensor2);
  timer.setInterval(300L,sensor3);
  timer.setInterval(300L,sensor4);
  timer.setInterval(300L,sensor5);
  timer.setInterval(300L,sensor6);
}
void loop()
{
  Blynk.run();
  timer.run();
}
//code for RFID

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 4 //define green LED pin
#define LED_R 5 //define red LED
#define BUZZER 2 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "A7 04 C4 B5") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    myServo.write(180);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
}  

