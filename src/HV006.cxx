#include "HV006.h"

void HV006::Reset(){
  vme->Write_16(addr, 0xffff, SV_A24);
}

bool HV006::Wait(){
  bool flag=0;
  for(int i=0; i<1e3; i++){
    flag = (vme->Read_16(addr, SV_A24)) >> 15;

    if(flag)
      break;
  }
  
  return flag;
}

short HV006::Read(int ch){
  short data = vme->Read_16(addr + 0x2*ch, SV_A24);
  return data & 0x3fff;
}

void HV006::Read(short *data){
  vme->Read_N(addr, 16, data, SV_A24);
  for(int i=0; i<16; i++)
    data[i] = data[i] & 0x3fff;
}


HV006::HV006(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

HV006::HV006(){
}

HV006::~HV006(){
}
