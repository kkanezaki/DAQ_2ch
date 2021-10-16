#include "CL_DP80057.h"

void CL_DP80057::VenderID(){
  int data = vme->Read_32(addr, SV_A24);
  
  char vender[5]
    = {(char)((data >> 24) & 0xff), (char)((data >> 16) & 0xff),
       (char)((data >>  8) & 0xff), (char)((data) & 0xff), '\0'};
  cout << hex << " Vendor ID  : " << vender << endl;
}

void CL_DP80057::ModuleID(){
  int data = vme->Read_32(addr+0x4, SV_A24);

  cout << dec;
  cout << " Module ID  : " << ((data >> 8) & 0xffffff) << endl;
  cout << " Version    : " << (data & 0xff) << endl;
}

void CL_DP80057::SetCommand(int com){
  vme->Write_32(addr+0x8, com, SV_A24);
}

int CL_DP80057::GetStatus(){
  return ((vme->Read_32(addr+0x20, SV_A24)) & 0x3ff);
}

void CL_DP80057::T_Width(int par){
  vme->Write_32(addr+0x10, par & 0xffff, SV_A24);
}

void CL_DP80057::V_Width(int par){
  vme->Write_32(addr+0x14, par & 0xffff, SV_A24);
}

void CL_DP80057::PortMask(bool pa, bool pb, bool pc, bool pd){
  int data = (pa << 4) + (pb << 5) + (pc << 6) + (pd << 7);
  vme->Write_32(addr+0x18, data, SV_A24);
}

void CL_DP80057::B_Width(int par){
  vme->Write_32(addr+0x1c, par & 0xffff, SV_A24);
}

void CL_DP80057::SetPipeLine(int par){
  vme->Write_32(addr+0x30, par & 0xffff, SV_A24);
}

void CL_DP80057::SetHeaderSize(int sa, int sb, int sc, int sd){
  vme->Write_32(addr+0x100, sa&0xffff, SV_A24);
  vme->Write_32(addr+0x104, sb&0xffff, SV_A24);
  vme->Write_32(addr+0x108, sc&0xffff, SV_A24);
  vme->Write_32(addr+0x10c, sd&0xffff, SV_A24);
}

void CL_DP80057::SetSDSBlockSize(int ba, int bb, int bc, int bd){
  vme->Write_32(addr+0x110, ba&0xffff, SV_A24);
  vme->Write_32(addr+0x114, bb&0xffff, SV_A24);
  vme->Write_32(addr+0x118, bc&0xffff, SV_A24);
  vme->Write_32(addr+0x11c, bd&0xffff, SV_A24);
}

void CL_DP80057::SetHeaderID(int ia, int ib, int ic, int id){
  vme->Write_32(addr+0x120, ia&0xffff, SV_A24);
  vme->Write_32(addr+0x124, ib&0xffff, SV_A24);
  vme->Write_32(addr+0x128, ic&0xffff, SV_A24);
  vme->Write_32(addr+0x12c, id&0xffff, SV_A24);
}

void CL_DP80057::PMT_A_Command(int com){
  while(GetStatus() & 0x200)
    usleep(1);
  vme->Write_32(addr+0x44, com, SV_A24);
}

void CL_DP80057::PMT_B_Command(int com){
  while(GetStatus() & 0x200)
    usleep(1);
  vme->Write_32(addr+0x48, com, SV_A24);
}

void CL_DP80057::PMT_C_Command(int com){
  while(GetStatus() & 0x200)
    usleep(1);
  vme->Write_32(addr+0x50, com, SV_A24);
}

void CL_DP80057::PMT_D_Command(int com){
  while(GetStatus() & 0x200)
    usleep(1);
  vme->Write_32(addr+0x58, com, SV_A24);
}

void CL_DP80057::SetPedestal_A(int ch, int *data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x14000+i*4, data[i], SV_A24);
}

void CL_DP80057::SetPedestal_A(int ch, int data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x14000+i*4, data, SV_A24);
}

void CL_DP80057::SetPedestal_B(int ch, int *data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x14800+i*4, data[i], SV_A24);
}

void CL_DP80057::SetPedestal_B(int ch, int data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x14800+i*4, data, SV_A24);
}

void CL_DP80057::SetPedestal_C(int ch, int *data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x15000+i*4, data[i], SV_A24);
}

