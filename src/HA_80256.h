#ifndef HA_80256_h
#define HA_80256_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include "CL_DP80057.h"

#define  Port_A  0x01
#define  Port_B  0x02
#define  Port_C  0x04
#define  Port_D  0x08

#define  PMT_EXTTRIGOUT  0x10000
#define  PMT_EXTTRIGIN   0x08000
#define  PMT_ANTRIG      0x04000

using namespace std;

class HA_80256 : public CL_DP80057 {
 public:
  HA_80256();
  HA_80256(SiTCP_VME*, const int);
  ~HA_80256();

  void  HA_Init();
  void  DP_Setup();
  void  HA_Reset();
  void  Enable(char);
  void  ResetTime();
  void  PowerOn(int, int, int, int);
  void  TrigMode(int);
  void  tHoldTime();
  void  TrigGen(int, int, int, int);
  void  SetThreshold(int, int, int, int, int);
  void  HA_ForceTrg();
  char  DataExist();
  void  BusyExtation();
  bool  GetData(int*, int*, int*, int*);

  bool  Enable_A()                          {return fa;};
  bool  Enable_B()                          {return fb;};
  bool  Enable_C()                          {return fc;};
  bool  Enable_D()                          {return fd;};
  
 private:
  bool  fa, fb, fc, fd;
};

#endif
