# Lee alima 313467441 04
# Omer havakook 203345087 06

a.out: compileAll
	g++ -pthread -o ../../exe/Server.out *.o 
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -pthread -c src/*.cpp