void CL_DP80057::SetPedestal_C(int ch, int data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x15000+i*4, data, SV_A24);
}

void CL_DP80057::SetPedestal_D(int ch, int *data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x15800+i*4, data[i], SV_A24);
}

void CL_DP80057::SetPedestal_D(int ch, int data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x15800+i*4, data, SV_A24);
}

void CL_DP80057::SetGain_A(int ch, int *data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x16000+i*4, data[i], SV_A24);
}

void CL_DP80057::SetGain_A(int ch, int data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x16000+i*4, data, SV_A24);
}

void CL_DP80057::SetGain_B(int ch, int *data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x16800+i*4, data[i], SV_A24);
}

void CL_DP80057::SetGain_B(int ch, int data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x16800+i*4, data, SV_A24);
}

void CL_DP80057::SetGain_C(int ch, int *data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x17000+i*4, data[i], SV_A24);
}

void CL_DP80057::SetGain_C(int ch, int data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x17000+i*4, data, SV_A24);
}

void CL_DP80057::SetGain_D(int ch, int *data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x17800+i*4, data[i], SV_A24);
}

void CL_DP80057::SetGain_D(int ch, int data){
  for(int i=0; i<ch; i++)
    vme->Write_32(addr+0x17800+i*4, data, SV_A24);
}

bool CL_DP80057::GetData_A(int num, int *buf){
  bool flag=0;
  
  vme->Read_N(addr+0x11000, num, buf, SV_A24, SV_F_USR);
  for(int i=0; i<num; i++){
    if(buf[i]==-1)
      flag=0;
    else
      flag=1;
  }

  return flag;
}

bool CL_DP80057::GetData_B(int num, int *buf){
  bool flag=0;
  
  vme->Read_N(addr+0x11400, num, buf, SV_A24, SV_F_USR);
  for(int i=0; i<num; i++){
    if(buf[i]==-1)
      flag=0;
    else
      flag=1;
  }

  return flag;
}

bool CL_DP80057::GetData_C(int num, int *buf){
  bool flag=0;
  
  vme->Read_N(addr+0x11800, num, buf, SV_A24, SV_F_USR);
  for(int i=0; i<num; i++){
    if(buf[i]==-1)
      flag=0;
    else
      flag=1;
  }

  return flag;
}

bool CL_DP80057::GetData_D(int num, int *buf){
  bool flag=0;
  
  vme->Read_N(addr+0x11c00, num, buf, SV_A24, SV_F_USR);
  for(int i=0; i<num; i++){
    if(buf[i]==-1)
      flag=0;
    else
      flag=1;
  }

  return flag;
}


void CL_DP80057::FIFO_Reset(){
  SetCommand(mode | 0x00000001);
}

void CL_DP80057::ForceTrigger(){
  SetCommand(mode | 0x00000002);
}

void CL_DP80057::BUSY(bool flag){
  if(flag)
    mode = (mode & 0x0000c07f) | 0x00001000;
  else
    mode = (mode & 0x0000c07f) | 0x00002000;
  SetCommand(mode);
}

void CL_DP80057::LED(bool flag){
  if(flag)
    mode = (mode & 0x0000c07f) | 0x00001000;
  else
    mode = (mode & 0x0000c07f) | 0x00002000;
  SetCommand(mode);
}

void CL_DP80057::Power(bool flag){
  if(flag)
    mode = (mode & 0x0000307f) | 0x00004000;
  else
    mode = (mode & 0x0000307f) | 0x00008000;
  SetCommand(mode);
}

void CL_DP80057::ExtTrgIn(bool flag){
  if(flag)
    mode = (mode & 0x0000f06f) | 0x00000010;
  else
    mode = (mode & 0x0000f06f) | 0x00000000;
  SetCommand(mode);
}

void CL_DP80057::ExtTrgOut(){
  mode = (mode & 0x0000f03f) | 0x00000020;
  SetCommand(mode);
}

void CL_DP80057::BusyOut(){
  mode = (mode & 0x0000f05f) | 0x00000040;
  SetCommand(mode);
}


CL_DP80057::CL_DP80057(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
  mode = 0;
}

CL_DP80057::CL_DP80057(){
  mode = 0;
}

CL_DP80057::~CL_DP80057(){
}
