/*
*    =============================================
*      MetaTemp controller for hands
*      Prototype with Arduino Uno
*      By Alex Noyanov, September 8th 2022,Moscow
*    =============================================
*
*/

#include "MetaTempController.hpp"
      
// Peltier Element
void Peltier::Peltier(int plusPin, int minusPin) {
    _plusPin = plusPin;
    _minusPin = minusPin;
    }

    void Peltier::heatUp() {
        digitalWrite(_plusPin, HIGH);
        digitalWrite(_minusPin, LOW);
    }

    void Peltier::coolDown() {
        digitalWrite(_plusPin, LOW);
        digitalWrite(_minusPin, HIGH);
    }

// Peltier Element
void MetaTempController::MetaTempController(int plusPin, int minusPin) {
    _plusPin = plusPin;
    _minusPin = minusPin;
    }

    Sonar::Sonar() {
       setWp(false);
    }
    
     Sonar::Sonar(int trig,int echo, bool isWp) //: mySerial(trig, echo)
    {
         setPin(trig, echo);
         setWp(isWp);
    }

    Sonar::Sonar(int trig,int echo, bool isWp, bool isMM) //: mySerial(trig, echo)
    {
         setPin(trig, echo);
         setWp(isWp);
         setMM(isMM);
    }

    Sonar::Sonar(int trig,int echo) //: mySerial(trig, echo)
    {
         setPin(trig, echo);
         setWp(false);
    }

#ifdef UNIPIN
    Sonar::Sonar(int universalPin, bool isWp){
        _onePin = universalPin;
        pinMode(_onePin,OUTPUT);
        setWp(isWp);
    }

    long Sonar::oneReadDistanceWp(){
        pinMode(_onePin, OUTPUT);
        // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
        digitalWrite(_onePin, HIGH);
        delayMicroseconds(10);
        digitalWrite(_onePin, LOW);
        
        // Change pin mode to read signal:
        pinMode(_onePin,INPUT);
        //delay(1);
        // Reads the echoPin, returns the sound wave travel time in microseconds
         _oneDuration = pulseIn(_onePin, HIGH);
        
        // Calculating the distance
        _distance = _duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
              
    }

#endif

void Sonar::setPin(int trig,int echo)
    {
        _echoPin = echo;
        _trigPin = trig;
        pinSetup();
    }

void Sonar::setWp(bool wpMode){
    _isWp = wpMode;
    //Serial.begin(57600);
    //mySerial.begin(9600);
}

void Sonar::setMM(bool isMM){
    _isMM = isMM;
}

  // Reading distance:
   void Sonar::readDistance()
{    if(_isWp)
         readDistanceWp();
    else
         readDistanceNWp();
    
}
   void Sonar::readDistanceNWp()
{
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
       
       // Checking for waterproof:
       //if()
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
       
  // Reads the echoPin, returns the sound wave travel time in microseconds
  _duration = pulseIn(_echoPin, HIGH);
       
  // Calculating the distance
  _distance = _duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  // ==== USE serialTest(); TO CALIBRATE SENSOR! =====
  //return _distance;
  }

     void Sonar::readDistanceNWpMM()
    {
         digitalWrite(_trigPin, HIGH);
         delayMicroseconds(10);
         digitalWrite(_trigPin, LOW);
              
         // Reads the echoPin, returns the sound wave travel time in microseconds
         _duration = pulseIn(_echoPin, HIGH);
              
         // Calculating the distance
         _distance = _duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    }

    void Sonar::readDistanceWp(){
        // 100;
    }


  long Sonar::getDistance(){
    return _distance;
  }
  
// Waterproof sensor here:
 WPSonar::WPSonar(int trig, int echo) : Sonar(trig, echo)//, _mySerial(echo, trig)
{
    setPin(trig, echo);
}
