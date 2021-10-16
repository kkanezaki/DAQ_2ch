#ifndef RPV160_h
#define RPV160_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "SiTCP_VME.h"

using namespace std;

class RPV160 {
 public:
  RPV160();
  RPV160(SiTCP_VME*, const int);
  ~RPV160();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  void  Initialize();
  void  Start();
  void  Stop();
  void  Clear();

  int   GetAddr();
  bool  DataExist();
  void  Read(int ch, int num, char *data);

 private:
  SiTCP_VME   *vme;
  int          addr;
};

#endif
