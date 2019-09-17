
/*
  .CPP file for MCP401x POTTY
  Author: Ranjan Kumar Rath, rath.ranjankumar@gmail.com
*/

#include"_POT.h"
#define OUTPUT 1
#define HIGH 1
#define LOW 0

// from the datasheet: there should be a minimum delay between signal changes
// here I have taken it as 1 ms for simplicity 
#define MINIMUM_WAIT_TIME_FOR_CS_UD_STATE_CHANGES 1

/* The following define should be uncommented if serial prints are wanted*/
//#define SERIAL_DEBUG_INTERFACE_PRINT

/*
  Constructor: parameters CS, and UD Signal Pins.
*/
MCP_4011_POT :: MCP_4011_POT(int CS, int UD)
{

  // Initialize the private members of the object
  this->CS = CS;
  this->UD = UD;
  this->memorize_last_POT_val = 32; // The POT has a POR value of mid point
  
  //The two signals are set as an OUTPUT  
  pinMode(this->CS, OUTPUT);
  pinMode(this->UD,OUTPUT);
  
  // Set both signals high
  digitalWrite (this->CS, HIGH);
  digitalWrite (this->UD, HIGH);
  
  // Incase you want to see the initialized Object
  #ifdef SERIAL_DEBUG_INTERFACE_PRINT
  Serial.begin(9600);
  Serial.println("POT Object is Created:"); 
  Serial.print ("CS:"); 
  Serial.print (this->CS);
  Serial.print ("UD:");  
  Serial.print (this->UD); 
  Serial.print ("memorize_last_POT_val:");
  Serial.print (this->memorize_last_POT_val);
  Serial.end();
  #endif
  
}
void MCP_4011_POT :: _POT_increment_unity_()
{
  // Initial State: Both signals are high
  
  /* The protocol is explained in the datasheet by signal diagrams */
  
  // 1) CS low : 
  digitalWrite (this->CS, LOW);
  
  // 2) wait for the minimum time as mentioned in the datasheet: here we wait for 1 ms.
  delay (MINIMUM_WAIT_TIME_FOR_CS_UD_STATE_CHANGES);
  
  // 3) UD low
  digitalWrite(this->UD, LOW);
  
  // 4) wait
  delay(MINIMUM_WAIT_TIME_FOR_CS_UD_STATE_CHANGES);
  
  // 5) UD high
  digitalWrite(this->UD, HIGH);
  
  // 6) wait
  delay(MINIMUM_WAIT_TIME_FOR_CS_UD_STATE_CHANGES);
  
  // 7) CS high
  digitalWrite(this->CS, HIGH);
  
  // Reverted back to Initial State: Both signals are high
  
  #ifdef SERIAL_DEBUG_INTERFACE_PRINT
  Serial.println("POT Increment method got Called:");
  #endif
}
void MCP_4011_POT :: _POT_decrement_unity_()
{
  // Initial State: Both signals are high
  
  // 1) UD LOW
  digitalWrite (this->UD, LOW);
  
  // 2) wait
  delay(MINIMUM_WAIT_TIME_FOR_CS_UD_STATE_CHANGES);
  
  // 3) CS low
  digitalWrite (this->CS, LOW);
  
  // 4) wait
  delay(MINIMUM_WAIT_TIME_FOR_CS_UD_STATE_CHANGES);
  
  // 5) UD high
  digitalWrite (this->UD, HIGH);
  
  // 6) wait
  delay(MINIMUM_WAIT_TIME_FOR_CS_UD_STATE_CHANGES);
  
  // 7) CS high
  digitalWrite (this->CS, HIGH);

  // Reverted back to Initial State: Both signals are high
  
  #ifdef SERIAL_DEBUG_INTERFACE_PRINT
  Serial.println("POT Decrement method got Called:");
  #endif
  
}

void MCP_4011_POT :: _POT_wiper_Set(int previous_val, int required_val)
{
  
  
  // Calculate the amount of wiper shift
  
  char POT_steps = 0;
  POT_steps =  required_val - previous_val; //abs = always positive
  
  // Move the wiper the required number of times
  if (POT_steps < 0)
  {
    
    for (char i=POT_steps; i<0; i++)
    {
     _POT_decrement_unity_(); 
    }
    return;
    
  }
  else if (POT_steps > 0)
  {
    for (char j=0; j<POT_steps; j++)
    {
      _POT_increment_unity_(); 
    }
    return;
  }

  else
  {
    // Do Nothing
    return;
  }
    
}

void MCP_4011_POT :: _POT_Set(int required_val)
{
  #ifdef SERIAL_DEBUG_INTERFACE_PRINT
  Serial.println("POT SET method got Called with Set Value:"); Serial.println(required_val);
  #endif
  
  // make the change
  _POT_wiper_Set(this->memorize_last_POT_val, required_val);
  
  //Update the memory
  this->memorize_last_POT_val = required_val;
  
  #ifdef SERIAL_DEBUG_INTERFACE_PRINT
  Serial.println("POT SET method execution Over with memorize_last_POT_val:"); Serial.println(memorize_last_POT_val);
  #endif
  
}
