#include "ArkusADC.h"

void ArkusADC::ReadCh(short *buf){
  int data[32];
  vme->Read_N(addr, 32, data, SV_A32);
  for(int i=0; i<32; i++)
    buf[i] = data[i] & 0xffff;
}

void ArkusADC::ReadSubCh(short *buf){
  int data[128];
  vme->Read_N(addr, 128, data, SV_A32);
  for(int i=0; i<128; i++)
    buf[i] = data[i] & 0xffff;
}

void ArkusADC::Read_ZG(short *zero, short *gain){
  int data[64];
  vme->Read_N(addr+0x100, 64, data, SV_A32);
  for(int i=0; i<32; i++){
    zero[i] = data[2*i] & 0xffff;
    gain[i] = data[2*i+1] & 0xffff;
  }
}

void ArkusADC::Initialize(int MainEna, int NumSubCh){
  int flag=0x2;
  if(NumSubCh)
    flag = 0x0;

  vme->Write_32(addr+0x088, MainEna, SV_A32);
  vme->Write_32(addr+0x08c, NumSubCh, SV_A32);
  vme->Write_32(addr+0x080, flag, SV_A32);
}

void ArkusADC::Start(){
  vme->Write_32(addr+0x084, 0xffffffff, SV_A32);
}

int ArkusADC::GetStatus(){
  int data = vme->Read_32(addr+0x90, SV_A32);
  return data;
}


ArkusADC::ArkusADC(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

ArkusADC::ArkusADC(){
}

ArkusADC::~ArkusADC(){
}
