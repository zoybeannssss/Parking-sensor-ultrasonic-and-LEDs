// conncetion for ultrasonic
const int trigPin = 2;
const int echoPin = 3;

// LEDs and buzzer
const int redLED = 7;
const int greenLED = 5;
const int yellowLED = 6;
const int buzzerPin = 8;

int buzzerState = LOW;

//ultrasonic shooter
long duration;
int distance;

//millisecond ultrasonic (US)
unsigned long previousMillisUS = 0;
const long coolDownUS = 20; //gap between 20 milliseconds

//millisecond buzzer (BZ1)
const long coolDownBZ = 200; //200 millisecond cooldown for each buzzer beeps
unsigned long previousMillisBZ = 0;

//millisecond buzzer (BZ2)
const long coolDownBZ2 = 50; //50 millisecond cooldown for each buzzer beeps
unsigned long previousMillisBZ2 = 0;


void setup() {
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
}


void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisUS >= coolDownUS) {
    previousMillisUS = currentMillis;
     digitalWrite(trigPin, LOW);
     delayMicroseconds(2);
     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(trigPin, LOW);

     long duration = pulseIn(echoPin, HIGH, 30000); //30 millisecond timeout

     distance = duration * 0.034 / 2;
     if (distance > 70) {
     distance = 70; 
}


     Serial.println(distance);

if (distance <= 15) { //less than 15
  digitalWrite(redLED, HIGH);
   digitalWrite(greenLED, LOW);
     digitalWrite(yellowLED, LOW);
     lowAlert();
 }
    else if (distance < 40) { //between 15-40
      digitalWrite(yellowLED, HIGH);
 digitalWrite(greenLED, LOW);
    digitalWrite(greenLED, LOW);
    mediumAlert();


 } else { //more than 40
 digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, LOW);
 digitalWrite(greenLED, HIGH);
 digitalWrite(buzzerPin, LOW);      

 } 
  }

}


void mediumAlert() {
  
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillisBZ >= coolDownBZ) {
    previousMillisBZ = currentMillis;
    if (buzzerState == LOW) {
      buzzerState = HIGH;
    } else {
      buzzerState = LOW;
    }
    
    digitalWrite(buzzerPin, buzzerState);

  }
}

void lowAlert() {
  
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillisBZ2 >= coolDownBZ2) {
    previousMillisBZ2 = currentMillis;
    if (buzzerState == LOW) {
      buzzerState = HIGH;
    } else {
      buzzerState = LOW;
    }
    digitalWrite(buzzerPin, buzzerState);

  }
}