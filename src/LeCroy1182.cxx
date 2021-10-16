#include "LeCroy1182.h"

void LeCroy1182::Start(){
  vme->Write_16(addr, 0x0104, SV_A24);
}

bool LeCroy1182::DataWait(){
  bool flag = 0;
  for(int i=0; i<1e4; i++){
    short tmp = vme->Read_16(addr, SV_A24);
    flag = tmp & 0x1;
    if(flag)
      break;
  }

  return flag;
}

void LeCroy1182::Read(short *buf){
  vme->Read_N(addr, 8, buf, SV_A24);
}


LeCroy1182::LeCroy1182(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

LeCroy1182::LeCroy1182(){
}

LeCroy1182::~LeCroy1182(){
}
