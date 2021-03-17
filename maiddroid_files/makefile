G1_TP2_maiddroid: main.o sim.o visual.o
	g++ -Wall -o maiddroid main.o sim.o visual.o
	
main.o: main.cpp sim.h struct.h const.h
	g++ -Wall -c main.cpp
	
sim.o: sim.cpp sim.h struct.h const.h
	g++ -Wall -c sim.cpp
	
visual.o: visual.cpp visual.h sim.h struct.h const.h
	g++ -Wall -c visual.cpp
#########################################
clean:
	rm *.o
	
clean_all: clean
	rm maiddroid
