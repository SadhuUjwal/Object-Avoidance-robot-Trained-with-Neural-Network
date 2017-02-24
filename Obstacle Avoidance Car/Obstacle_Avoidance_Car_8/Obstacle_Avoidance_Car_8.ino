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
int ABS = 70;



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
 Serial.print("\t");
 Serial.print(" moving forward");
 
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
 Serial.print("\t");
 Serial.print("moving left");
}

void _mright()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,LOW);
 digitalWrite(in4,HIGH);
 Serial.print("\t");
 Serial.print("moving right");
 
} 
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.print("\t");
  Serial.print("stop");
  
} 

long lookright()
{
    long duration,rightDistance;
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
    //Serial.print("right dist=");
    Serial.print(rightDistance);
    return rightDistance;
}

long lookleft()
{
    long duration, leftDistance;
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
    //Serial.print("left dist=");
    Serial.print(leftDistance);
    return leftDistance;
}

long lookforward()
{
  long duration, cm;
  myservo.write(90);//setservo position according to scaled value
  delay(500);
     
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
  Serial.print(cm);
  Serial.print("\t");
  return cm;
}

void setup() 
{ 
  myservo.attach(3);
  // attach servo on pin 3 to servo object
  Serial.begin(9600);  
 
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
} 


void loop() {

   long fwd,rgt,lft;
    
   fwd=lookforward(); 
   delay(2000);
   
   if(fwd<=30)
   {
   
    _mStop();
    delay(1000);  
       
  //right
    rgt=lookright();
    delay(2000);
    //left
    lft=lookleft();
  delay(2000);
    
  myservo.write(90);
    delay(2000);
    if(rgt>=lft)
    {
      _mright();
     
      delay(500);    
    }
    else
    {
      _mleft();
     
      delay(500);   
    }
   
   }
    else
   {
    
    _mForward();
   delay(1000);
   }
        
   
   Serial.println("");
}


