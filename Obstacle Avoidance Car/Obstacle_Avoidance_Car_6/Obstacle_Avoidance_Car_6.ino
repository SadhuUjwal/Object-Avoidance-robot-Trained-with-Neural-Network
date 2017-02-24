//servo library
 // create servo object to control servo
 
 #include <Servo.h> 
Servo myservo;

long randNumber;
const int trigPin = 2;
const int echoPin = 4;

int LED=13;
volatile int state = LOW;
char getstr;
 
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 110;
int middleDistance = 0,distance=0 ;

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void _mForward()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
 
}

void _mBack()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
 
}

void _mleft()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
 
}

void _mright()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,LOW);
 digitalWrite(in4,HIGH);
 
} 
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  
} 
 /*Ultrasonic distance measurement Sub function
int Distance_test()   
{
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;       
  return (int)Fdistance;
}  
*/
void setup() 
{ 
myservo.attach(3);
  // attach servo on pin 3 to servo object
  Serial.begin(9600);  
 // randomSeed(analogRead(0));  
//  pinMode(Echo, INPUT);    
 // pinMode(Trig, OUTPUT);  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
} 


void loop() {

  myservo.write(90);//setservo position according to scaled value
    delay(500);
    long duration, cm,rightDistance,leftDistance;

  
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.println("");
  Serial.print("fwd dist=");
  Serial.print(cm);
  Serial.print("\t");
  // randNumber = random(1, 3); print a random number from 10 to 19
  
  
   
   
   if(cm<=20)
   {
    _mStop();
    Serial.print("\t");
    Serial.print("stop");
    delay(1000);
   
    myservo.write(0);
    delay(2000);
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    rightDistance = microsecondsToCentimeters(duration);
    Serial.print("\t");
    Serial.print("right dist=");
    Serial.print(rightDistance);
    delay(2000);
   
   
    myservo.write(180);
    delay(2000);
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    leftDistance = microsecondsToCentimeters(duration);
    Serial.print("\t");
    Serial.print("left dist=");
    Serial.print(leftDistance);
    delay(2000);
  
    myservo.write(90);
    delay(2000);
    if(rightDistance>=leftDistance)
    {
      _mright();
      Serial.print("\t");
      Serial.print("moving right");
      delay(1000);    
    }
    else
    {
      _mleft();
      Serial.print("\t");
      Serial.print("moving left");
      delay(1000);   
    }
   
   }
    else
   {
    _mForward();
    Serial.print("\t");
    Serial.print(" moving forward");
   }
        
   
   Serial.println("");
}

