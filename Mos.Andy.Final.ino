/*
Student Name: Andy Mos
Course Code: TEJ2O
Teacher: Mr. So
Project Name: Gaming Security System
Project Description: This project is a security system. After 1 minute of calibration, the PIR Sensor starts looking for other people. If people are
                     detected, the system will activate and ask the person for a pin. If the person enters the correct pin, nothing happens. If the
                     person fails to enter the pin 3 times, the security system will start emiting noise, designed to alert others to the intruder.
Date of completion: Project building & coding: December 13, 2021
Date of total project completion: TBD
*/

// PIN is 1243.
// LED is used to refer to the RGB LED.
// LCD is used to refer to the LCD Display.
// PIR is used to refer to the PIR Sensor.
// This program uses "person" and "user" to refer to the entity detected by the sensor and that has to enter the pin.

#include <LiquidCrystal.h> // Get LCD library.

int LEDredPin = A0; // Assign RGB LED red pin to analog pin 0.
int LEDgreenPin = A1; // Assign RGB LED green pin to analog pin 1.
int LEDbluePin = A2; // Assign RGB LED blue pin to analog pin 2.
int PIRPin = 7; // Assign PIR Sensor OUT pin to digital pin 7.
int PIRState; // Create a varibale for the PIR Sensor State.
int button1Pin = 6; // Assign Button 1 pin to digital pin 6.
int button2Pin = 5; // Assign Button 2 pin to digital pin 5.
int button3Pin = 4; // Assign Button 3 pin to digital pin 4.
int button4Pin = 3; // Assign Button 4 pin to digital pin 3.
int button1State; // Create a variable for button 1's state.
int button2State; // Create a variable for button 2's state.
int button3State; // Create a variable for button 3's state.
int button4State; // Create a variable for button 4's state.
int buzzerPin = 2; // Assign buzzer pin to digital pin 2.
bool num1Pass = false; // Create a variable for weather or not the person has correctly entered the first number.
bool num2Pass = false; // Create a variable for weather or not the person has correctly entered the second number.
bool num3Pass = false; // Create a variable for weather or not the person has correctly entered the third number.
int limit = 0; // Create a variable for attempt limit.
int x = 0; // Variable for PIR Sensor calibration delay.
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); // Create an instance of the LCD Display, connected to digital pins 13, 12, 11, 10, 9, and 8.

void setup() {
  lcd.begin(16, 2); // Start the LCD Display, with 2 rows and 16 colums.
  pinMode(LEDredPin, OUTPUT); // Declare pin A0 to be an output.
  pinMode(LEDgreenPin, OUTPUT); // Declare pin A1 to be an output.
  pinMode(LEDbluePin, OUTPUT); // Declare pin A2 to be an output.
  pinMode(buzzerPin, OUTPUT); // Declare digital pin 2 to be an output.
  pinMode(PIRPin, INPUT); // Declare pin 7 to be an input.
  pinMode(button1Pin, INPUT); // Declare button 1 to be an input.
  pinMode(button2Pin, INPUT); // Declare button 2 to be an input.
  pinMode(button3Pin, INPUT); // Declare button 3 to be an input.
  pinMode(button4Pin, INPUT); // Declare button 4 to be an input.
}

