Target = main PHADC
Module = SiTCP_VME
Module += RPV130 RPV160 LeCroy1182 HV006 GNV230 MemTMB2
Module += ArkusScaler ArkusADC CL_DP80057 HA_80256

ObjSuf = .o
SrcSuf = .cxx

# Compiler flags
CFLAGS = -Wall -O2 -c

# Debug flags
#CFLAGS += -g

#LDFLAGS += -all_load
#LDFLAGS += -g

TargetSrc = $(Target:%=%$(SrcSuf))
TargetObj = $(Target:%=%$(ObjSuf))
ModuleSrc = $(Module:%=%$(SrcSuf))
ModuleObj = $(Module:%=%$(ObjSuf))

all	: $(Target)

$(Target): $(TargetObj) $(ModuleObj)
	$(CXX) -o $@ $@.o $(ModuleObj) $(LDFLAGS)
	mv $@ ../bin/

.cxx.o	:
	$(CXX) $(CFLAGS) -c -o $@ $<

.SUFFIXES: .o .cxx

clean	:
	rm -f *.o
	rm -f *~
	rm -f ../bin/$(Target)
