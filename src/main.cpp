#include <Arduino.h>
#define RED_LED 1
#define YELLOW_LED 2
#define GREEN_LED 3
#define red_time 10
#define yellow_time 3
#define green_time 10

// put function declarations here:
int myFunction(int, int);

int state = 1;
int flag = 0;
void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state){
    case 1:
      digitalWrite(RED_LED, HIGH);
      delay(red_time * 1000);
      digitalWrite(RED_LED, LOW);
      state = 2;
      //behavior for green button (switch to 2 state)
    break;
    case 2:
      blink(3, RED_LED);
      state = 3;
    break;
    case 3:
      //beh for red button (switch to 1 after timeout)
      //beh for green (switch to 4 after timeout)
      digitalWrite(YELLOW_LED, HIGH);
      delay(yellow_time * 1000);
      digitalWrite(YELLOW_LED, LOW);
      if (flag == 0) // flag to ensure correct switch algorithm
        state = 4;
      else{
          state = 1;
          flag = 0;
      }
        
    break;
    case 4:
    //beh for red button (switch to 5 -> 3)
      digitalWrite(GREEN_LED, HIGH);
      delay(green_time * 1000);
      digitalWrite(GREEN_LED, LOW);
      state = 5;
    break;
    case 5:
      //beh for red button (switch ro yellow and green state (2))
      //beh for green button (switch to yellow and red state (4))
      blink(3, GREEN_LED);
      state = 3;
      flag = 1;
    break;
  }

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
void blink(int times, int led){
  for (int i = 0; i< times; i++){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    i++;
  }
void activateLED(int sec, int led){

  digitalWrite(RED_LED, HIGH);
  delay(red_time * 1000);
  digitalWrite(RED_LED, LOW);
}

}