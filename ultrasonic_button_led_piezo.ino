//Output
const int ledPin = 13;
const int piezoPin = 4;

//Button
const int buttonPin = 10;
int buttonVal;

//Sensor
const int trigPin = 8;
const int echoPin = 9;
long duration;
int distance;

//Alarm boolean
bool alarm = false; 

//Timer
unsigned long currentTime;
unsigned long previousTime = 0;
int timerLength = 500; 


void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

}

void loop()
{
  buttonVal = digitalRead(buttonPin);
  
  currentTime = millis(); 
        
  if(!alarm){
    
    if(buttonVal == HIGH){
      alarm = !alarm; 
    }
    
  } else {
  //Turn on sensor
	ultraSensor(); 
    
    if(distance <= 50){
      
      //USING TIMER :)
      if(currentTime - previousTime>timerLength){
        
        digitalWrite(ledPin, HIGH);
        previousTime = currentTime;//Reset Timer 
        
      } else {
        
        digitalWrite(ledPin, LOW);
        
      }   
      
      //DOESN'T MESS WITH SOUND! 
      tone(piezoPin, 440); //pin, freq
      
      
    } else {
      //LED & Sound off 
      digitalWrite(ledPin, LOW); 
      noTone(piezoPin); 
    }
  }
  
    
    
}

void ultraSensor(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
 // Serial.print("Distance: ");
 // Serial.println(distance); 
}