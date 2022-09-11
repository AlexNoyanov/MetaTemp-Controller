//
//  MetaTempController.hpp
//  
//
//  Created by Alex Noyanov on 11/03/2021.
//
//
//

//#if defined(ARDUINO) && ARDUINO >= 100
//#include "Arduino.h"
//#else
//#include "WProgram.h"
//#endif

#ifndef MetaTempController.hpp
#define MetaTempController.hpp

#include <stdio.h>
#include <Arduino.h>

#endif
/* MetaTempController_hpp */

class Peltier {
   /*
    
    Peltier element
    5V Input, Current up to 2.5Amp
    20mm x 20mm x 3mm Sizes
    Two pins connection
    
    */
    
private:
    int _plusPin;
    int _minusPin;
    int _power;
public:
    Peltier(int left, int right);
    heatUp();
    cooldDown();
    off();
}

class MetaTempController {
    
    /*
     
     MetaTemp L298N-based controller
     4 pins for connection
     
     */
    
    private:
      Peltier _peltierLeftHand[], _peltierRightHand[]; // Peltier elements for hands
      int _pins[];
      bool _leftHandModes[];                   // Left hand mode (cool/heat)
      bool _rightHandModes[];                   // Right hand mode
    
    public:
        MetaTempController();
        MetaTempController(int leftPins[], int rightPins[]);
        MetaTempController(int trig, int echo, bool isWp);
    
        void setPin(int trig,int echo);
private:
        long getDistanceNWp();              // For distance waterproof
        long getDistanceWp();               // For distance not waterproof
        void readDistanceWp();
        void readDistanceNWp();
public:
};
