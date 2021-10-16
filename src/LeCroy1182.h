#ifndef LeCroy1182_h
#define LeCroy1182_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "SiTCP_VME.h"

using namespace std;

class LeCroy1182 {
 public:
  LeCroy1182();
  LeCroy1182(SiTCP_VME*, const int);
  ~LeCroy1182();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  void  Start();
  bool  DataWait();
  void  Read(short*);

 private:
  SiTCP_VME   *vme;
  int          addr;  
};

#endif
