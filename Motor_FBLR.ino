//MOTOR_FBLR// Define motor control pins for Motor 1
const int motor1Pin1 = A0;   // IN1 on L298
const int motor1Pin2 = A1;   // IN2 on L298

// Define motor control pins for Motor 2
const int motor2Pin1 = A2;  // IN3 on L298
const int motor2Pin2 = A3;  // IN4 on L298     


void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize motor control pins as OUTPUT
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Initially stop both motors
  stopMotors();
}

void loop() {
  // Check if serial input is available
  if (Serial.available()) {
    char command = Serial.read();  // Read the input character from Serial Monitor
    
    // Motor control based on command
    if (command == 'F' || command == 'f') {
      moveForward();
      Serial.println("Motors Moving Forward");
    }
    else if (command == 'B' || command == 'b') {
      moveBackward();
      Serial.println("Motors Moving Backward");
    }
    else if (command == 'L' || command == 'l') {
      turnLeft();
      Serial.println("Turning Left");
    }
    else if (command == 'R' || command == 'r') {
      turnRight();
      Serial.println("Turning Right");
    }
    else if (command == 'S' || command == 's') {
      stopMotors();
      Serial.println("Motors Stopped");
    }
    else {
      // If the command is not recognized
      Serial.println("Invalid Command. Use 'F' for Forward, 'B' for Backward, 'L' for Left, 'R' for Right, or 'S' for Stop.");
    }
  }
}

// Function to move both motors forward
void moveForward() {
  // Motor 1 Forward
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  
  // Motor 2 Forward
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to move both motors backward
void moveBackward() {
  // Motor 1 Backward
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  
  // Motor 2 Backward
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Function to turn left (Left motor backward, Right motor forward)
void turnLeft() {
  // Motor 1 Backward (Left motor)
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  
  // Motor 2 Forward (Right motor)
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to turn right (Left motor forward, Right motor backward)
void turnRight() {
  // Motor 1 Forward (Left motor)
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  
  // Motor 2 Backward (Right motor)
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Function to stop both motors
void stopMotors() {
  // Stop Motor 1
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  
  // Stop Motor 2
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}