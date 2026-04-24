// Stepper Motor Driver Pins
#define directionPin 52 //
#define stepPin 53 //
#define enPin 5 // 
#define enPin2 3 // 

// Buttons Pins
#define BlueLeftPin 51 //Blue (Turn Left) 
#define GreenGoPin 49 //Green (Start) 
#define RedStopPin 50 //Red (Stop) 
#define YellowRightPin 48 //Yellow (Turn Right) 

// Sensors Pins
#define IRpin A0 // Infared LEFT
#define IRpin2 A2 // Infared RIGHT
#define IRpin3 A4 // Infared RIGHT


// Speakers Pins
#define Speaker A1 //  Buzzer LEFT
#define Speaker2 A3 // Buzzer RIGHT
//#define spm 2890  //????????????

// Button inital setup
//int button; // ????????
int lastButtonState2 = HIGH;  // Track Start button
int lastButtonState3 = HIGH; // Track Stop button
int buttonState2 = HIGH;  // Start button initial off
int buttonState3 = HIGH; // Stop button initial off
int buttonState1 = HIGH; // Left button initial off
int buttonState4 = HIGH; // Right button initial off

// Infrared detection setup
int valArray[400]; 
int i=100;
int isturned = 0; 
int isturned2 = 0;
int StopLine = 0;
int val = 0; 
int val2 = 0; 
int val3 = 0;
  
// Ultrasonic Sensors setup
const int trigPin = 30; 
const int echoPin = 32; 

// LED Pins
const int rled = 27; 
const int yled = 25; 
const int bled = 31; 
const int gled = 29; 

float timing = 0.0; 
float distance = 0.0; 

const unsigned long debounceDelay = 50; 
unsigned long lastDebounceTime2 = 0; 
unsigned long lastDebounceTime3 = 0; 


void setup() { 
  // Rear Motor Pins
  pinMode(46, OUTPUT); 
  pinMode(47, OUTPUT);  
  digitalWrite(46, LOW); 
  digitalWrite(47, LOW); 
 
  // Stepper Motor Driver
  pinMode(directionPin, OUTPUT); 
  pinMode(stepPin, OUTPUT); 
  pinMode(enPin, OUTPUT);  
  pinMode(enPin2, OUTPUT);
  
  digitalWrite(enPin, LOW); 
  digitalWrite(directionPin, HIGH);  
 
  // Buttons
  pinMode(BlueLeftPin, INPUT_PULLUP); // Blue
  pinMode(GreenGoPin, INPUT_PULLUP); // Green
  pinMode(RedStopPin, INPUT_PULLUP); // Red
  pinMode(YellowRightPin, INPUT_PULLUP); // Yellow

  // LEDS
  pinMode(rled, OUTPUT); 
  pinMode(yled, OUTPUT); 
  pinMode(bled, OUTPUT); 
  pinMode(gled, OUTPUT); 
  
  // Ultrasonic Sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  digitalWrite(trigPin, LOW); 
  Serial.flush(); 
  
  // Infrared Sensors
  pinMode(IRpin, INPUT); 
  pinMode(IRpin2, INPUT); 
  pinMode(IRpin3, INPUT);

  // Buzzers
  pinMode(Speaker, OUTPUT); 
  pinMode(Speaker2, OUTPUT); 
  digitalWrite(Speaker, LOW); 
  digitalWrite(Speaker2, LOW); 
  Serial.begin(9600); 
} 


