
int tvolt = 3720; //threshold voltage 
unsigned long time; //time in between heartbeats 
volatile bool heartbeat = false; //heartbeat volatile so interrupts can handle it
int bpm; 

//function here to calculate bpm and such
void IRAM_ATTR beat()
{
  heartbeat = true; 
}

void calcBPM()
{
  //time is in miliseconds so you have to adjust the value accordingly
  bpm = 1/(time/(1000*60)); 
  Serial.print("BPM: ")
  Serial.println(bpm)
  time = 0; //resets the time
  heartbeat = false; //resets the heartbeat
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT); 

  attachInterrupt(digitalPinTo,beat,FALLING);

  Serial.begin(9600)
}

void loop() {
  // put your main code here, to run repeatedly:

  // read the voltage from the main circuit
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue); 
  delay(1) //delay for stability

  //check if there's a beat
  if (heartbeat)
  {
    time = millis();
    calcBPM();
  }

}
