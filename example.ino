/*
  Example Code: Connect 2 MCP401x devices and the POTTY resistace changes between A-W or B-W from Min to Max in unity steps.
  In order to set to the resistance value, please calculate it and accordingly set it with the number of steps.
  For example: On MCP4011: A-B Resistance is 5k Ohm, So one step increment of the wiper from POR value of 2.5k Ohm,
                         would be 2.k Ohm + (5k Ohm / 64). Please read the data sheet about the zero offset on each devices.
  Author: Ranjan Kumar Rath rath.ranjankumar@gmail.com
*/

#include "_POT.h"

#define CS_POT_1 5
#define UD_POT_1 4

#define CS_POT_2 6
#define UD_POT_2 7


MCP_4011_POT POT_1(CS_POT_1, UD_POT_1);
MCP_4011_POT POT_2(CS_POT_2, UD_POT_2);

void _POT_self_test(MCP_4011_POT * obj, int _POT_NUMBER);



void setup() {

Serial.begin(9600);
Serial.println("**************************************************************************");

 _POT_self_test(&POT_1, 1);

 _POT_self_test(&POT_2, 2);


}

void loop() {


}


void _POT_self_test(MCP_4011_POT * obj, int _POT_NUMBER)
{

    Serial.print("POT_ Self TEST: MIN TO MAX with unit steps: WITH 3S DELAY to meassure the POTTY value with Multimeter \n POT NUMBER: "); Serial.print(_POT_NUMBER);
    Serial.println("");
	
	for (int i = 0; i<64; i++)
	{
		Serial.println("\n_POT_Set("); Serial.print(i); Serial.print(")");
		obj->_POT_Set(i);
		delay(3000);
	}
    
  
}
