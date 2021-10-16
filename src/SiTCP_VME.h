#ifndef SiTCP_VME_h
#define SiTCP_VME_h 1

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

///  parameters for SiTCP_VME_Master  //////////
#define SV_A16   0x00
#define SV_A24   0x01
#define SV_A32   0x02

#define SV_D8    0x00
#define SV_D16   0x04
#define SV_D32   0x08

#define SV_USER  0x00
#define SV_PROG  0x10
#define SV_BLT   0x20
#define SV_SUP   0x40
#define SV_SPRG  0x50
#define SV_SBLT  0x60
#define SV_F_USR 0x80
#define SV_F_PRG 0x90
#define SV_F_SUP 0xa0
#define SV_F_SPG 0xb0
////////////////////////////////////////////////

using namespace std;

class SiTCP_VME {
 public:
  SiTCP_VME();
  SiTCP_VME(const string);
  ~SiTCP_VME();

  bool   Open(const string);
  void   Close();

  char   Read_8(int addr, int am, int opt=0);
  short  Read_16(int addr, int am, int opt=0);
  int    Read_32(int addr, int am, int opt=0);

  int    Read_N(int addr, const int num, char *buf, int am, int opt=0);
  int    Read_N(int addr, const int num, short *buf, int am, int opt=0);
  int    Read_N(int addr, const int num, int *buf, int am, int opt=0);

  bool   Write_8(int addr, char data, int am, int opt=0);
  bool   Write_16(int addr, short data, int am, int opt=0);
  bool   Write_32(int addr, int data, int am, int opt=0);

  char   CRC_8(char*);

 private:
  int                 dev_num, sock;
  struct sockaddr_in  param;
  short               pack_num;
};

#endif
