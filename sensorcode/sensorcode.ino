 #include <SoftwareSerial.h>
SoftwareSerial HC12(10,11); //hc12 tx, hc12 rx

//Ultrasonic Sensor
const int trigPin = 4;
const int echoPin = 5;
long duration;
int distanceCm;

//Vibrate Sensor
int vib = 6;
int val;
int getar = 0;

void setup()
{
  //All Device Begin
  Serial.begin(9600);
  HC12.begin(9600);

  //Ultrasonic pin configuration
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Soil Moisture + Vibrate Sensor pin Confuguration
  pinMode(A0, INPUT);
  pinMode (vib, INPUT);
}

void loop()
{
  float sensorValue = analogRead(A0);
  float persen=((1024-sensorValue)/1024)*100;
  Serial.println(persen);
  HC12.println(persen);
  delay(500);
  
  distanceCm= duration*0.034/2;

  int getar= digitalRead(vib);  

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
//aman dan waspada
  if (getar == 1 && distanceCm >= 10)
  {
    if (persen >= 0 && persen <= 65)
    {
      Serial.println("safe"); 
      HC12.println(1100); //aman
      delay(500);
    }
    else if (persen >= 65 && persen <= 90)
    {
      Serial.println("alert");
      HC12.println(1110); //waspada
      delay(500);
    }
    else if (persen >= 90 && persen <= 100)
    {
      Serial.println("danger");
      HC12.println(1101); //waspada
      delay(500);
    }
  }
//bahaya
  else if (getar == 0 && distanceCm <= 5 )
  {
    if (persen >= 0 && persen <= 100)
    {
      Serial.println("safe");
      HC12.println(1101); //bahaya
      delay(500);
    }
  }

  else if (distanceCm <= 10)
  {
    Serial.println("danger");
    HC12.println(1101);
    delay(500);
  }
  delay(100);  
}

