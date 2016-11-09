//Defining the pins before the setup
#define echopin 9
#define trigpin 8
#define motorLeft2 3
#define motorRight2 5
#define motorLeft1 6
#define motorRight1 7



int maximumRange = 30;
long duration, distance;
void setup() {
  Serial.begin (9600);   // setting up the serial communication
  pinMode (trigpin, OUTPUT);       // setting the Input / Output in setup
  pinMode (echopin, INPUT );
  pinMode (motorLeft1, OUTPUT);     // pins for motor movement
  pinMode (motorLeft2, OUTPUT);
  pinMode (motorRight1, OUTPUT);
  pinMode (motorRight2, OUTPUT);
  }
  void loop ()
  {
    {
      digitalWrite(trigpin,LOW);
      delayMicroseconds(2);
      digitalWrite(trigpin,HIGH);
      delayMicroseconds(10);
      duration=pulseIn (echopin,HIGH);
      distance= duration/58.2;
      delay (50);
      Serial.println(distance);
      }
      if (distance >= 30 ){
        digitalWrite(motorLeft1,HIGH);
        digitalWrite(motorRight1,HIGH);
        digitalWrite(motorLeft2,LOW);
        digitalWrite(motorRight2,LOW);
        delay (200);
        }
        else if (distance >=15 && distance <= 25) {
          digitalWrite (motorLeft1,HIGH);
          digitalWrite (motorRight1,LOW);
          digitalWrite (motorLeft2,LOW);
          digitalWrite (motorRight2,LOW);
          delay (1000);
          }
          else if (distance < 15){
            digitalWrite (motorLeft1, LOW);
            digitalWrite (motorRight1, LOW);
            digitalWrite (motorLeft2,HIGH);
            digitalWrite (motorRight2,HIGH);
            delay (1000);
            digitalWrite (motorLeft1,LOW);
            digitalWrite (motorRight1,HIGH);
            digitalWrite (motorLeft2,LOW);
            digitalWrite (motorRight2, LOW);
            delay (1000);
          }
          
          }
