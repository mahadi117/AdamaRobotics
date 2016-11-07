const int rightLDR = A0;                                  //right LDR attached to analog pin 0
const int leftLDR = A1;                                   //left LDR attached to analog pin 1       

int leftValue;                                            //this variable is used to store the analog value returned from the left LDR
int rightValue;                                           //this variable is used to store the analog value returned from the right LDR
int difference;                                           //this variable is used to compare the difference in the two readings to see if there is a neglible difference

void setup()
{
  Serial.begin(9600);
  pinMode (4, OUTPUT);                                    // Motor Left output 1 
  pinMode (6, OUTPUT);                                    // Motor Left Output 2
  pinMode (5, OUTPUT);                                    // Motor Right output 1 
  pinMode (7, OUTPUT);                                    // Motor Right Output 2       
 
}

void loop()
{
  rightValue = analogRead(rightLDR);                    //store value from A0 into the variable rightValue
  leftValue = analogRead(leftLDR);                      //store value from A1 into the variable leftValue
  difference = abs(rightValue-leftValue);               //calculate the difference between the two values
  //Serial.println(rightValue);
  //delay(500);
  Serial.println("left LDR: "leftValue,"right LDR: "rightValue);
  delay(1000);
  if(difference < 90)                                   //if the difference is less than 50 then...
  {
    moveForward();                                      //the robot will move forward
  }
  else                                                  //if not then...
  {
   if(rightValue > leftValue)                           //is it darker on the right hand side?
    {
     moveLeft();  //light follow                        //if so then turn left
     //moveRight();  //light avoid
    } 
    else
    {
     moveRight(); //light follow                        //if it isn't then turn right
     //moveLeft();  //light avoid
    }
  }
}

void moveForward()
{
        digitalWrite(4,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(7,LOW);
        delay (500);

}

void moveLeft()
{
        digitalWrite(4,LOW);
        digitalWrite(6,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(7,LOW);
        delay (500);

}

void moveRight()
{
        digitalWrite(4,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(5,LOW);
        digitalWrite(7,LOW);
        delay (500);

}
