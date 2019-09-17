/*
  Header file for MCP401x type POTTY
  Author: Ranjan Kumar Rath, rath.ranjankumar@gmail.com
*/


#ifndef _POT
#define _POT

class MCP_4011_POT
{
  int memorize_last_POT_val, CS, UD;
  public:
  MCP_4011_POT(int CS, int UD);
  void _POT_increment_unity_(void);
  void _POT_decrement_unity_(void);
  void _POT_wiper_Set(int, int);
  void _POT_Set(int);
};

#endif
