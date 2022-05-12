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
//const int expandPin = 31;
//const int contractPin = 18;
const int mouseClickPin = 23;

const int trPin1 = 31; //zoom in  //see 32
const int trPin2 = 18; //zoom out

const int debounceTime = 10;
const int analogThreshold = 925 ;
const int mouseThreshold = 950;

int mCliMax = -1;
int mCliMin = 4000;

int homeMin = 4000;
int homeMax = -1;


int galaxyMin = 4000;
int galaxyMax = -1;

int expandMin = 4000;
int expandMax = -1;

int contractMax = -1;
int contractMin = 4000;



int zoomIn;
int zoomOut;
// teensy 3.2
Bounce homePin = Bounce(homePinPin, debounceTime);
Bounce galaxyPin = Bounce(galaxyPinPin, debounceTime);
Bounce expand = Bounce(expandPin, debounceTime);
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
  //pinMode(trPin1, INPUT_PULLUP);
  //pinMode(trPin2, INPUT_PULLUP);

  Mouse.screenSize(1920, 1080, true);  // configure screen size
  Serial.begin(9600);
  delay(3000);
  Serial.println("Start Diagnostic");

  while (1) {
    int mCli = analogRead(mouseClickPin);
    int homeV = analogRead(homePinPin) ;
    int galaxyV = analogRead(galaxyPinPin) ;
    int expandV = analogRead(expandPin) ;
    int contractV = analogRead(contractPin);


    mCliMin = min(mCliMin, mCli);
    mCliMax = max(mCliMax, mCli);
    printDebug("mCli" , mCli, mCliMin, mCliMax, "CLICK") ;

    homeMin = min(homeMin, homeV);
    homeMax = max(homeMax, homeV);
    printDebug("homeV", homeV, homeMin, homeMax, "KEY_SPACE") ;

    galaxyMin = min(galaxyMin, galaxyV);
    galaxyMax = max(galaxyMax, galaxyV);
    printDebug("galaxyV", galaxyV, galaxyMin, galaxyMax, "KEY_W") ;

    expandMin = min(expandMin, expandV);
    expandMax = max(expandMax, expandV);
    printDebug("expandV", expandV, expandMin, expandMax, "KEY_A") ;

    contractMin = min(contractMin, contractV);
    contractMax = max(contractMax, contractV);
    printDebug("contractV", contractV, contractMin, contractMax, "KEY_D") ;


    delay(100);

    if (Serial.available() > 0)
    {
      char cc = Serial.read();
      if (cc == 's' || cc == '?') {
        Serial.println("Start Program");

        break;
      }
      if (cc == 'r') {
        Serial.println("Reset Min Max");
        mCliMin = 1024;
        mCliMax = 0;

        homeMin = 1024;
        homeMax = 0;

        galaxyMin = 1024;
        galaxyMax = 0;

        expandMin = 1024;
        expandMax = 0;

        contractMin = 1024;
        contractMax = 0;
      }
    }
  }
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
  Serial.print("mCli: ");
  Serial.print(analogRead(mouseClickPin));
  Serial.print(" > Thresh: ");
  Serial.println(analogThreshold);
  //if (analogRead(mouseClickPin) < analogThreshold) { // defaults to high so we want a low to be triggered, so we NOT it.
 //   Mouse.set_buttons(1, 0, 0); //aalways be clicking so our mouse can move
    if (analogRead(arrowUpPin) < mouseThreshold) {
      Mouse.set_buttons(1, 0, 0);
      Mouse.move(0, -30);
    }
    if (analogRead(arrowDownPin) < mouseThreshold) {
      Mouse.set_buttons(1, 0, 0);
      Mouse.move(0, 30);
    }
    if (analogRead(arrowLeftPin) < mouseThreshold) {
      Mouse.set_buttons(1, 0, 0);
      Mouse.move(-30, 0);
    }
    if (analogRead(arrowRightPin) < mouseThreshold) {
      Mouse.set_buttons(1, 0, 0);
      Mouse.move(30, 0);
    }
    Mouse.set_buttons(0, 0, 0);
  //} //else {Mouse.set_buttons(0, 0, 0);}
  (analogRead(homePinPin) < analogThreshold) ? (Keyboard.press(KEY_SPACE)) : (Keyboard.release(KEY_SPACE));
  (analogRead(galaxyPinPin) < analogThreshold) ? (Keyboard.press(KEY_W)) : (Keyboard.release(KEY_W));
  (analogRead(expandPin) < analogThreshold) ? (Keyboard.press(KEY_A)) : (Keyboard.release(KEY_A));
  (analogRead(contractPin) < analogThreshold) ? (Keyboard.press(KEY_D)) : (Keyboard.release(KEY_D));

/*
  if (analogRead(trPin1) < analogThreshold) {
    Mouse.scroll(2);
  }
  else if (analogRead(trPin2) < analogThreshold) {
    Mouse.scroll(-2);
  }
*/

  delay(100);
}

void printDebug(String label, int val, int minV, int maxV, String action) {

  Serial.print(label);
  Serial.print(", Max: ");
  Serial.print(maxV);
  Serial.print(", Min: ");
  Serial.print(minV);
  Serial.print(", Val: ");
  Serial.print(val);
  Serial.print(" > Thresh: ");
  if ( val < analogThreshold) {
    Serial.print(analogThreshold);
    Serial.print(" : ");
    Serial.println(action);

  } else {
    Serial.println(analogThreshold);
  }
}
