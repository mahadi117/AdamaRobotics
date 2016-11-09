const int rightLDR = A0;                                  //right LDR attached to analog pin 0
const int leftLDR = A1;                                   //left LDR attached to analog pin 1       

#define echopin  2
#define trigpin 3
#define buzzer 9

int maximumRange = 30;
long duration, distance;

int leftValue;                                            //this variable is used to store the analog value returned from the left LDR
int rightValue;                                           //this variable is used to store the analog value returned from the right LDR
int difference;                                           //this variable is used to compare the difference in the two readings to see if there is a neglible difference

void setup()
{
  Serial.begin(9600);
  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  pinMode (8, OUTPUT);                                    // Motor Left output 1 
  pinMode (6, OUTPUT);                                    // Motor Left Output 2
  pinMode (5, OUTPUT);                                    // Motor Right output 1 
  pinMode (7, OUTPUT);                                    // Motor Right Output 2       
  pinMode(buzzer, OUTPUT);                                // Buzzer pin 

}

void loop()
{
  rightValue = analogRead(rightLDR);                    //store value from A0 into the variable rightValue
  leftValue = analogRead(leftLDR);                      //store value from A1 into the variable leftValue
  difference = abs(rightValue-leftValue);               //calculate the difference between the two values

  /*/ Obstacle avoidance bit, here it will check if there is any obstacle /*/
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

  
  Serial.write("left LDR:");
  Serial.println(leftValue);
  Serial.write("right LDR:"); 
  Serial.println(rightValue);
  delay(1000);
  if(difference < 90)                            //if the difference is less than 50 then...
  {
    /*/ if the difference of light between the sensors is less than 90
        that means the light is coming from the front. So keep moving forward.
   */
    moveForward();                               //the robot will move forward
    // check if both sensor getting no light or minimal light then stop the robot
        if(rightValue < 70 && leftValue< 70){
           motor_stop();
           beep(100); 
           beep(200);
         }
    checkObstacle();
  }
  else                                                 //if not then...
  {
   if(rightValue > leftValue)                           //is it darker on the right hand side?
    {
     moveLeft();  //light follow                        //if so then turn left
     //moveRight();  //light avoid
     checkObstacle();
     
    } 
    else
    {
     moveRight(); //light follow                        //if it isn't then turn right
     //moveLeft();  //light avoid
     checkObstacle();
    }   
   } // end else
  

      /* check if the obstacle is out of 30 cm, then move forward
        else if it is in the range then move left, else if it less than the range
        then go back a bit then move again.
      */

}
void checkObstacle()
{
 
      if (distance >= 30 ){
        moveForward(); 
       }
      else if(distance >=15 && distance <=25){
        moveLeft();
       }
      else if(distance <15){
        moveBack();
        delay(1000);
        moveLeft();
        delay(500);
        moveForward();
        delay(500);
       } // here the obstacle checking bit finishes.
} 

/* This bit here are functions to control the motor */
void moveForward()
{
        digitalWrite(8,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(7,HIGH);
        delay (500);

}

void moveLeft()
{
        digitalWrite(8,LOW);
        digitalWrite(6,LOW);
        digitalWrite(5,LOW);
        digitalWrite(7,HIGH);
        delay (500);
        beep(50); 
        beep(100);

}

void moveRight()
{
        digitalWrite(8,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(7,LOW);
        delay (500);
        beep(100); 
        beep(50);

}
void moveBack()
{
        digitalWrite(8,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(7,LOW);
        delay (500);
        beep(100); 
        beep(170);
        beep(100); 
        beep(170);

}
void motor_stop()
{
        digitalWrite(8,LOW);
        digitalWrite(6,LOW);
        digitalWrite(5,LOW);
        digitalWrite(7,LOW);
        delay (1000);
        beep(20); 
        delay(50);
        beep(20);

}

void beep(unsigned char delayms){
  analogWrite(buzzer, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(buzzer, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  

