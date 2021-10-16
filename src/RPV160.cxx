#include "RPV160.h"

void RPV160::Start(){
  vme->Write_16(addr+0x30008, 0x0001, SV_A32);
}

void RPV160::Stop(){
  vme->Write_16(addr+0x30008, 0x0002, SV_A32);
}

void RPV160::Clear(){
  vme->Write_16(addr+0x30008, 0x0004, SV_A32);
}

int RPV160::GetAddr(){
  int num  = vme->Read_16(addr+0x30000, SV_A32);

  return num;
}

bool RPV160::DataExist(){
  int flag=0;
  for(int i=0; i<1e4; i++){
    flag = vme->Read_16(addr+0x30004, SV_A32);
    if(flag & 0x20)
      break;
  }

  return ((flag >> 5) & 0x1);
}

void RPV160::Read(int ch, int num, char *data){
  short raw[0x1000];
  vme->Read_N(addr+ch*0x2000, 0x1000, raw, SV_A32);

  int e_addr = GetAddr() + 0x1000;
  for(int i=0; i<num/2; i++){
    int tmp = (e_addr + i - num/2) % 0x1000;
    
    *(data + 2*i) = (raw[tmp] >> 8) & 0xff;
    *(data + 2*i+1) = raw[tmp] & 0xff;
  }
}

void RPV160::Initialize(){
  vme->Write_16(addr+0x20000, 0x0003, SV_A32);
  vme->Write_16(addr+0x20002, 0x0012, SV_A32);
  vme->Write_16(addr+0x20004, 0x5678, SV_A32);
  vme->Write_16(addr+0x20006, 0x0003, SV_A32);

  for(int i=0; i<8; i++)
    vme->Write_16(addr+0x21002+i*0x200, 0x0080, SV_A32);
}


RPV160::RPV160(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

RPV160::RPV160(){
}

RPV160::~RPV160(){
}

