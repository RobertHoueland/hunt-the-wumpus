CC = g++ -ggdb3
exe_file = hunt_wumpus

$(exe_file): *.o
	$(CC) *.o -o $(exe_file)
*.o: src/*.cpp
	$(CC) -c src/*.cpp

clean:
	rm -f *.out *.o $(exe_file)