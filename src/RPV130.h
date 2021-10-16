#ifndef RPV130_h
#define RPV130_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "SiTCP_VME.h"

using namespace std;

class RPV130 {
 public:
  RPV130();
  RPV130(SiTCP_VME*, const int);
  ~RPV130();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  int   Latch_1();
  int   Latch_2();
  int   Latch_FF();
  int   Read();
  void  Pulse(int);
  void  Level(int);
  void  Clear(bool b1=1, bool b2=1, bool b3=1);
  void  Enable(bool b1=1, bool b2=1, bool b3=1);

 private:
  SiTCP_VME   *vme;
  int          addr;
};

#endif
