// Author: Nhanrunandgo - written on 5Jan2023 - Team Ra Dẻ participated in LED Hackathon of NES HCMUS
const int pulseSignal = 100; // Increase this value in case the sound is too loud, otherwise decrease it
int Prev = 0;
void OnAir(int Present) // Manage leds
{
  if(Present > 12) Present = 12;
  for(int i = min(Present, Prev) + 1; i <= max(Prev, Present); i++)
    digitalWrite(i, (Present > Prev)); // Only switch needed lights on or off to reduce time complexity
  Prev = Present; // update the current status
}

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(A2, INPUT); // initialize pin of microphone to read it

  for(int i = 2; i <= 12; i++)
    pinMode(i, OUTPUT); // initialize pins of the lights connect to AVR
}

int ActiveLights;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(A2); 
    if (sample < 1024)  // toss out spurious readings
    {
        if (sample > signalMax)
        {
          signalMax = sample;  // save just the max levels
        }
        else if (sample < signalMin)
        {
          signalMin = sample;  // save just the min levels
        }
    }
  }
  peakToPeak = signalMax - signalMin;
  //Serial.println(peakToPeak);

  ActiveLights = map(peakToPeak, 0, pulseSignal, 1, 12);
  OnAir(ActiveLights);
}
