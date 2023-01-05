// Author: Nguyen Dinh Nhan - written on 5Jan2023 - Team Ra Dẻ participated in LED Hackathon of NES HCMUS
int Prev = 0;
void OnAir(int Present)
{
  if(Present > 12) Present = 12;
  for(int i = min(Present, Prev) + 1; i <= max(Prev, Present); i++)
    digitalWrite(i, (Present > Prev)); // Only get lights from D2 to D12
  Prev = Present;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A2, INPUT);

  for(int i = 2; i <= 12; i++)
    pinMode(i, OUTPUT); // initialize pins of the lights connect to AVR
}

int cnt = 0, val;
int Min = 1000, Max = -1000; // Assume they are infinity
void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A2);
  if(cnt++ < 20) // Take 20 samples 
  {
    Min = min(Min, val);
    Max = max(Max, val);
  }
  else // Then process
  {
    int ActiveLights = map(Max - Min, 0, 250, 1, 12);
    OnAir(ActiveLights); // Control Leds to follow the present value
    Serial.println(ActiveLights);

    // Reset the values
    cnt = 0;
    Min = 1000, Max = -1000;
  }
}
