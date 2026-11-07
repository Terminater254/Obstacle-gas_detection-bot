const int led1 = 9;//Green
const int led2 = 10;//Yellow
const int led3 = 11;//Red?
const int buzzer = 3;
const int trigPin = 7;
const int echoPin = 6;
const int gasPin = A0;

const int gasLimit = 500;

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(gasPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  long dist = getDistance();
  int gasValue = analogRead(gasPin);

    Serial.print("Dist: "); Serial.print(dist); 
    Serial.print(" cm | Gas: "); Serial.println(gasValue);

  allLEDsOff();

  if (gasValue > 500){
    redLEDOn();
    alarmSound(3);
    Serial.println("Gas Leackage! DANGER!");
    delay(2000);
  }
  else if (dist > 0 && dist < 50){
    blinkedLED(11, 5);
    beepSound(800);
    Serial.println("YOU ARE ABOUT TO HIT AN OBSTACLE!");
    delay(2000);
  }
  else if (dist < 200){
    blinkedLED(10, 5);
    beepSound(300);
    Serial.println("Obstacle detected!");
    delay(2000);
  }
  else{
    greenLEDOn();
    noTone(buzzer);
    Serial.println("You are safe.");
    delay(2000);
  }

  delay(2000);

}

long getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 999;

  return duration * 0.034 / 2;
}
void redLEDOn(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
}
void greenLEDOn(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}
void allLEDsOff(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}
void blinkedLED(int pin, int times){
  for (int i = 0; i < times; i++){
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(500);
  }
}

void beepSound(int freq){
  tone(buzzer, freq, 150);
  delay(2000);
}
void alarmSound(int times){
  for (int i = 0; i < times; i++){
    tone(buzzer, 1000, 300);
    delay(400);
    tone(buzzer, 500, 300);
    delay(400);
  }
}