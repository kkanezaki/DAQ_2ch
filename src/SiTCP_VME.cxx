#include "SiTCP_VME.h"

char SiTCP_VME::Read_8(int addr, int am, int opt){
  char com[12] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  0, 0, 0, 1,
		  (char)((am | SV_D8) & 0xff), (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0};
  com[11] = CRC_8(com);
  send(sock, com, 12, 0);
  pack_num++;

  char reply[32];
  recv(sock, reply, 32, 0);
  char check = CRC_8(reply);

  if(check != reply[11] && reply[10] != com[10])
    return -1;

  return reply[12];
}

short SiTCP_VME::Read_16(int addr, int am, int opt){
  char com[12] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  0, 0, 0, 2,
		  (char)((am | SV_D16) & 0xff), (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0};
  com[11] = CRC_8(com);
  send(sock, com, 12, 0);
  pack_num++;

  char reply[32];
  recv(sock, reply, 32, 0);
  char check = CRC_8(reply);

  if(check != reply[11] && reply[10] != com[10])
    return -1;

  short data 
    = ((unsigned)(reply[12] & 0xff) << 8)
    + ((unsigned)(reply[13] & 0xff));

  return data;
}

int SiTCP_VME::Read_32(int addr, int am, int opt){
  char com[12] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  0, 0, 0, 4,
		  (char)((am | SV_D32) & 0xff), (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0};
  com[11] = CRC_8(com);
  send(sock, com, 12, 0);
  pack_num++;

  char reply[32];
  recv(sock, reply, 32, 0);
  char check = CRC_8(reply);

  if(check != reply[11] && reply[10] != com[10])
    return -1;

  int data
    = ((unsigned)(reply[12] & 0xff) << 24)
    + ((unsigned)(reply[13] & 0xff) << 16)
    + ((unsigned)(reply[14] & 0xff) << 8)
    + ((unsigned)(reply[15] & 0xff));

  return data;
}

int SiTCP_VME::Read_N(int addr, const int num, char *buf, int am, int opt){
  char com[12] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  (char)((num >> 24) & 0xff), (char)((num >> 16) & 0xff),
		  (char)((num >>  8) & 0xff), (char)(num & 0xff), 
		  (char)((am | SV_D8) & 0xff), (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0};
  com[11] = CRC_8(com);
  send(sock, com, 12, 0);
  pack_num++;

  int n_head=0, index=0;
  unsigned d_size=0, p_index=0;;
  char header[12];
  while(index < num){
    char reply[4096];
    int n = recv(sock, reply, sizeof(reply), 0);

    for(int i=0; i<n; i++){
      if(n_head<12){
	header[n_head] = reply[i];
	n_head++;
      }

      if(d_size>0){
	buf[index] = reply[i];
	index++;
	p_index++;
      }

      if(n_head>11 && d_size<1){
	char check = CRC_8(header);
	if(check != header[11])
	  return -1;
	d_size 
	  = (((unsigned)header[4] & 0xff) << 24) 
	  + (((unsigned)header[5] & 0xff) << 16) 
	  + (((unsigned)header[6] & 0xff) << 8) 
	  + (((unsigned)header[7] & 0xff));
	p_index=0;
      }
      
      if(d_size>0 && d_size==p_index){
	n_head = 0;
	d_size = 0;
	p_index = 0;
      }
    }
  }
  
  return index;
}

int SiTCP_VME::Read_N(int addr, const int num, short *buf, int am, int opt){
  int size = num << 1;
  char com[12] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  (char)((size >> 24) & 0xff), (char)((size >> 16) & 0xff),
		  (char)((size >>  8) & 0xff), (char)(size & 0xff), 
		  (char)((am | SV_D16) & 0xff), (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0};
  com[11] = CRC_8(com);
  send(sock, com, 12, 0);
  pack_num++;

  int n_head=0, index=0;
  unsigned d_size=0, p_index=0;;
  char header[12];
  while(index < num){
    char reply[4096];
    int n = recv(sock, reply, sizeof(reply), 0);

    for(int i=0; i<n; i++){
      if(n_head<12){
	header[n_head] = reply[i];
	n_head++;
      }

      if(d_size>0){
	if(p_index%2){
	  buf[index] += ((unsigned)reply[i] & 0xff);
	  index++;
	}
	else
	  buf[index] = (((unsigned)reply[i] & 0xff) << 8);
	p_index++;
      }

      if(n_head>11 && d_size<1){
	char check = CRC_8(header);
	if(check != header[11])
	  return -1;
	d_size 
	  = (((unsigned)header[4] & 0xff) << 24) 
	  + (((unsigned)header[5] & 0xff) << 16) 
	  + (((unsigned)header[6] & 0xff) << 8) 
	  + (((unsigned)header[7] & 0xff));
	p_index=0;
      }
      
      if(d_size>0 && d_size==p_index){
	n_head = 0;
	d_size = 0;
	p_index = 0;
      }
    }
  }
  
  return index;
}

