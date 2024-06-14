#include <Adafruit_CircuitPlayground.h>

int switchpin = 7;
int rbuttonpin = 5;
int lbuttonpin = 4;
volatile int gamestate = 0;
volatile bool lbuttonflag = false;
volatile bool rbuttonflag = false;
volatile bool switchflag = false;
volatile int speedvalue = 500;
volatile int score = 0;
float midi[127];
int A_four = 440;
int i = 2;

void switchISR(){
  switchflag = !switchflag;
  Serial.println("Paused");
};

void lbuttonISR(){
  lbuttonflag = true;
};

void rbuttonISR(){
  rbuttonflag = true;
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
};

void setup() {
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(switchpin), switchISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(lbuttonpin), lbuttonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(rbuttonpin), rbuttonISR, RISING);
  generateMIDI();

  Serial.begin(9600);
  while(!Serial);
  Serial.println();
  Serial.println("Rules:");
  Serial.println("1: Press the Right and Left Buttons when the Light is coming towards them in Order to Score Points");
  Serial.println("2: The Light Gets Faster the More You Score");
  Serial.println("3: You Can Pause the Game With the Slide, Press the Start Button Again To Unpause");
  Serial.println("4: If the Light Passes the Buttons, You Lose");
  Serial.println("5: Have Fun, Not Having Fun is Against the Rules :P");
  Serial.println("Press the Right Button to Start the Game");
}

void loop() {
  if (gamestate == 0){ //Functions as a game buffer, either for starting or in pausing, does nothing but halt the game
  }
  if (switchflag){  //Functions as a pause by setting the gamestate to 0
    CircuitPlayground.playTone(60, 100);
    gamestate = 0;
    switchflag = false;
  }
  if (gamestate == 0 && lbuttonflag){ //Starts the game
    gamestate = 1;
    lbuttonflag = false;
  }
  if (gamestate == 1){ //First phase of the game, causes a light to bounce towards the left button (when held correctly) and waits for the button to be pushed
    lbuttonflag = false;
    CircuitPlayground.clearPixels();
    i++;
    CircuitPlayground.setPixelColor(i, 200, 0, 255);
    delay(speedvalue);
    CircuitPlayground.clearPixels();
    if(rbuttonflag){ //if the proper button is pushed, plays a tone, adds score, decreases delay timer, and sets the game to the other active gamestate
      CircuitPlayground.playTone(61, 100);
      score++;
      speedvalue=speedvalue-50;
      gamestate = 2;
      rbuttonflag = false;
    }
  }
  if (gamestate == 2){ //Second active phase of the game. Causes the light to bounce towards the other button and waits for it to be pushed.
    rbuttonflag = false;
    CircuitPlayground.clearPixels();
    i--;
    CircuitPlayground.setPixelColor(i, 200, 0, 255);
    delay(speedvalue);
    CircuitPlayground.clearPixels();
    if(lbuttonflag){
      CircuitPlayground.playTone(62, 100);
      score++;
      speedvalue=speedvalue-50;
      gamestate = 1;
      lbuttonflag = false;
    }
  }
  if (i == 1 || i == 8){
    CircuitPlayground.playTone(55, 500);
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
    Serial.print("Game Over! Your Score is: ");
    Serial.println(score);
    Serial.println("Press the Right Button to Play Again");
    rbuttonflag = false;
    lbuttonflag = false;
    i=2;
    speedvalue = 500;
    score = 0;
    gamestate=0;
  }
}
