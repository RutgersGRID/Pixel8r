#include <Bounce.h>

// pin assignments
const int arrowUpPin = 17;  
const int arrowDownPin = 15;
const int arrowLeftPin = 16;
const int arrowRightPin = 19;
const int homePinPin = 22;
const int galaxyPinPin = 32; //changed for 3.5, was using 3.6 board schematic
const int expandPin = 21;
const int contractPin = 20;
const int mouseClickPin = 23; 

const int trPin1 = 31; //zoom in  //see 32
const int trPin2 = 18; //zoom out

const int debounceTime = 10;
const int analogThreshold = 900;
const int mouseThreshold = 950;

int zoomIn;
int zoomOut;
// teensy 3.2
  Bounce homePin = Bounce(homePinPin, debounceTime);
  Bounce galaxyPin = Bounce(galaxyPinPin,debounceTime);
  Bounce expand = Bounce(expandPin,debounceTime);
  Bounce contract = Bounce(contractPin, debounceTime);
void setup() {

  pinMode(arrowUpPin, INPUT_PULLUP);
  pinMode(arrowDownPin, INPUT_PULLUP);
  pinMode(arrowLeftPin, INPUT_PULLUP);
  pinMode(arrowRightPin, INPUT_PULLUP);
  pinMode(expandPin, INPUT_PULLUP);
  pinMode(contractPin, INPUT_PULLUP);
  pinMode(homePinPin, INPUT_PULLUP);
  pinMode(galaxyPinPin, INPUT_PULLUP);
  pinMode(mouseClickPin, INPUT_PULLUP);
  pinMode(trPin1, INPUT_PULLUP);
  pinMode(trPin2, INPUT_PULLUP);

  Mouse.screenSize(1920, 1080, true);  // configure screen size
  Serial.begin(9600);
  delay(3000);
}

void loop() {

  //Serial.println(analogRead(mouseClickPin));
  homePin.update();
  galaxyPin.update();
  expand.update();
  contract.update();
  //mouseClick.update();
  // for reference: https://www.pjrc.com/teensy/td_keyboard.html
  //if () {} // if the right mouse button is pressed, for click and drag
  // positive x is to the RIGHT
  // positive y is DOWN
  Serial.print(analogRead(mouseClickPin));
  Serial.print("\t");
  Serial.println(analogRead(arrowLeftPin));
 if (analogRead(mouseClickPin) < analogThreshold){ // defaults to high so we want a low to be triggered, so we NOT it.
    Mouse.set_buttons(1,0,0); //aalways be clicking so our mouse can move
    if (analogRead(arrowUpPin) < mouseThreshold) {Mouse.move(0, -30);} 
    if (analogRead(arrowDownPin) < mouseThreshold) {Mouse.move(0,30);}
    if (analogRead(arrowLeftPin) < mouseThreshold) {Mouse.move(-30,0);}
    if (analogRead(arrowRightPin) < mouseThreshold){Mouse.move(30,0);}
    Mouse.set_buttons(0,0,0);
  } //else {Mouse.set_buttons(0, 0, 0);}
  (analogRead(homePinPin) < analogThreshold) ? (Keyboard.press(KEY_SPACE)) : (Keyboard.release(KEY_SPACE));
  (analogRead(galaxyPinPin) < analogThreshold) ? (Keyboard.press(KEY_W)) : (Keyboard.release(KEY_W));
  (analogRead(expandPin) < analogThreshold) ? (Keyboard.press(KEY_A)) : (Keyboard.release(KEY_A));
  (analogRead(contractPin) < analogThreshold) ? (Keyboard.press(KEY_D)) : (Keyboard.release(KEY_D));
  

  if (analogRead(trPin1) < analogThreshold) {
    Mouse.scroll(2);
  }
  else if (analogRead(trPin2) < analogThreshold) {
    Mouse.scroll(-2);
  }

  delay(100);
}
