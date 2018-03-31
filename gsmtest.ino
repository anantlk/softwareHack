#include <SoftwareSerial.h>
#include <Servo.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
int digital;
int flag;
int servoPin = 3;
Servo Servo1;
String a;
String b;
int c=0;
int sensor_pin = A0;
int output_value ;
SoftwareSerial mySerial(9, 10);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode (2 , INPUT);
  Servo1.attach(servoPin);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(100);
}

void loop()
{
  humiditytemp();
  water();
  servoo();
  moisture();
  if (mySerial.available()>0)
 {
   a=mySerial.readString();
   Serial.println(a);
   b=a.substring(51);
   Serial.println(b);
   b.trim();
   if(b.equals("ON"))
   {
     c=1;
     String x="Turned ON";
     SendMessage(x);
     Serial.println(c);
   }
   if(b.equals("OFF"))
   {
     String y="Turned Off";
     c=0;
     SendMessage(y);
     Serial.println(c);
   }
   if(b.equals("Status"))
   {
      String t="Temperature is: "+(String)temp+"\n"+"Humidity is: "+(String)hum+"\n"+"Mositure % is: "+String(output_value);
      SendMessage(t);   
   }
 } 

}




void humiditytemp()
{
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(500);
 
}

int water()
{
  // put your main code here, to run repeatedly:
 
  digital = digitalRead(2);
  Serial.println (digital);
}
int flag1=1;
void servoo()
{
  if(c==1){
    if(digital==0)
     {
       Servo1.write(0);
       if(flag1==1)
       {
       flag1=0; 
       String a="Overflow turned off";
       SendMessage(a);
       }
     }
     else{
       flag1=1;
       Servo1.write(0);
       delay(1000);
       Servo1.write(180);
       delay(1000);
      } 
  }   
}  

 void SendMessage(String a)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919944777265\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(a);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(100);
}
void moisture() {
   output_value= analogRead(sensor_pin);
   output_value = map(output_value,550,0,0,100);
   Serial.print("Mositure : ");
   Serial.print(output_value);
   Serial.println("%");
   delay(500);

   }

