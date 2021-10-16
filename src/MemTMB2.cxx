#include "MemTMB2.h"

int MemTMB2::GetVersion(){
  return vme->Read_32(addr+0x1018, SV_A32);
}

int MemTMB2::Status1(){
  return vme->Read_32(addr+0x1020, SV_A32);
}

int MemTMB2::Status2(){
  return vme->Read_32(addr+0x1028, SV_A32);
}

void MemTMB2::SetDepth1(int depth){
  vme->Write_32(addr+0x1030, depth, SV_A32);
}

int MemTMB2::GetDepth1(){
  return vme->Read_32(addr+0x1030, SV_A32);
}

void MemTMB2::SetDepth2(int depth){
  vme->Write_32(addr+0x1038, depth, SV_A32);
}

int MemTMB2::GetDepth2(){
  return vme->Read_32(addr+0x1038, SV_A32);
}

int MemTMB2::GetCount1(){
  return vme->Read_32(addr+0x1040, SV_A32);
}

int MemTMB2::GetCount2(){
  return vme->Read_32(addr+0x1048, SV_A32);
}

int MemTMB2::ReadCount1(){
  return vme->Read_32(addr+0x1050, SV_A32);
}

int MemTMB2::ReadCount2(){
  return vme->Read_32(addr+0x1058, SV_A32);
}

void MemTMB2::Start(){
  vme->Write_32(addr+0x1010, 0x1, SV_A32);
}

void MemTMB2::Stop(){
  vme->Write_32(addr+0x1010, 0x2, SV_A32);
}

void MemTMB2::Reset(){
  vme->Write_32(addr+0x1010, 0x4, SV_A32);
}

void MemTMB2::Clear(int flag){
  vme->Write_32(addr+0x1010, 0x8 | ((flag & 0x3) << 5), SV_A32);
}

void MemTMB2::ClearAll(int flag){
  vme->Write_32(addr+0x1010, 0x10 | ((flag & 0x3) << 5), SV_A32);
}

int MemTMB2::GetActiveSide(){
  int flag = vme->Read_32(addr+0x1018, SV_A32);
  return ((flag >> 24) & 0x1);
}

bool MemTMB2::Read1(int num, int *buf){
  bool flag = 0;
  for(int i=0; i<1e4; i++){
    flag = (Status1() & 0x02) >> 1;
    if(flag)
      break;
  }

  if(flag)
    vme->Read_N(addr, num, buf, SV_A32, SV_F_USR);

  return flag;
}

bool MemTMB2::Read2(int num, int *buf){
  bool flag = 0;
  for(int i=0; i<1e4; i++){
    flag = (Status2() & 0x02) >> 1;
    if(flag)
      break;
  }

  if(flag)
    vme->Read_N(addr+0x800, num, buf, SV_A32, SV_F_USR);

  return flag;
}


MemTMB2::MemTMB2(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

MemTMB2::MemTMB2(){
}

MemTMB2::~MemTMB2(){
}
