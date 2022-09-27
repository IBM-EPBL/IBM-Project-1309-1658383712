// C++ code
//
void setup()
{
  pinMode(2, INPUT);
  pinMode(11, OUTPUT);
  pinMode (4, OUTPUT) ;
  pinMode (3, INPUT);
  Serial.begin(9600);
}

void loop()
{
  	//Potentiometer
  	int a=analogRead(A0);
  	analogWrite(11,a/4);
  	//Push Button
  	a=digitalRead(2);
  	if(a==0)
    	digitalWrite(11,HIGH);
  	//Temp Sensor
  	double b=analogRead(A1);
	Serial.print("Temp In C : ");
	Serial.println((5*b/1024-0.5)*100);
    digitalWrite(4, LOW);
    digitalWrite(4, HIGH);
    delayMicroseconds (10);
    digitalWrite(4, LOW);
    float dur = pulseIn (3, HIGH);
    float dis =(dur*0.0343)/2;
    Serial.print ("Distance is ");
    Serial.println(dis);
	delay(2000);
}