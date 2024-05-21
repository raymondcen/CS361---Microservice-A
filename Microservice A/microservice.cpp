#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;


const int PORT = 3503;
const int MAX_CONNECTIONS = 5;
const int BUFFER_SIZE = 2048;


//convert to ascii
string convertASCII(const string& receivedMessage) {
    // Define ASCII art representations for each letter
    string asciiArt[26] = {
        R"(           
     /\    
    /  \   
   / /\ \  
  / ____ \ 
 /_/    \_\         
           )",
        R"(
  ____  
 |  _ \ 
 | |_) |
 |  _ < 
 | |_) |
 |____/       
        )",
    R"(
   _____ 
  / ____|
 | |     
 | |     
 | |____ 
  \_____|    
    )",
    R"(
  _____  
 |  __ \ 
 | |  | |
 | |  | |
 | |__| |
 |_____/     
    )",
    R"(
  ______ 
 |  ____|
 | |__   
 |  __|  
 | |____ 
 |______|     
    )",
    R"(
  ______ 
 |  ____|
 | |__   
 |  __|  
 | |     
 |_| 
    )",
    R"(
   _____ 
  / ____|
 | |  __ 
 | | |_ |
 | |__| |
  \_____|
   )",
    R"(
  _    _ 
 | |  | |
 | |__| |
 |  __  |
 | |  | |
 |_|  |_|
   )",
    R"(
  _____ 
 |_   _|
   | |  
   | |  
  _| |_ 
 |_____|
   )",
    R"(
       _ 
      | |
      | |
  _   | |
 | |__| |
  \____/ 
  )",
    R"(
  _  __
 | |/ /
 | ' / 
 |  <  
 | . \ 
 |_|\_\
    )",
    R"(
  _      
 | |     
 | |     
 | |     
 | |____ 
 |______|
    )",
    R"(
  __  __ 
 |  \/  |
 | \  / |
 | |\/| |
 | |  | |
 |_|  |_|
   )",
    R"(
  _   _ 
 | \ | |
 |  \| |
 | . ` |
 | |\  |
 |_| \_|
    )",
    R"(
   ____  
  / __ \ 
 | |  | |
 | |  | |
 | |__| |
  \____/ 
  )",
    R"(
  _____  
 |  __ \ 
 | |__) |
 |  ___/ 
 | |     
 |_|            
    )",
    R"(
   ____  
  / __ \ 
 | |  | |
 | |  | |
 | |__| |
  \___\_\      
    )",
    R"(
  _____  
 |  __ \ 
 | |__) |
 |  _  / 
 | | \ \ 
 |_|  \_\
    )",
    R"(
   _____ 
  / ____|
 | (___  
  \___ \ 
  ____) |
 |_____/ 
      )",
    R"(
  _______ 
 |__   __|
    | |   
    | |   
    | |   
    |_|   
    )",
    R"(
  _    _ 
 | |  | |
 | |  | |
 | |  | |
 | |__| |
  \____/ 
    )",
    R"(
 __      __
 \ \    / /
  \ \  / / 
   \ \/ /  
    \  /   
     \/    
     )",
    R"(
 __          __
 \ \        / /
  \ \  /\  / / 
   \ \/  \/ /  
    \  /\  /   
     \/  \/    
     )",
    R"(
 __   __
 \ \ / /
  \ V / 
   > <  
  / . \ 
 /_/ \_\        
   )",
    R"(
 __     __
 \ \   / /
  \ \_/ / 
   \   /  
    | |   
    |_|   
    )",
    R"(
  ______
 |___  /
    / / 
   / /  
  / /__ 
 /_____|
     )"
    };

    string result = "";
    for (char c : receivedMessage) {
        if (isalpha(c)) {
            int index = toupper(c) - 'A';
            result += asciiArt[index] + "\n";
        }
    }

    return result;
}



int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    vector<string> messages;

    //create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "Failed to create socket" << endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Failed to bind socket" << endl;
        close(server_socket);
        return 1;
    }

    //listen for incoming connections
    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        cerr << "Failed to listen on socket" << endl;
        close(server_socket);
        return 1;
    }

    cout << "Server listening on port " << PORT << endl;

    while (true) {
        //accept connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            cerr << "Failed to accept connection" << endl;
            continue;
        }

        cout << "Connected to client" << endl;

        //receive data from the client
        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received == -1) {
            cerr << "Failed to receive data" << endl;
            close(client_socket);
            continue;
        }

        buffer[bytes_received] = '\0';
        string receivedMessage(buffer);

        //process the received message
        string responseMessage = convertASCII(receivedMessage);

        //send the response back to the client
        send(client_socket, responseMessage.c_str(), responseMessage.size(), 0);

        //close the connection
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
