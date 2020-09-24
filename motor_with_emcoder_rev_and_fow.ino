volatile int count=0;
void isr();




void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),isr,CHANGE);
  attachInterrupt(digitalPinToInterrupt(3),isr,CHANGE);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(9,LOW);
  digitalWrite(8,LOW);
}
void isr()
{
  
  if(digitalRead(2)==HIGH)
  {
    if(digitalRead(3)==LOW)
    {
      
      count = count +1;
    }
  else
  {
    count= count-1;
  }
  }
  else{
  if(digitalRead(3)==LOW)
  {
    count=count+1;
  }
  else
  {
    count= count-1;
  }
  }}



void loop()
{do{
 digitalWrite(9,HIGH);
  digitalWrite(8,LOW);
  
  
    count=count+1;
    Serial.println(count);
  }while(count<=100);
 digitalWrite(8,LOW);
 delay(2000);
  
  count=0;
  do{
  digitalWrite(9,LOW);
  digitalWrite(8,HIGH);
  
    count--;
    Serial.println(count);
  }while(count>-100);
 

  
  
  
}

  
  
