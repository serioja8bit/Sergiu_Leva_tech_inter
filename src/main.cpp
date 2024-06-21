#include <Arduino.h>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire); //added a 0.96 inch monocrome display for showing timer for traffic light
#define RED_LED 1
#define YELLOW_LED 2
#define GREEN_LED 3
#define red_time 10
#define yellow_time 3
#define green_time 10
#define green_button 7
#define red_button 8
enum button_State{
  PRESSED,
  NOT_PRESSED
};

button_State green_state;
button_State red_state;
int state = 1;
int flag = 0;
void setup() {
  pinMode(green_button, INPUT);
  attachInterrupt(digitalPinToInterrupt(green_button), changeStateofGreen, FALLING);

  pinMode(red_button, INPUT);
  attachInterrupt(digitalPinToInterrupt(red_button), changeStateofRed, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state){
    case 1:
      activateLED(red_time, RED_LED);
      state = 2;
      if (green_state == PRESSED){
        state = 2;
        green_state = NOT_PRESSED;
        break;
      }
    break;
    case 2:
      blink(3, RED_LED);
      state = 3;
    break;
    case 3:
      //beh for red button (switch to 1 after timeout)
      //beh for green (switch to 4 after timeout)
      activateLED(yellow_time, YELLOW_LED);
      if (red_state == PRESSED){
        state = 1;
        red_state = NOT_PRESSED;
        break;
      }
      if (green_state == PRESSED){
        state = 4;
        green_state = NOT_PRESSED;
        break;
      }
      if (flag == 0) // flag to ensure correct switch algorithm
        state = 4;
      else{
          state = 1;
          flag = 0;
      }
        
    break;
    case 4:
    //beh for red button (switch to 5 -> 3)
      if (red_state == PRESSED){
        state = 5;
        green_state = NOT_PRESSED;
        break;
      }
      if (green_state == PRESSED){
        green_state = NOT_PRESSED;
      }
      activateLED(green_time, GREEN_LED);
      state = 5;
    break;
    case 5:
      //beh for red button (switch to yellow and green state (2))
      //beh for green button (switch to yellow and red state (4))
      if (red_state == PRESSED){
        digitalWrite(YELLOW_LED, HIGH); // switch to yelow
        blink(3, GREEN_LED); //switch to oposite color of button
        state = 3;
        flag = 1;
        red_state = NOT_PRESSED;
        digitalWrite(YELLOW_LED, LOW);
        break;
      }
      if (green_state == PRESSED){
        digitalWrite(YELLOW_LED, HIGH);//switch to yellow
        blink(3, RED_LED); //switch to oposite color of button
        state = 3;
        flag = 1;
        red_state = NOT_PRESSED;
        digitalWrite(YELLOW_LED, LOW);
        break;
      }
      blink(3, GREEN_LED);
      state = 3;
      flag = 1;
    break;
  }

}


void blink(int times, int led){
  for (int i = 0; i< times; i++){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    i++;
  }
}
void activateLED(int sec, int led){
  digitalWrite(led, HIGH);
  for (int i = 0; i < sec; i++){
    drawText(i+1);
    delay(1000); // delay for 1 sec
  }
  digitalWrite(led, LOW);
}

void changeStateofGreen(){
    if (green_state == NOT_PRESSED){
      green_state = PRESSED;
    }
    
}
void changeStateofRed(){
    if (red_state == NOT_PRESSED){
      red_state = PRESSED;
    } 
}
void drawText(char number){ // function to draw timer on display
  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(number);
  display.display();
}