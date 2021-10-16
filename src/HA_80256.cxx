#include "HA_80256.h"

void HA_80256::HA_Init(){
  T_Width(63);
  V_Width(240);
  B_Width(300);

  tHoldTime();
  BusyExtation();

  SetHeaderID(0xeb90, 0xeb91, 0xeb92, 0xeb93);
  SetHeaderSize(64, 64, 64, 64);
  SetSDSBlockSize(64, 64, 64, 64);  
}

void HA_80256::DP_Setup(){
  LED(1);
  Power(1);
  SetPipeLine(0);
  ExtTrgIn(0);
  TrigMode(0);

  SetPedestal_A(24, 0);
  SetPedestal_B(24, 0);
  SetPedestal_C(24, 0);
  SetPedestal_D(24, 0);

  SetGain_A(24, 4095);
  SetGain_B(24, 4095);
  SetGain_C(24, 4095);
  SetGain_D(24, 4095);
}

void HA_80256::Enable(char flag){
  fa = flag & 0x1;
  fb = (flag >> 1) & 0x1;
  fc = (flag >> 2) & 0x1;
  fd = (flag >> 3) & 0x1;
  PortMask(fa, fb, fc, fd);
}

void HA_80256::HA_Reset(){
  PMT_A_Command(0x1ff00000);
  PMT_B_Command(0x1ff00000);
  PMT_C_Command(0x1ff00000);
  PMT_D_Command(0x1ff00000);
  usleep(100);
}

void HA_80256::ResetTime(){
  if(fa)
    PMT_A_Command(0x10100000);
  if(fb)
    PMT_B_Command(0x10100000);
  if(fc)
    PMT_C_Command(0x10100000);
  if(fd)
    PMT_D_Command(0x10100000);
}

void HA_80256::TrigGen(int pa, int pb, int pc, int pd){
  int A_id = (pa & 0x3f) << 14;
  int B_id = (pb & 0x3f) << 14;
  int C_id = (pc & 0x3f) << 14;
  int D_id = (pd & 0x3f) << 14;

  if(fa)
    PMT_A_Command(0x10900000 | A_id);
  if(fb)
    PMT_B_Command(0x10900000 | B_id);
  if(fc)
    PMT_C_Command(0x10900000 | C_id);
  if(fd)
    PMT_D_Command(0x10900000 | D_id); 
}

void HA_80256::PowerOn(int pa, int pb, int pc, int pd){
  int A_id = (pa & 0x3f) << 14;
  int B_id = (pb & 0x3f) << 14;
  int C_id = (pc & 0x3f) << 14;
  int D_id = (pd & 0x3f) << 14;

  if(fa)
    PMT_A_Command(0x10a00000 | A_id);
  if(fb)
    PMT_B_Command(0x10a00000 | B_id);
  if(fc)
    PMT_C_Command(0x10a00000 | C_id);
  if(fd)
    PMT_D_Command(0x10a00000 | D_id); 
}

void HA_80256::TrigMode(int par){
  int trig_mode = par & 0x0001c000;

  if(fa)
    PMT_A_Command(0x10600000 | trig_mode);
  if(fb)
    PMT_B_Command(0x10600000 | trig_mode);
  if(fc)
    PMT_C_Command(0x10600000 | trig_mode);
  if(fd)
    PMT_D_Command(0x10600000 | trig_mode); 
}

void HA_80256::tHoldTime(){
  if(fa)
    PMT_A_Command(0x10701000);
  if(fb)
    PMT_B_Command(0x10701000);
  if(fc)
    PMT_C_Command(0x10701000);
  if(fd)
    PMT_D_Command(0x10701000); 
}

void HA_80256::SetThreshold(int pa, int pb, int pc, int pd, int val){
  val = (val & 0xfff);

  if(fa){
    int par = ((pa & 0x3f) << 14) + val;
    PMT_A_Command(0x10b00000 | par);
  }
  if(fb){
    int par = ((pb & 0x3f) << 14) + val;
    PMT_B_Command(0x10b00000 | par);
  }
  if(fc){
    int par = ((pc & 0x3f) << 14) + val;
    PMT_C_Command(0x10b00000 | par);
  }
  if(fd){
    int par = ((pd & 0x3f) << 14) + val;
    PMT_D_Command(0x10b00000 | par); 
  }
}

void HA_80256::BusyExtation(){
  if(fa)
    PMT_A_Command(0x10800500);
  if(fb)
    PMT_B_Command(0x10800500);
  if(fc)
    PMT_C_Command(0x10800500);
  if(fd)
    PMT_D_Command(0x10800500); 
}

void HA_80256::HA_ForceTrg(){
  if(fa)
    PMT_A_Command(0x10200000);
  if(fb)
    PMT_B_Command(0x10200000);
  if(fc)
    PMT_C_Command(0x10200000);
  if(fd)
    PMT_D_Command(0x10200000);   
}

char HA_80256::DataExist(){
  char flag = 0;
  int ena_port = fa + (fb << 1) + (fc << 2) + (fd << 3);
  
  int status = GetStatus();
  if((status & ena_port) == ena_port){
    flag = 0x01;
  }
  else if((status & ena_port) != 0){
    flag = 0xff;
    cout << " [DataExist Error] [Data Leak] Status = 0x" 
	 << hex << status << dec << endl;
  }

  return flag;
}

bool HA_80256::GetData(int *da, int *db, int *dc, int *dd){
  bool valid_a, valid_b, valid_c, valid_d;
  
  if(fa)
    valid_a = GetData_A(14, da);
  else
    valid_a = 1;

  if(fb)
    valid_b = GetData_B(14, db);
  else
    valid_b = 1;

  if(fc)
    valid_c = GetData_C(14, dc);
  else
    valid_c = 1;

  if(fd)
    valid_d = GetData_D(14, dd);
  else
    valid_d = 1;

  return valid_a & valid_b & valid_c & valid_d;
}


HA_80256::HA_80256(){
}

HA_80256::HA_80256(SiTCP_VME *master, const int base){
  SetMaster(master);
  SetBaseAddr(base);
}

HA_80256::~HA_80256(){}
