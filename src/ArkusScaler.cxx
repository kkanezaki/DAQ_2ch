#include "ArkusScaler.h"

void ArkusScaler::CountHold(){
  vme->Write_32(addr+0x100, 0x1, SV_A32);
}

void ArkusScaler::HoldOff(){
  do{
    vme->Write_32(addr+0x100, 0x0, SV_A32);
  }while(HoldStatus());
}

int ArkusScaler::HoldStatus(){
  int data = vme->Read_32(addr+0x100, SV_A32);
  return data;
}

void ArkusScaler::Start(){
  vme->Write_32(addr+0x104, 0x1, SV_A32);
}

void ArkusScaler::Stop(){
  vme->Write_32(addr+0x104, 0x0, SV_A32);
}

int ArkusScaler::RunStatus(){
  int flag = vme->Read_32(addr+0x104, SV_A32);
  return flag;
}

void ArkusScaler::Reset(){
  vme->Write_32(addr+0x108, 0x1, SV_A32);
}

long long ArkusScaler::Read_Ch(int ch){
  long long data;
  data = vme->Read_32(addr+0x004+ch*0x008, SV_A32);
  data += ((long long)(vme->Read_32(addr+0x000+ch*0x008, SV_A32)) << 32);

  return data;
}

void ArkusScaler::Read(long long *buf){
  int data[2*32];
  vme->Read_N(addr, 64, data, SV_A32);

  for(int ch=0; ch<32; ch++)
    buf[ch] = data[ch*2+1] + ((long long)data[ch*2] << 32);
}


ArkusScaler::ArkusScaler(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

ArkusScaler::ArkusScaler(){
}

ArkusScaler::~ArkusScaler(){
}