void loop() { 
  buttonState1 = digitalRead(BlueLeftPin);  // No debounce for BlueLeftPin 
  buttonState4 = digitalRead(YellowRightPin);  // No debounce for YellowRightPin 
  readButton(GreenGoPin, lastButtonState2, buttonState2, 
  lastDebounceTime2); 
  readButton(RedStopPin, lastButtonState3, buttonState3, 
  lastDebounceTime3); 


  //TURN LEFT BLUE 
if (buttonState1 == LOW) {
  digitalWrite(yled, LOW);
  digitalWrite(rled, LOW);
  digitalWrite(bled, HIGH);
  digitalWrite(directionPin, LOW);

  for (int i = 0; i < 378; i++) {
    digitalWrite(stepPin, LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(3000);
  }
  delay(2500);
  digitalWrite(directionPin, HIGH);
  for (int i = 0; i < 378; i++) {
    digitalWrite(stepPin, LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(3000);
  }
  digitalWrite(directionPin, LOW); // CCW rotation 
  digitalWrite(bled, LOW);
}
  
 //FORWARD 
 if (buttonState2 == LOW) { 
  analogWrite(enPin2, 240); 
  digitalWrite(46, HIGH); 
  digitalWrite(47, LOW); 
  digitalWrite(bled, LOW); 
  digitalWrite(rled, LOW); 
  digitalWrite(yled, LOW); 
  digitalWrite(gled, HIGH); 
 } 
 
 //STOP 
 if ((buttonState3 == LOW )) { 
  analogWrite(enPin2, 0); 
  digitalWrite(46, LOW); 
  digitalWrite(47, LOW); 
  digitalWrite(bled, LOW); 
  digitalWrite(gled, LOW); 
  digitalWrite(yled, LOW); 
  digitalWrite(rled, HIGH); 
 } 

 //TURN RIGHT YELLOW 
 if (buttonState4 == LOW) { 
  digitalWrite(bled, LOW); 
  digitalWrite(rled, LOW); 
  digitalWrite(yled, HIGH); 
  digitalWrite(directionPin, HIGH); 
  for (int i = 0; i < 378; i++) { 
    digitalWrite(stepPin, LOW); 
    digitalWrite(stepPin, HIGH); 
    delayMicroseconds(3000); 
  } 
  delay(2500); 
  digitalWrite(directionPin, LOW); 
  
  for (int i = 0; i < 378; i++) { 
    digitalWrite(stepPin, LOW); 
    digitalWrite(stepPin, HIGH); 
    delayMicroseconds(3000); 
  } 
  digitalWrite(directionPin, HIGH); // CW rotation
  digitalWrite(yled, LOW); 
 }
  
 //INFRARED DETECTION 1 | WHITE LINE ON LEFT
 val = analogRead(IRpin); 
 valArray[i]=val; 
 i++;
  
 if (val < 100 && isturned == 0 && digitalRead(rled)== LOW) { 
  isturned = 1; 
  analogWrite(Speaker, 256); // communicating with the NAO robot ??????
  digitalWrite(directionPin, HIGH); 
  for (int i = 0; i < 150; i++) { 
    digitalWrite(stepPin, LOW); 
    digitalWrite(stepPin, HIGH); 
    delayMicroseconds(3000); 
  } 
 } 
  if (isturned==1){ 
    digitalWrite(bled, LOW); 
    digitalWrite(rled, LOW); 
    digitalWrite(yled, HIGH); 
    if (val > 100) { 
      digitalWrite(directionPin, LOW); 
      for (int i = 0; i < 150; i++) { 
        digitalWrite(stepPin, LOW); 
        digitalWrite(stepPin, HIGH); 
        delayMicroseconds(3000); 
      } 
      digitalWrite(yled, LOW); 
      isturned = 0; 
      analogWrite(Speaker, 0); 
    } 
  } 
  
  //INFRARED DETECTION 2 WHITE LINE ON RIGHT
  val2 = analogRead(IRpin2); 
if (val2 < 100 && isturned2 == 0 && digitalRead(rled)== LOW) { 
  isturned2 = 1; 
  analogWrite(Speaker2, 256); 
  digitalWrite(directionPin, LOW); 
  for (int i = 0; i < 150; i++) { 
    digitalWrite(stepPin, LOW); 
    digitalWrite(stepPin, HIGH); 
    delayMicroseconds(3000); 
  } 
  } 
  if (isturned2==1){ 
    digitalWrite(bled, HIGH); 
    digitalWrite(rled, LOW); 
    digitalWrite(yled, LOW); 
  //Serial.println(val2); 
  if (val2 > 100) { 
    digitalWrite(directionPin, HIGH); 
  for (int i = 0; i < 150; i++) { 
    digitalWrite(stepPin, LOW); 
    digitalWrite(stepPin, HIGH); 
    delayMicroseconds(3000); 
  } 
    digitalWrite(bled, LOW); 
    isturned2 = 0; 
    analogWrite(Speaker2, 0); 
  } 
  } 
  
  //INFRARED DETECTION 3 STOP LINE 
   val3 = analogRead(IRpin3); 
if (val3 < 200 && digitalRead(rled)== LOW) { 
 StopLine = 1;
 analogWrite(Speaker, 256);
 analogWrite(Speaker2, 256);
 for(int i = 0; i<200; i++){
  analogWrite(enPin2, 0); 
  digitalWrite(46, LOW); 
  digitalWrite(47, LOW);
  digitalWrite(rled, HIGH);
  digitalWrite(bled, LOW);    
  digitalWrite(yled, LOW);
  digitalWrite(gled, LOW);
  delayMicroseconds(3000); // Timing for stopline stoping
  }
}
 if(StopLine==1){
    digitalWrite(rled, LOW); 
    StopLine = 0; 
    analogWrite(Speaker, 0); 
    analogWrite(Speaker2, 0); 
 }
  


 //FRONT SENSOR 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH); 
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW); 
 timing = pulseIn(echoPin, HIGH); 
 distance = (timing * 0.034) / 2; 
 Serial.println(distance); 
 if(distance > 40) { 
  digitalWrite(Speaker, LOW); 
  digitalWrite(Speaker2, LOW); 
 } 
 if(distance > 40) { 
  digitalWrite(Speaker, LOW); 
 } 
  delay(30); 
} 
 
void readButton(int pin, int &lastState, int &currentState, unsigned long &lastDebounceTime) { 
  int reading = digitalRead(pin); 
  if (reading != lastState) { 
    lastDebounceTime = millis();  // Reset debounce timer 
  } 
  // Only change the state if the debounce time has passed 
  if ((millis() - lastDebounceTime) > debounceDelay) { 
    if (reading != currentState) { 
      currentState = reading; 
      // You can take action on button press here 
    } 
  } 
  lastState = reading; 
} 
