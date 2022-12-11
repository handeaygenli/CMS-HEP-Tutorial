# Makefile for HEP Tutorial

C=c++
LD=c++

ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS =
LFLAGS =

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

SRC1= MyAnalysis.o MyJet.o MyMuon.o MyElectron.o MyPhoton.o Plotter.o

%.o: %.C %.h
		$(C) $(RCXX) -c $<

all: example

example.o: example.C MyAnalysis.h
		$(C) $(RCXX) -c $<

example: $(SRC1) example.o
		$(LD) $(SRC1) example.o $(RLXX) -o example.x
		@echo '-> example.x created!'

clean:
		@rm -f *~
		@rm -f *.o 
		@rm -f *.x
