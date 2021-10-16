#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>

#include "SiTCP_VME.h"
#include "RPV130.h"
#include "RPV160.h"
#include "GNV230.h"

#define  MASTER_IP  "192.168.10.16"
//#define  RPV_Base   0x5000
//#define  FADCbase   0x800000
#define  GNV230base 0x400000

using namespace std;

int main(int argc, char *argv[]){
  SiTCP_VME *vme = new SiTCP_VME(MASTER_IP);
  //RPV130 rpv(vme, RPV_Base);
  //RPV160 fadc(vme, FADCbase);
  GNV230 fadc(vme, GNV230base);

  // DIO test
  // int tmp = rpv.Read();
  // cout << hex << setw(8) << setfill('0') << tmp << endl;

  // for(int i=0; i<10; i++){
  //   rpv.Level(0x0f);
  //   tmp = rpv.Read();
  //   cout << hex << setw(8) << setfill('0') << tmp << endl;

  //   rpv.Level(0x00);
  //   tmp = rpv.Read();
  //   cout << hex << setw(8) << setfill('0') << tmp << endl;
  // }

  // FADC test
  // fadc.Initialize();
  // fadc.Clear();
  // fadc.Start();
  // usleep(10);
  // fadc.Stop();

  // if(fadc.DataExist()){
  //   char data[8][500];
  //   for(int ch=0; ch<8; ch++)
  //     fadc.Read(ch, 500, data[ch]);

  //   for(int i=0; i<500; i++){
  //     for(int ch=0; ch<8; ch++)
  //   	cout << hex << setw(2) << setfill('0')
  //   	     << ((unsigned)data[ch][i] & 0xff) << " ";
  //     cout << endl;
  //   }
  // }

  // GNV230
  fadc.SetMemSize(0, 1, 0);

  fadc.Reset();
  fadc.Start();
  sleep(1);

  fadc.Stop();
  //if(fadc.WaitData()){
    while(true){
    char wave[8*200];
    fadc.Read_Data(200, wave);

    for(int i=0; i<200; i++){
      for(int ch=0; ch<8; ch++)
	cout << hex << setw(2) << setfill('0')
	     << ((unsigned)wave[ch*200+i] & 0xff) << " ";

      cout << endl;
    }
    sleep(1000);
  }
}
