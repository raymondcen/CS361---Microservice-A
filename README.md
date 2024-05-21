1. Download all the makefile and microservice.cpp and run the makefile by typing "make" into the terminal. This will compile all three files.
2. Then to run the file, you have to type in "server" into the terminal which will then create a socket on port 3503. Then your client, or the client in the file (client.cpp) will be also be ran and connected to the same port which will then ask the user for a message
3. Type the message and hit enter
4. The ASCII Word Art will be returned to the client.
Here is an exmaple call:
```
int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[2048] = {0};
    char buffer[2048] = {0};

    
    //create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "Socket creation error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cerr << "Invalid address/ Address not supported" << endl;
        return -1;
    }

    //connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection Failed" << endl;
        return -1;
    }

    cout << "Enter message to send: ";
    cin.getline(message, sizeof(message));

    //send message to server
    send(sock, message, strlen(message), 0);

    //get back message from server
    recv(sock, buffer, 1024, 0);
    cout << buffer << endl;

    close(sock);
    return 0;
}

```

![uml](https://github.com/raymondcen/cs361/assets/109717872/6fa705fc-c8b5-4f46-8dfc-1553fcb346cd)

