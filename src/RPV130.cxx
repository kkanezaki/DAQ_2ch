#include "RPV130.h"

int RPV130::Latch_1(){
  int data = vme->Read_16(addr + 0x00, SV_A16);
  return data & 0xff;
}

int RPV130::Latch_2(){
  int data = vme->Read_16(addr + 0x02, SV_A16);
  return data & 0xff;
}

int RPV130::Latch_FF(){
  int data = vme->Read_16(addr + 0x04, SV_A16);
  return data & 0xff;
}

int RPV130::Read(){
  int data = vme->Read_16(addr + 0x06, SV_A16);
  return data & 0xff;
}

void RPV130::Pulse(int data){
  vme->Write_16(addr + 0x08, data & 0xff, SV_A16);
}

void RPV130::Level(int data){
  vme->Write_16(addr + 0x0a, data & 0xff, SV_A16);
}

void RPV130::Clear(bool b1, bool b2, bool b3){
  int d1 = (b1 << 1) | b3;
  int d2 = (b2 << 1) | b3;

  vme->Write_16(addr + 0xc, d1, SV_A16);
  vme->Write_16(addr + 0xe, d2, SV_A16);
}

void RPV130::Enable(bool b1, bool b2, bool b3){
  int d1=0, d2=0;
  if(b1)
    d1 += 0x1a;
  if(b2)
    d2 += 0x1a;
  if(b3){
    d1 += 0x41;
    d2 += 0x41;
  }

  vme->Write_16(addr + 0xc, d1, SV_A16);
  vme->Write_16(addr + 0xe, d2, SV_A16);
}


RPV130::RPV130(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

RPV130::RPV130(){
}

RPV130::~RPV130(){
}

