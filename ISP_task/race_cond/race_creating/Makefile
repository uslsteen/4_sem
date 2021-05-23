.PHONY: clean build

CXX = g++ -std=c++2a
OPTS = -Wall -Wextra
BLD = build

all: clean bld start

start: frac_bldr.o frac.o main.o
	$(CXX) $(BLD)/frac_bldr.out $(BLD)/frac.o $(BLD)/main.o -o $(BLD)/exec.out
	
	$(i execute .out file only for example)
	./$(BLD)/exec.out

clean:
	rm -rf $(BLD)/ frac.cc

bld:
	mkdir $(BLD)/


frac_bldr.o:
	$(CXX) $(OPTS) frac_bldr.cc -o $(BLD)/frac_bldr.out
	./$(BLD)/frac_bldr.out


frac.o:
	$(CXX) $(OPTS) -c frac.cc -o $(BLD)/frac.o


main.o:
	$(CXX) $(OPTS) -c main.cc -o $(BLD)/main.o




