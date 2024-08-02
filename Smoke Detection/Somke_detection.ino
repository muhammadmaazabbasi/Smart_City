
#define Smoke A0
#define Buz 3
#define Ex 4 


void setup() {
  Serial.begin(9600);

  pinMode(Smoke, INPUT);
  pinMode(Buz, OUTPUT);
  pinMode(Ex, OUTPUT);

}

void loop() {
  int SmokeVal = analogRead(Smoke);
  Serial.println(SmokeVal);
  if(SmokeVal > 230){
    digitalWrite(Buz, HIGH);
    digitalWrite(Ex, HIGH);
    
  }
  else{
    digitalWrite(Buz, LOW);
    digitalWrite(Ex, LOW);
  }                                   
}
