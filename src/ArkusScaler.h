#ifndef ArkusScaler_h
#define ArkusScaler_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "SiTCP_VME.h"

using namespace std;

class ArkusScaler {
 public:
  ArkusScaler();
  ArkusScaler(SiTCP_VME*, const int);
  ~ArkusScaler();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  void  CountHold();
  void  HoldOff();
  int   HoldStatus();
  void  Start();
  void  Stop();
  int   RunStatus();
  void  Reset();

  long long  Read_Ch(int);
  void       Read(long long*);

 private:
  SiTCP_VME   *vme;
  int          addr;
};

#endif
