#include "GNV230.h"

int GNV230::Read_CSR(){
  int data = vme->Read_32(addr+0x400, SV_A24, SV_SUP);
  return data;
}

void GNV230::Start(){
  int tmp = Read_CSR();
  tmp = ((tmp & ~0x2000) | 0x2000);
  vme->Write_32(addr+0x400, tmp, SV_A24, SV_SUP);
}

void GNV230::Stop(){
  int tmp = Read_CSR();
  tmp = ((tmp & ~0x4000) | 0x4000);
  vme->Write_32(addr+0x400, tmp, SV_A24, SV_SUP);
}

void GNV230::Reset(){
  int tmp = Read_CSR();
  tmp = ((tmp & ~0x1000) | 0x1000);
  vme->Write_32(addr+0x400, tmp, SV_A24, SV_SUP);
}

void GNV230::SetMemSize(bool LD, bool FSEL0, bool FSEL1){
  int data = (LD << 8) + (FSEL0 << 9) + (FSEL1 << 10);
  vme->Write_32(addr+0x400, data, SV_A24, SV_SUP);

  data = (data >> 8) & 0x7;
  switch(data){
  case 0:  offset = 127;  break;
  case 1:  offset =  31;  break;
  case 2:  offset = 255;  break;
  case 3:  offset =   7;  break;
  case 4:  offset = 511;  break;
  case 5:  offset =  15;  break;
  case 6:  offset =  63;  break;
  default:  offset =   3;  break;
  }
}

bool GNV230::WaitData(){
  bool flag=0;
  for(int i=0; i<1e4; i++){
    int tmp = Read_CSR();
    flag = (tmp >> 5) & 0x1;
    if(!flag)
      break;
  }

  return ~flag;
}

void GNV230::Read_Data(int num, char *buf){
  for(int j=0; j<4; j++){
    int data[1024];
    vme->Read_N(addr+j*0x100, 1024-offset, data, SV_A24, SV_F_USR);

    for(int i=0; i<num/2; i++){
      *(buf + (2*j)*num + 2*i) 
	= data[1024-offset-(num/2)+i] & 0xff;
      *(buf + (2*j)*num + 2*i+1) 
	= (data[1024-offset-(num/2)+i] >> 8) & 0xff;
      *(buf + (2*j+1)*num + 2*i) 
	= (data[1024-offset-(num/2)+i] >> 16)& 0xff;
      *(buf + (2*j+1)*num + 2*i+1) 
	= (data[1024-offset-(num/2)+i] >> 24) & 0xff;
    }
  }
}


GNV230::GNV230(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

GNV230::GNV230(){
}

GNV230::~GNV230(){
}
