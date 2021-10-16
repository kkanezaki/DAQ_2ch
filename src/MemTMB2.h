#ifndef MemTMB2_h
#define MemTMB2_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "SiTCP_VME.h"

using namespace std;

class MemTMB2 {
 public:
  MemTMB2();
  MemTMB2(SiTCP_VME*, const int);
  ~MemTMB2();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  int   GetVersion();
  int   Status1();
  int   Status2();
  void  SetDepth1(int);
  int   GetDepth1();
  void  SetDepth2(int);
  int   GetDepth2();
  int   GetCount1();
  int   GetCount2();
  int   ReadCount1();
  int   ReadCount2();

  void  Start();
  void  Stop();
  void  Reset();
  void  Clear(int);
  void  ClearAll(int);

  int   GetActiveSide();
  bool  Read1(int, int*);
  bool  Read2(int, int*);


 private:
  SiTCP_VME   *vme;
  int          addr;
};

#endif
