bandle: server client

server: server.o
	g++ -o server server.o ../../resources/common.o ../../resources/multithreading.o -lcrypto -pthread -lssl
server.o: server.cpp
	g++ -c --std=c++0x server.cpp -lcrypto -I../../resources -pthread

client: client.o
	g++ -o client client.o  ../../resources/common.o ../../resources/multithreading.o -pthread  -lcrypto -lssl

client.o : client.cpp
	g++ --std=c++0x -c client.cpp -I../../resources

