 volatile long int count, last=0,sum;
volatile int c=0;
void isr();
void pid();
int setpoint =3000;
int error;
int lasterror;
float kp=4.0, ki=0.0 , kd=0.0;
float dt,  tim, ltim=0;
float x,y; 
int errorsum ,errordiff;
int PWM= 13 ;
int DIR = 12 ;
int currentspeed=255;
int speedchange;
void setup()
{
  
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(PWM , OUTPUT);
  pinMode( DIR,OUTPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(18),isr,CHANGE);
  attachInterrupt(digitalPinToInterrupt(19),isr,CHANGE);
 
  tim=millis();
 analogWrite(PWM,-255);
 digitalWrite(DIR,HIGH);
}
void isr()
{
   
 c = (digitalRead(18)<<1)|digitalRead(19);
 
 sum = ((last<<2)|c);
  if((sum==0b1011) || (sum==0b1101) || (sum==0b0100) || (sum==0b0010))
  {
    count = count + 1;
  }
  else if((sum==0b0111)||(sum==0b1110)||(sum==0b1000)||(sum==0b0001))
  {
    count = count - 1;
  }
 last=c;
 
}
void pid()
{
  dt=tim-ltim;
error =count - setpoint;
errordiff = error-lasterror;
errorsum= error + lasterror;
int speedchange =(kp*error)+(errorsum*ki)*dt+(errordiff*kd)/dt;

if(error>0)
  {
    
    analogWrite(PWM,-speedchange);
digitalWrite(DIR,LOW);
  }
 else if(error<0)
  {
   analogWrite(PWM,speedchange);
digitalWrite(DIR,HIGH); 
  }
 else if(error==0)
{
    analogWrite(PWM,0);

}
//Serial.println(error);
//int x=currentspeed+speedchange;
//int y=currentspeed-speedchange;
if (speedchange>255)
speedchange=255;
if(speedchange<0)
speedchange=0;
/*if(y>200)
y=200;
if(y<0)
y=0;
/*analogWrite(PWM,x);
digitalWrite(DIR,HIGH);
analogWrite(PWM,y);
digitalWrite(DIR,HIGH);
*/
lasterror=error;
ltim=tim;

}

  
void loop()
{ 
  pid();
  Serial.println(count);
  
  
  /*while ((count< setpoint)||(count> setpoint))
  {
   if (count < setpoint){
  analogWrite(PWM ,100);
  digitalWrite(DIR , LOW);
  pid();
  }
   if (count > setpoint){
  analogWrite(PWM ,100);
  digitalWrite(DIR , HIGH);
  pid();
  }
  }*/
/*analogWrite(PWM ,255);
  digitalWrite(DIR ,HIGH);
  delay(2000);
 Serial.println(count); 
 analogWrite(PWM ,0);
 delay(1000);
  analogWrite(PWM ,255);
  digitalWrite(DIR ,LOW);
  Serial.println(    count);
 delay(2000);
 analogWrite(PWM ,0);
 delay(1000);

  
  
   Serial.println(           count);
   /* if (count < setpoint){
    //while (count <= setpoint)
  {analogWrite(PWM ,100);
  digitalWrite(DIR ,LOW);
  pid();
  Serial.println(count);}
  }
  else if (count > setpoint){
 // while (count >= setpoint)
  {
  analogWrite(PWM ,100);
  digitalWrite(DIR , HIGH);
  pid();
  Serial.println(count);}
  } 
  else if (count == setpoint)
  analogWrite(PWM ,0); 
   
  Serial.print(    error); 
  
  // for now
 /* analogWrite(PWM ,100);
  digitalWrite(DIR , LOW);
   pid();
/* if(count!= setpoint )
{
   pid(); 
} // add comment here
  
 if(count ==setpoint )
  {
    analogWrite(PWM ,0);
  }
  
  Serial.println(count);*/
}
