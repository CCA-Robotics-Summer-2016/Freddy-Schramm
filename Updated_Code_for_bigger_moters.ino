/*
   I am Abrar
   this is the program for controlling my robot 
   with a distance measuring sensor
   if it gets too close to something, it looks 
   for a clear path away

   Modified by Michael in class on June 10

   Modified slightly more by Michael before 
   uploading to class blog on June 11
*/
    

// Control pins for the right half of the H-bridge
const int enable2 = 9; // PWM pin for speed control
const int in3 = 8;
const int in4 = 7;

//other half
const int enable1 = 6; // PWM pin for speed control
const int in1 = 4;
const int in2 = 2;

// ultrasonic distance measuring sensor
const int trigPin = 12;
const int echoPin = 11;

void setup() {

  Serial.begin (9600);

  // pins for the ultrasonic distance measuring sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // motors
  pinMode( enable1, OUTPUT);
  pinMode( in1, OUTPUT);
  pinMode( in2, OUTPUT);

  pinMode( enable2, OUTPUT);
  pinMode( in3, OUTPUT);
  pinMode( in4, OUTPUT);

  // Set the speed to 100, which is pretty slow
  analogWrite (enable1, 255);
  analogWrite (enable2, 255);
}

void loop() {

  long distance;

  distance = measureDistance();

  // check validity of distance reading
  if (distance >= 200 || distance <= 0) {
    Serial.println("Going forward reading straight ahead");
    // go forward for just a little bit
    goForward(500);
  } else {

    if (distance <= 35 ) { 
      // turn left a bit; take measurement 
      // turn right a bit; take measurement 
      // go whereever is more distance 

      // Might need to adjust the turn duration 
      turnLeft(3000); // turn left for 50 milliseconds 

      int leftDistance = measureDistance(); 

      // Might need to adjust the turn duration 
      // In theory, 50 milliseconds to get forward, 
      // then another 50 to turn right the same amount 
      turnRight(6000); 
      int rightDistance = measureDistance(); 
      turnLeft(3000); // return to forward 

      // check validity of both readings 
      if (leftDistance >= 200
          || leftDistance <= 0 
          || rightDistance >= 200
          || rightDistance <= 0) 
       { 
         Serial.println("Either the left or right distance reading is bad"); 
         // better not do anything } 
         // otherwise, check to see if left or right 
         // is the better path 
       }else if (leftDistance > rightDistance ) {
        turnLeft(3000);
      } else {
        turnRight(3000);

      }

    } // end of case where distance is less than 30

    // otherwise, distance is greater than 30, we
    // can proceed forward
    else {
      goForward (6000);
    }
  } 
  
   if (distance <= 15 || distance <= 0) {
    Serial.println("too close, turning around");
    // go forward for just a little bit
    turnAround(6500);
  }
  
  // end of what to do if we have a valid reading
} // end of loop

// go forward for a certain amount of time
void goForward(int timeToMove) {

  // left motor
  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  // Right motor
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);

  delay (timeToMove);
}

// turn left for a certain amount of time
void turnLeft(int timeToMove) {

  // left motor
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  // Right motor
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);

  delay (timeToMove);
}

// turn right for a certain amount of time
void turnRight(int timeToMove) {

  // left motor
  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  //Right motor
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);

  delay (timeToMove);
}




void turnAround(int timeToMove) {


  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);

  //RIGHT MOTER
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);

  delay (timeToMove);
}

// Take a measurement using the ultrasonic discance
// measuring sensor and return the distance in cm
// no error checking takes place

long measureDistance() {
  long duration, distance;

  // measure how far anything is from us
  // send the pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // low for 2 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // high for 10 microseconds
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // measure the time to the echo
  distance = (duration / 2) / 29.1; // calculate the distance in cm
  return distance;
}
