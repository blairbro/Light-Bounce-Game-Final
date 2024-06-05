#include <Adafruit_CircuitPlayground.h>

int switchpin = 7;
int rbuttonpin = 5;
int lbuttonpin = 5;
volatile int gamestate = 0;
volatile bool lbuttonflag = false;
volatile bool rbuttonflag = false;
volatile bool switchflag = false;
volatile int speedvalue = 2;
volatile int score = 0;
float midi[127];
int A_four = 440;
int i = 2;
void switchISR(){
  switchflag = true;
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
  pinMode(switchpin, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  Serial.println(gamestate);
  if (gamestate == 0){
    Serial.println("game is either over or paused, press right button to restart/continue");
  }
  if (switchflag){
    CircuitPlayground.playTone(60, 100);
    gamestate = 0;
  }
  if (gamestate == 0 && rbuttonflag){
    gamestate = 1;
  }
  if (gamestate == 1){
    CircuitPlayground.clearPixels();
    delay(speedvalue);
    i++;
    CircuitPlayground.setPixelColor(i, 200, 0, 255);
  }
  if (gamestate == 1 && lbuttonflag){
    CircuitPlayground.playTone(61, 100);
    score++;
    speedvalue*(2/3);
    gamestate = 2;
  }
  if (gamestate == 2){
    CircuitPlayground.clearPixels();
    delay(speedvalue);
    i--;
    CircuitPlayground.setPixelColor(i, 200, 0, 255);
  }
  if (gamestate == 2 && rbuttonflag){
    CircuitPlayground.playTone(62, 100);
    score++;
    speedvalue=speedvalue*(2/3);
    gamestate = 1;
  }
  if (i == 1 or i == 8){
    CircuitPlayground.playTone(55, 500);
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
    i=2;
    gamestate=0;
  }
}
