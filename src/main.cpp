#include <Arduino.h>  // This isn't needed if you are using arduino IDE
#include <ESP32Servo.h> // To use the servo with an ESP32 

#define CUSTOM_SETTINGS  
#define INCLUDE_GAMEPAD_MODULE // Including the gamepad module to configure the GUI in the mobile app
#include <DabbleESP32.h> // Include the Dabble library to enable bluetooth RC functionnality throught your phone

// Right motot pins (you can use the left but don't forget to wire it correctly)
int enableRightMotor = 23;
int RightMotorPin1 = 18;
int RightMotorPin2 = 19;

// Defining Servo motor pin and Variable
#define SERVO_PIN 13
Servo myServo;

// Maximum speed for the DC motor 
#define MAX_MOTOR_SPEED 255

// Declaring the PWM frequency, resolution, and channel of the DC motor
const int PWMFreq = 1000;
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;

// Moving forward or backward function 
void rotateMotor(int Speed)
{
  if (Speed < 0)
  {
    digitalWrite(RightMotorPin1, LOW);
    digitalWrite(RightMotorPin2, HIGH);
  }
  else if (Speed > 0)
  {
    digitalWrite(RightMotorPin1, HIGH);
    digitalWrite(RightMotorPin2, LOW);
  }
  else
  {
    digitalWrite(RightMotorPin1, LOW);
    digitalWrite(RightMotorPin2, LOW);
  }

  // write the spped to the DC motor on the corresponding channel
  ledcWrite(rightMotorPWMSpeedChannel, abs(Speed));
}

// Pins Setup function
void setUpPinModes()
{
  // Configurging the motor pins as outputs
  pinMode(enableRightMotor, OUTPUT);
  pinMode(RightMotorPin1, OUTPUT);
  pinMode(RightMotorPin2, OUTPUT);

  // Associate the servo motor the his GPIO pin with configuring his mininum value(500 -> 0 degrees) and maximum value (2400 -> 180 degrees)
  myServo.attach(SERVO_PIN, 500, 2400);

  // Sets up the PWM channel
  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);

  // Link a specific GPIO pin to the PWM channel
  ledcAttachPin(enableRightMotor, rightMotorPWMSpeedChannel);

  // Initially the motor is Stopped and the servo is configured in a way that the front and back wheels axis are parallels
  rotateMotor(0);
  myServo.write(90);
}

void setup()
{
  // Calling the setup function
  setUpPinModes();

  // Using dabble and assowicate this name for the car (you can chose whatever you want)
  Dabble.begin("MyBluetoothCar");
}

void loop()
{
  // Declaring initial speed
  int Speed = 0;

  // Analyse input from the Dabble app
  Dabble.processInput();

  // If isUp button is pressed then move forward
  if (GamePad.isUpPressed())
  {
    Speed = MAX_MOTOR_SPEED;
  }

  // If isDown button is pressed then move backward 
  else if (GamePad.isDownPressed())
  {
    Speed = -MAX_MOTOR_SPEED;
  }

  // If isRight button is pressed the deviate to the right
  else if (GamePad.isRightPressed())
  {
    myServo.write(105); // Change this depending on the servo's position in the car chasis you are using
  }

  // If isLeft button is pressed the deviate to the left
  else if (GamePad.isLeftPressed())
  {
    myServo.write(80); // Change this depending on the servo's position in the car chasis you are using
  }

  // If isCircle button is pressed the return the front wheels to their initial position 
  else if (GamePad.isCirclePressed()) 
    myServo.write(90);

  // If none of the above is presseed then the car stops
  else
  {
    Speed = 0;
  }

  // Using Serial Monitor for debugging purposes
  Serial.print("Motor Speed: ");
  Serial.println(Speed);

  // Calling the moving function depending on the speed variable
  rotateMotor(Speed);
}
