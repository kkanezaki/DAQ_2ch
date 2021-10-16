#ifndef CL_DP80057_h
#define CL_DP80057_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>

#include "SiTCP_VME.h"

using namespace std;

class CL_DP80057 {
 public:
  CL_DP80057();
  CL_DP80057(SiTCP_VME*, const int);
  ~CL_DP80057();

  void  SetMaster(SiTCP_VME *master)   {vme = master;};
  void  SetBaseAddr(const int base)    {addr = base;};

  void  VenderID();
  void  ModuleID();
  void  SetCommand(int);
  int   GetStatus();
  void  T_Width(int);
  void  V_Width(int);
  void  PortMask(bool, bool, bool, bool);
  void  B_Width(int);
  void  SetPipeLine(int);

  void  SetHeaderSize(int, int, int, int);
  void  SetSDSBlockSize(int, int, int, int);
  void  SetHeaderID(int, int, int, int);
  void  PMT_A_Command(int);
  void  PMT_B_Command(int);
  void  PMT_C_Command(int);
  void  PMT_D_Command(int);

  void  SetPedestal_A(int, int*);
  void  SetPedestal_B(int, int*);
  void  SetPedestal_C(int, int*);
  void  SetPedestal_D(int, int*);
  void  SetPedestal_A(int, int);
  void  SetPedestal_B(int, int);
  void  SetPedestal_C(int, int);
  void  SetPedestal_D(int, int);
  void  SetGain_A(int, int*);
  void  SetGain_B(int, int*);
  void  SetGain_C(int, int*);
  void  SetGain_D(int, int*);
  void  SetGain_A(int, int);
  void  SetGain_B(int, int);
  void  SetGain_C(int, int);
  void  SetGain_D(int, int);

  bool  GetData_A(int, int*);
  bool  GetData_B(int, int*);
  bool  GetData_C(int, int*);
  bool  GetData_D(int, int*);
  
  void  FIFO_Reset();
  void  ForceTrigger();
  void  BUSY(bool);
  void  LED(bool);
  void  Power(bool);
  void  ExtTrgIn(bool);
  void  ExtTrgOut();
  void  BusyOut();

 private:
  SiTCP_VME   *vme;
  int          addr, mode;
};

#endif
