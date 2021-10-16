#ifndef ArkusADC_h
#define ArkusADC_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "SiTCP_VME.h"

using namespace std;

class ArkusADC {
 public:
  ArkusADC();
  ArkusADC(SiTCP_VME*, const int);
  ~ArkusADC();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  void  Read_ZG(short *zero, short *gain);
  void  ReadCh(short*);
  void  ReadSubCh(short*);

  void  Initialize(int MainEna, int NumSubCh);
  void  Start();
  int   GetStatus();

 private:
  SiTCP_VME   *vme;
  int          addr;
};

#endif
