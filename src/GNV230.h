#ifndef GNV230_h
#define GNV230_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "SiTCP_VME.h"

using namespace std;

class GNV230 {
 public:
  GNV230();
  GNV230(SiTCP_VME*, const int);
  ~GNV230();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  int   Read_CSR();
  void  Start();
  void  Stop();
  void  Reset();
  bool  WaitData();
  void  Read_Data(int, char*);
  void  SetMemSize(bool LD, bool FSEL0, bool FSEL1);

 private:
  SiTCP_VME   *vme;
  int          addr, offset;
};

#endif
