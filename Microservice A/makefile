CC=g++ -std=c++11 -g 
CLIENT_EXEC = client
SERVER_EXEC = server


# Complete the makefile
# Your code here: 
all: $(CLIENT_EXEC) $(SERVER_EXEC) 

$(CLIENT_EXEC): client.o 
	$(CC) client.o  -o $(CLIENT_EXEC)

client.o: client.cpp
	$(CC) -c client.cpp

$(SERVER_EXEC): microservice.o 
	$(CC) microservice.o  -o $(SERVER_EXEC)

microservice.o: microservice.cpp
	$(CC) -c microservice.cpp






clean:
	rm -f *.o $(CLIENT_EXEC) $(SERVER_EXEC)
