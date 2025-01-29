#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <unistd.h> 
using namespace std;



int main(){


char tcp_server_message[256] = " Hello, you have successfully connected to the TCP Server!! \n\n Bye Bye!!!\n\n";
struct sockaddr_in tcp_server_address;
int tcp_server_socket;
int tcp_client_socket;


tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0);
if(tcp_server_socket == 0){
    perror("Socket creation failed");
    exit(1);
}

tcp_server_address.sin_family = AF_INET;
tcp_server_address.sin_addr.s_addr = INADDR_ANY;
tcp_server_address.sin_port = htons(8080);

if(bind(tcp_server_socket, (struct sockaddr *) &tcp_server_address, sizeof(tcp_server_address)) < 0){
    perror("Binding failed");
    exit(1);
}

if(listen(tcp_server_socket, 1) <0){
    perror("listen");
    exit(1);
}



tcp_client_socket = accept(tcp_server_socket, NULL, NULL);

//send data stream
send(tcp_client_socket, tcp_server_message, sizeof(tcp_server_message), 0); 

//close the socket
close(tcp_server_socket);



    return 0;
}