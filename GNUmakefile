OBJS = readFrameRootRecoMain.C
EXE = readFrameRootRecoMain

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

FASTJETCXX = `fastjet-config --cxxflags`
FASTJETLIB = `fastjet-config --libs --plugins`

INCFLAGS = -I${ROOTSYS}/include -I${ROOTSYS}/include/root/
LDFLAGS = -L${ROOTSYS}/lib -L${ROOTSYS}/lib/root -lpodio -ledm4hep -ledm4eic -lpodioRootIO -lpodioDict -lfmt ${FASTJETLIB}
#LDFLAGS = -L${ROOTSYS}/lib -L${ROOTSYS}/lib/root -lpodio -ledm4hep -ledm4eic -lpodioRootIO -lpodioDict -lpodioRootIODict -lfmt

#-L${PODIO}/lib

#CXX = g++ -m32
CXX = g++ -std=c++20
FLAGS = -Wall -g $(INCFLAGS) $(LDFLAGS) $(FASTJETCXX)

COMPILE = $(CXX) $(FLAGS) -c 

all: $(EXE)

#$(EXE): $(OBJS)
#	$(CXX) -o $(EXE) $(OBJS) $(ROOTFLAGS) $(ROOTLIBS)

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(ROOTFLAGS) $(ROOTLIBS) $(FLAGS)

#%.o: %.C
	$(COMPILE) $<	
	
clean:
	rm $(EXE)

	