.PHONY: clean

CXX = g++ -std=c++2a
OPTS = -pthread  -lpthread
BLD = build

all: clean start

start:
	$(CXX) $(OPTS) pthread_race.cc -o race.out
	$(i execute .out file only for example)
	./race.out

clean:
	rm -rf *.out
	

