#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>
#include <time.h>

#include "SiTCP_VME.h"
#include "RPV130.h"
#include "HV006.h"

#define  MASTER_IP  "192.168.10.16"
#define  RPV_Base   0x5000
#define  PHADC_base 0x140000

using namespace std;

int main(int argc, char *argv[]){

  time_t start_time;
  start_time = time(NULL);

  if(argc!=4){
    cerr << " usage> PHADC <ch0 file name><ch1 file name> <#event>" << endl;
    exit(1);
  }

  int count = atoi(argv[3]);
  string filename = argv[1];
  string filename2 = argv[2];

  SiTCP_VME *vme = new SiTCP_VME(MASTER_IP);
  
  RPV130 rpv(vme, RPV_Base);
  HV006 phadc(vme, PHADC_base);

  int index=0;
  ofstream outData(filename.c_str(), ios::out);
  ofstream outData2(filename2.c_str(), ios::out);

  phadc.Reset();
//  rpv.Pulse(0x03);
  do{
  /*    for(;;)
      if(rpv.Read())
     	break;
  */
    if(phadc.Wait()){
      short data = phadc.Read(1);
      short data2 = phadc.Read(2);
      outData.write((char*)&data, sizeof(data));
      outData2.write((char*)&data2, sizeof(data));
   }
    index++;
    phadc.Reset();
    if(!(index%10))
      cout << dec << index << '\r' << flush;

    //rpv.Pulse(0x03);
  }while(index < count);
  cout << endl;

  outData.close();

  printf("time:%.1f\n", difftime(time(NULL), start_time));
}

