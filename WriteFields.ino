#include <LiquidCrystal_I2C.h> 
#include <ESP8266WiFi.h>
#include<WifiClient.h>
#include<ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define BUZZER_PIN D1
String URL="http://api.thingspeak.com/update?api_key=OKB7Z16F9D2SJSWW&field2=";
String URL1="http://api.thingspeak.com/update?api_key=OKB7Z16F9D2SJSWW&field1=";
LiquidCrystal_I2C lcd(0x27,16,2);
const char* ssid = "Yaseen";
const char* password = "shaik2425";
double sensorValue1 = 0;
double sensorValue2 = 0;
int crosscount = 0;
int climb_flag = 0;
int val[100];
int max_v = 0;
double VmaxD = 0;
double VeffD = 0;
double Veff = 0;
int xCoord = 0;
 const int trigPin = D5;  
 const int echoPin = D6;   
 long duration;  
 int distance;  

void setup() {
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output  
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  delay(100);
  pinMode(BUZZER_PIN, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Daradici Levente");
  lcd.setCursor(2,1);
  lcd.print("AC Voltmeter");
  delay(3000);
  lcd.clear();
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
   WiFiClient client;
  HTTPClient http; 
  digitalWrite(trigPin, LOW);  
 delayMicroseconds(2);  
 // Sets the trigPin on HIGH state for 10 micro seconds  
 digitalWrite(trigPin, HIGH);  
 delayMicroseconds(10);  
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);  
 // Calculating the distance  
 distance= duration*0.034/2;  
 // Prints the distance on the Serial Monitor  
 Serial.print("Distance: ");  
 Serial.println(distance);  
 delay(2000);
  String newUrl=URL+String(distance);
  http.begin(client,newUrl);
  int responsecode=http.GET();
  String data=http.getString();
  Serial.println(data);
  http.end();
 if(distance<600){
  for ( int i = 0; i < 100; i++ ) {
    sensorValue1 = analogRead(A0);
    if (analogRead(A0) > 511) {
      val[i] = sensorValue1;
    }
    else {
      val[i] = 0;
    }
    delay(1);
  }
 
  max_v = 0;
 
  for ( int i = 0; i < 100; i++ )
  {
    if ( val[i] > max_v )
    {
      max_v = val[i];
    }
    val[i] = 0;
  }
  if (max_v != 0) {
 
 
    VmaxD = max_v;
    VeffD = VmaxD / sqrt(2);
    Veff = (((VeffD - 420.76) / -90.24) * -210.2) + 210.2;
  }
  else {
    Veff = 0;
  }
  Serial.print("Voltage: ");
  Serial.println(Veff);
  VmaxD = 0;
  Serial.println(Veff);
  String newUrl1=URL1+String(Veff);
  http.begin(client,newUrl1);
  int responsecode1=http.GET();
  String data1=http.getString();
  Serial.println(data1);
  http.end();
  if(Veff>110){
    tone(BUZZER_PIN, 1000); // 1000 Hz tone
  delay(1000); // Wait for 1 second
  }
  else{
     noTone(BUZZER_PIN); // Turn off the buzzer
  delay(1000); // Wait for 1 second
}
 }
 else{
  Serial.println("nothing is detected");
 }
  if (Veff < 1000) { xCoord = 8;} 
  if (Veff < 100) { xCoord = 9; } 
  if (Veff < 10) { xCoord = 10; } 
  lcd.clear();  
  lcd.setCursor(xCoord,1);
  lcd.print(Veff);
  lcd.setCursor(15,1);
  lcd.print("V");
  delay(500);
 }