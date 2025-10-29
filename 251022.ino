
const int buttonPin = 2;

const int Rpin = 9;
const int Bpin = 10;
const int Gpin = 11;

int buttonState = 0;

bool buttonPressed = false;

unsigned long pressingTime = 0;

const int longPressInterval = 2000;

int lightNum = 0;

int Rcolor =0;
int Bcolor =0;
int Gcolor =0;

int RcurrentColor = 0;
int BcurrentColor = 0;
int GcurrentColor = 0;


int currentMode = 0;

unsigned long blinkTimer = 0;

const int blinkInterval = 500;

bool blinkON = true;

const int fadeAmount = 2;

int fadeDirection = 1;


void setup() {
  // put your setup code here, to run once:

  pinMode(buttonPin,INPUT);
  pinMode(Rpin,OUTPUT);
  pinMode(Bpin,OUTPUT);
  pinMode(Gpin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  checkButton ();
  updateLEDcolor();
  setRGBLEDColor(RcurrentColor, BcurrentColor, GcurrentColor);

}


void checkButton(){

  buttonState = digitalRead(buttonPin);

  if(buttonState == LOW && !buttonPressed){
    pressingTime = millis();
    buttonPressed = true;
  }
  if(buttonState == HIGH && buttonPressed){
    unsigned long currentTime = millis();
    if(currentTime - pressingTime < longPressInterval){
      // Serial.println("short click");
      changeLEDcolor();
    }
    else{
      // Serial.println("long press");
      changeMode();
    }
    buttonPressed = false;
  }

}

void changeLEDcolor(){
    lightNum = lightNum + 1;
    if(lightNum >= 5)
      lightNum = 0;

    if(lightNum == 0){
      Rcolor = 0;
      Bcolor = 0;
      Gcolor = 0;
    }

    if(lightNum == 0){
      Rcolor = 0;
      Bcolor = 0;
      Gcolor = 0;
    }

    if(lightNum == 1){
      Rcolor = 0;
      Bcolor = 255;
      Gcolor = 255;
    }

    if(lightNum == 2){
      Rcolor = 255;
      Bcolor = 0;
      Gcolor = 255;
    }

    if(lightNum == 3){
      Rcolor = 255;
      Bcolor = 255;
      Gcolor = 0;
    }

    if(lightNum == 4){
      Rcolor = 0;
      Bcolor = 0;
      Gcolor = 255;
    }

    
    RcurrentColor = Rcolor;
    BcurrentColor = Bcolor;
    GcurrentColor = Gcolor;

  }

  void changeMode(){

    currentMode = currentMode + 1;
    if(currentMode >= 3){
      currentMode = 0;
    }

    if(currentMode == 1){
      blinkTimer = millis();
      blinkON = true;
    }

  }

  void updateLEDcolor(){
    if(currentMode == 0){
       RcurrentColor = Rcolor;
       BcurrentColor = Bcolor;
       GcurrentColor = Gcolor;
    }
    
    else if(currentMode == 1){
      unsigned long currentTime = millis();
      if(currentTime - blinkTimer >= blinkInterval){
      // Serial.println("short click");
        blinkON = !blinkON;
        blinkTimer = currentTime;
      }

      if(blinkON){
        RcurrentColor = Rcolor;
        BcurrentColor = Bcolor;
        GcurrentColor = Gcolor;
      }
      else{
        RcurrentColor = 255;
        BcurrentColor = 255;
        GcurrentColor = 255;
      }

    }

    else if (currentMode == 2){

      bool negativeDir = false;

      if(Rcolor == 0){
        RcurrentColor = RcurrentColor + fadeDirection * fadeAmount;
        if(RcurrentColor > (255 - Rcolor) || (RcurrentColor < 0)){
          negativeDir = true;
        }

        if(RcurrentColor < 0) RcurrentColor  =0;
        if(RcurrentColor > 255) RcurrentColor = 255;
      }

      if(Bcolor == 0){
        BcurrentColor = BcurrentColor + fadeDirection * fadeAmount;
        if(BcurrentColor > (255 - Bcolor) || (BcurrentColor < 0)){
          negativeDir = true;
        }

        if(BcurrentColor < 0) BcurrentColor = 0;
        if(BcurrentColor > 255) BcurrentColor = 255;
      }

      if(Gcolor == 0){
        GcurrentColor = GcurrentColor + fadeDirection * fadeAmount;
        if(GcurrentColor > (255 - Gcolor) || (GcurrentColor < 0)){
          negativeDir = true;
        }

        if(GcurrentColor < 0) GcurrentColor = 0;
        if(GcurrentColor > 255) GcurrentColor = 255;
      }

      if(negativeDir)
        fadeDirection = -fadeDirection;

      delay(10);
      
    }
  }

  void setRGBLEDColor(int r, int b, int g){
    analogWrite(Rpin, r);
    analogWrite(Bpin, b);
    analogWrite(Gpin, g);
  }



