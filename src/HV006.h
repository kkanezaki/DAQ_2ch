#ifndef HV006_h
#define HV006_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "SiTCP_VME.h"

using namespace std;

class HV006 {
 public:
  HV006();
  HV006(SiTCP_VME*, const int);
  ~HV006();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  void  Reset();
  bool  Wait();
  short Read(int);
  void  Read(short*);

 private:
  SiTCP_VME   *vme;
  int          addr;
};

#endif
