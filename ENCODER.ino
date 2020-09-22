volatile int count;
void isr();




void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(2),isr,CHANGE);
}
void loop()
{
  Serial.println(count);
      }

void isr()
{
  if(digitalRead(2)==HIGH)
  {
    if(digitalRead(3)==LOW)
    {
      count= count +1;
    }
    else{
    count = count - 1;}
  }
  if(digitalRead(3)==LOW)
  
    {
      count=count +1;
    }
    else
    {
      count = count -1;
    }
  
  
}

  
  
