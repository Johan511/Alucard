main.out: udp_server.o map.o state.o
	g++   -o main.out udp_server.o map.o state.o

udp_server.o:
	g++ -g   -c udp_server.cpp

map.o: ./state/map.cpp ./0_headers/state/map.h
	g++ -g   -c ./state/map.cpp

state.o: ./state/state.cpp ./0_headers/state/state.h
	g++ -g   -c ./state/state.cpp

clean:
	rm *.o *.i *.out

run:
	make && rm *.o *.i