void loop() {
  LEDSetColor(0, 0, 0); // Turn the LED off.
  if (x == 0){ // If statement here to make sure the delay only happens once.
    delay(65000); // Wait ~60 seconds to allow the PIR Sensor to calibrate.
    x = 1; // Change the variable so that the delay no longer happens.
  }
  lcdRewrite("Security System."); // Print "Security System." to the LCD Display.
  PIRState = digitalRead(PIRPin); // Get PIR Sensor state.
  if (PIRState == 1) { // If motion is detected...
    bool active = true; // Turn on the security system.
    limit = 0; // Make sure the limit is at 0.
    while (active){ // While the security system is active...
      LEDSetColor(255, 255, 0); // Turn on the LED and make it yellow.
      lcdRewrite("Person detected."); // Print "Person detected." to the LCD Display.
      delay(3000); // Wait 3 seconds.
      lcdRewrite("Enter PIN."); // Make the LCD Display ask the person for the pin.
      delay(2000); // Wait 2 seconds.
      do{ // Do the following...
        if (num1Pass == true){ // If the user has already correctly entered number 1...
          goto num2; // Go to the code for the second number (Line 67).
        }
        lcdRewrite("First number?"); // Make the LCD ask the person for the first number.
        buttonRead(); // Get the states of all the buttons.
        if (button1State == 1){ // If the person pressed 1...
          LEDSetColor(0, 255, 0); // Make the RGB LED turn green.
          lcdRewrite("Correct."); // Print "Correct." to the LCD.
          num1Pass = true; // Note that the user has correctly entered the first number.
          delay(1000); // Wait 1 second.
          num2: // Label for second number code. (For the goto statement on line 58.)
          if (num2Pass == true){ // If the person has already correctly entered the second number...
            goto num3; // Go to the code for number 3 (Line 78).
          }
          lcdRewrite("Second number?"); // Make the LCD ask the user for the second number.
          buttonRead(); // Get the state of all the buttons.
          if (button2State == 1){ // If the user pressed 2...
            LEDSetColor(0, 255, 0); // Make the LED green.
            lcdRewrite("Correct."); // Print "Correct" to the LCD.
            num2Pass = true; // Note that the user has correctly entered the second number.
            delay(1000); // Wait 1 second.
            num3: // Label for third number code. (For the goto statement on line 69.)
            if (num3Pass == true){ // If the user has already correctly entered number 3...
              goto num4; // Go to the code for the fourth number (Line 89).
            }
            lcdRewrite("Third number?"); // Make the LCD ask the user for the third number.
            buttonRead(); // Get the state of all the buttons.
            if (button4State == 1){ // If the user pressed 4...
              LEDSetColor(0, 255, 0); // Make the LED green.
              lcdRewrite("Correct."); // Print "Correct." to the LCD.
              num3Pass = true; // Note that the user has correctly entered the third number.
              delay(1000); // Wait 1 second.
              num4: // Label for code for final number. (For the go to statement on line 80.)
              lcdRewrite("Final number?"); // Make the LCD ask the user for the final number.
              buttonRead(); // Get the states of the buttons.
              if (button3State == 1){ // If the user pressed 3...
                LEDSetColor(0, 255, 0); // Make the LED green.
                lcdRewrite("Correct."); // Print "Correct." to the LCD.
                delay(1000); // Wait 1 second.
                lcdRewrite("Disarming..."); // Print "Disarming..." to the LCD.
                delay(3000); // Wait 3 seconds.
                lcdRewrite("Disarmed."); // Print "Disarmed." to the LCD.
                delay(2000); // Wait 2 seconds.
                active = false; // Turn off the security system.
                num1Pass = false; // Reset the system.
                num2Pass = false; // Reset the system.
                num3Pass = false; // Reset the system.
              }
              else if ((button1State == 1) || (button2State == 1) || (button4State == 1)){ // If the user pressed something other than 3 for the final number...
                LEDSetColor(255, 0, 0); // Make LED red.
                lcdRewrite("Incorrect."); // Print "Incorrect." to the LCD.
                delay(1000); // Wait 1 second.
                lcdRewrite("Skill issue."); // Print "Skill issue." to the LCD.
                delay(1500); // Wait 1.5 seconds.
                limit += 1; // Add one to the limit counter.
              }
            }
            else if ((button1State == 1) || (button2State == 1) || (button3State == 1)){ // If the user pressed something other than 4 for the third number...
              LEDSetColor(255, 0, 0); // Make LED red.
              lcdRewrite("Incorrect."); // Print "Incorrect." to the LCD.
              delay(1000); // Wait 1 second.
              limit += 1; // Add one to the limit counter.
            }
          }
          else if ((button1State == 1) || (button3State == 1) || (button4State == 1)){ // If the user pressed something other than 2 for the second number...
            LEDSetColor(255, 0, 0); // Make LED red.
            lcdRewrite("Incorrect."); // Print "Incorrect." to the LCD.
            delay(1000); // Wait 1 second.
            limit += 1; // Add one to the limit counter.
          }
        }
        else if ((button2State == 1) || (button3State == 1) || (button4State == 1)){ // If the user pressed something other than 1 for the first number...
          LEDSetColor(255, 0, 0); // Make LED red.
          lcdRewrite("Incorrect."); // Print "Incorrect." to the LCD.
          delay(1000); // Wait 1 second.
          limit += 1; // Add one to the limit counter.
        }
        if (limit == 3){ // If the limit has been reached...
          LEDSetColor(255, 0, 0); // Make LED red.
          lcdRewrite("Too many fails."); // Make the LCD tell the user that they have failed too many times.
          tone(buzzerPin, 440); // Activate the buzzer.
          delay(5000); // Wait 5 seconds.
          noTone(buzzerPin); // Turn off the buzzer.
          active = false; // Turn off the security system.
          num1Pass = false; // Reset the system.
          num2Pass = false; // Reset the system.
          num3Pass = false; // Reset the system.
        }
        delay(100); // Wait 100ms.
      } while(active); // ... while the security system is active.
    }
  }
  delay(100); // 100ms delay for stability.
}

void LEDSetColor(int red, int green, int blue){ // Function for changing color of the LED. Takes the red value, green value, and blue value as parameters.
  analogWrite(LEDredPin, 255-red); // Change the red LED to the red color value provided.
  analogWrite(LEDgreenPin, 255-green); // Change the green LED to the green color value provided.
  analogWrite(LEDbluePin, 255-blue); // Change the blue LED to the blue color value provided.
}

void lcdRewrite(char text[]){ // Function for changing the text on the LCD. Takes the text to print to the LCD as a parameter.
  lcd.clear(); // Clear the LCD.
  lcd.setCursor(0, 0); // Set the cursor position to 0,0 on the grid.
  lcd.print(text); // Print the text provided.
}

void buttonRead(){ // Get all the button states.
  button1State = digitalRead(button1Pin); // Get button 1 state.
  delay(1000*button1State); // If button 1 has been pushed, wait 1 second.
  button2State = digitalRead(button2Pin); // Get button 2 state.
  delay(1000*button2State); // If button 2 has been pushed, wait 1 second.
  button3State = digitalRead(button3Pin); // Get button 3 state.
  delay(1000*button3State); // If button 3 has been pushed, wait 1 second.
  button4State = digitalRead(button4Pin); // Get button 4 state.
  delay(1000*button4State); // If button 4 has been pushed, wait 1 second.
}