int SiTCP_VME::Read_N(int addr, const int num, int *buf, int am, int opt){
  int size = num << 2;
  char com[12] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  (char)((size >> 24) & 0xff), (char)((size >> 16) & 0xff),
		  (char)((size >>  8) & 0xff), (char)(size & 0xff), 
		  (char)((am | SV_D32) & 0xff), (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0};
  com[11] = CRC_8(com);
  send(sock, com, 12, 0);
  pack_num++;

  int n_head=0, index=0;
  unsigned d_size=0, p_index=0;;
  char header[12];
  while(index < num){
    char reply[4096];
    int n = recv(sock, reply, sizeof(reply), 0);

    for(int i=0; i<n; i++){
      if(n_head<12){
	header[n_head] = reply[i];
	n_head++;
      }

      if(d_size>0){
	if(!(p_index%4))
	  buf[index] = ((unsigned)reply[i] & 0xff);
	else{
	  buf[index] 
	    = (buf[index] << 8)
	    + ((unsigned)reply[i] & 0xff);
	  if(p_index%4==3)
	    index++;
	}
	p_index++;
      }

      if(n_head>11 && d_size<1){
	char check = CRC_8(header);
	if(check != header[11])
	  return -1;
	d_size 
	  = (((unsigned)header[4] & 0xff) << 24) 
	  + (((unsigned)header[5] & 0xff) << 16) 
	  + (((unsigned)header[6] & 0xff) << 8) 
	  + (((unsigned)header[7] & 0xff));
	p_index=0;
      }
      
      if(d_size>0 && d_size==p_index){
	n_head = 0;
	d_size = 0;
	p_index = 0;
      }
    }
  }
  
  return index;
}

bool SiTCP_VME::Write_8(int addr, char data, int am, int opt){
  char com[16] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  0, 0, 0, 1,
		  (char)((0xc0 | am | SV_D8) & 0xff), 
		  (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0,
		  0, 0, 0, 0};
  com[11] = CRC_8(com);
  com[12] = data;
  send(sock, com, 13, 0);
  pack_num++;

  char reply[32];
  recv(sock, reply, 32, 0);
  char check = CRC_8(reply);

  if(check == reply[11] && reply[10] == com[10])
    return 0;
  else
    return 1;
}

bool SiTCP_VME::Write_16(int addr, short data, int am, int opt){
  char com[16] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  0, 0, 0, 2,
		  (char)((0xc0 | am | SV_D16) & 0xff), (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0,
		  0, 0, 0, 0};
  com[11] = CRC_8(com);
  com[12] = (data >> 8) & 0xff;
  com[13] = data & 0xff;
  send(sock, com, 14, 0);
  pack_num++;

  char reply[32];
  recv(sock, reply, 32, 0);
  char check = CRC_8(reply);

  if(check == reply[11] && reply[10] == com[10])
    return 0;
  else
    return 1;
}

bool SiTCP_VME::Write_32(int addr, int data, int am, int opt){
  char com[16] = {(char)((addr >> 24) & 0xff), (char)((addr >> 16) & 0xff),
		  (char)((addr >>  8) & 0xff), (char)(addr & 0xff), 
		  0, 0, 0, 4,
		  (char)((0xc0 | am | SV_D32) & 0xff), (char)(opt & 0xff), 
		  (char)(pack_num & 0xff), 0,
		  0, 0, 0, 0};
  com[11] = CRC_8(com);
  com[12] = (data >> 24) & 0xff;
  com[13] = (data >> 16) & 0xff;
  com[14] = (data >>  8) & 0xff;
  com[15] = data & 0xff;
  send(sock, com, 16, 0);
  pack_num++;

  char reply[32];
  recv(sock, reply, 32, 0);
  char check = CRC_8(reply);

  if(check == reply[11] && reply[10] == com[10])
    return 0;
  else
    return 1;
}

char SiTCP_VME::CRC_8(char *data){
  short flag = 0xff;
  for(int i=0; i<11; i++){
    flag = flag ^ data[i];

    for(int bit=0; bit<8; bit++){
      bool ck = (flag >> 7) & 0x1;
      flag = flag << 1;
      if(ck)
	flag = flag ^ 0x07;
    }
  }
  
  return flag & 0xff;
}

bool SiTCP_VME::Open(const string ip){
  if(!dev_num){
    param.sin_port = htons(24);
    param.sin_family = AF_INET;
    param.sin_addr.s_addr = inet_addr(ip.c_str());
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0){
      cerr << " ERROR(SiTCP): Can't open socket" << endl;
      return 1;
    }
    if(connect(sock, (struct sockaddr*)&param, sizeof(param))){
      cerr << " ERROR(SiTCP): Can't connet" << endl;
      return 1;
    }
    
    dev_num++;
  }
  
  return 0;
}

void SiTCP_VME::Close(){
  if(dev_num){
    close(sock);
  }
}


SiTCP_VME::SiTCP_VME(){
  dev_num = 0;
  pack_num = 0;
}

SiTCP_VME::SiTCP_VME(const string ip){
  dev_num = 0;
  pack_num = 0;
  Open(ip);
}

SiTCP_VME::~SiTCP_VME(){
  if(dev_num)
    Close();
}
