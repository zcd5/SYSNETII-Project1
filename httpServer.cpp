#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <unistd.h> 
using namespace std;



int main(){


struct sockaddr_in tcp_server_address;
int tcp_server_socket;
int tcp_client_socket;


//Creation of socket
tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0);
if(tcp_server_socket == 0){
    perror("Socket creation failed");
    exit(1);
}

//Setting the socket's address
tcp_server_address.sin_family = AF_INET;
tcp_server_address.sin_addr.s_addr = INADDR_ANY;
tcp_server_address.sin_port = htons(8080);

//Binding the socket
if(bind(tcp_server_socket, (struct sockaddr *) &tcp_server_address, sizeof(tcp_server_address)) < 0){
    perror("Binding failed");
    exit(1);
}

//listening for connections
if(listen(tcp_server_socket, 5) < 0){
    perror("listen");
    exit(1);
}



tcp_client_socket = accept(tcp_server_socket, NULL, NULL);


//Serving the initial html page (index.html)
ifstream file("index.html");
stringstream buffer;
 buffer << file.rdbuf();
string htmlPage = buffer.str();
string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + htmlPage;



//send data stream to browser
send(tcp_client_socket, response.c_str(), response.length(), 0); 

cout << "You have successfully connected to the server!" << endl;


/*TODO: add while true loop so server can keep servicing requests*/

/*TODO: if statements that service the client's requests (links on html page)*/

//close the socket
close(tcp_server_socket);



return 0;
}