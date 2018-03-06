/*

 LED Control  
 ------------------
 This sketch demonstrates the use of Arduino board.

 
 Circuit:
 --------
 Just plug in your Arduino board in USB port or power it up with external 5V power supply.

   
 User Guide:
 -----------  
   Tah protocol we use to communicate between the App and a Tah is basically a comma seprated string with end character "R".
   This protocol string is composed of 3 integer values with the end suffix "R" which represents end of string. 
 
   1st Integer represents--> Pin Type: 0 = DIGITAL,  1 = ANALOG,  2 = SERVO,  3 = Send Analog Status,  4 = Send Digital Status
   2nd Integer represents--> Pin No: From 2 to 13 for digital pins and 410 to 415 represents A0 to A5 analog pins
   3rd Integer represents--> Pin Value: 
                             0 or 1 for Digital
                             0 to 255 for Analog
                             0 to 179 for Servo

   e.g:  So if we want to turn ON the default led attached to pin 13 then the protocol sting would be => 0,13,1R                                                                                                 
*/


    #include<TAH.h>
    
    TAH mediator; 
    int pinType,pinNo,pinValue;
    int ledPin = 13;
    int ledValue;
    int lastLedValue;
    
    void setup() 
    {
        // Initialize serial:
        Serial.begin(9600);
        mediator.begin(9600);
      
        mediator.enterCommandMode();
      
        mediator.setName("LED DEMO");
        mediator.setWorkRole(SLAVE);
        mediator.setAuth(OPEN);
        mediator.setWorkMode(REMOTE_CONTROL);
        mediator.setiBeaconMode(ON);
      
        mediator.exitCommandMode();
        
        pinMode(ledPin, OUTPUT);
      
    }
    
    
    void loop() 
    {
      
        if (mediator.available()) 
        {
            ///// Parsing Value From Left Controller
            pinType = mediator.parseInt();
            pinNo = mediator.parseInt();
            pinValue = mediator.parseInt();
          
            if(mediator.read() == 'R')
            {
                if(pinValue == 1)
                {
                  digitalWrite(ledPin, HIGH);
                  delay(500);
                }
                else if(pinValue == 0)
                {
                  digitalWrite(ledPin, LOW);
                  delay(500);
                }
            }
        }
        
        ledValue = digitalRead(ledPin);
      
        if(ledValue != lastLedValue)
        {
            mediator.println(ledValue);
        }
        
        lastLedValue = ledValue;
    }
    
    

