int LED=13;
volatile int state = LOW;
char getstr;
int in1=6;
int in2=7;
int in3=8;
int in4=9;
int ENA=5;
int ENB=11;
int ABS=135;
void _mForward()
{ 
  digitalWrite(ENA,ABS);
  digitalWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("go forward!");
}
void _mBack()
{
  digitalWrite(ENA,ABS);
  digitalWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("go back!");
}
void _mleft()
{
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("go left!");
}
void _mright()
{
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("go right!");
}
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop!");
}
long getduration()
{
  long duration;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  return duration
}
long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void stateChange()
{
  state = !state;
  digitalWrite(LED, state);  
}
void setup()
{ 
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
}
void loop()
  { 
  
  myservo.write(90);//setservo position according to scaled value
  delay(500);
  long duration, cm,rightDistance,leftDistance;
 
  duration = getduration();
  
  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
    
  getstr=Serial.read();
 if(getstr=='f')
  {
    _mForward();
  }
  else if(getstr=='b')
  {
    _mBack();
    delay(200);
  }
  
  else if(getstr=='s')
  {
    _mStop(); 
	delay(1000);
	 
	myservo.write(0);
    delay(2000);
	duration = getduration();
	rightDistance = microsecondsToCentimeters(duration);
	Serial.println("rightDistance=");
	Serial.print(rightDistance);
	
	myservo.write(180);
    delay(2000);
	duration = getduration();
	leftDistance = microsecondsToCentimeters(duration);
	Serial.println("leftDistance=");
	Serial.print(leftDistance);
	
	getstr=Serial.read();
	
	if(getstr=='l')
    {
		_mleft();
		delay(1000);
    }
    else if(getstr=='r')
    {
		_mright();
		delay(1000);
    }
  }
  else if(getstr=='A')
  {
  stateChange();
  }
}

