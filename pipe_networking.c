#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

#include "pipe_networking.h"

int server_handshake ( int * client ) {
  
  char message[MESSAGE_BUFFER_SIZE];
  
  printf("[SERVER] Handshake initiated\n");
  
  mkfifo ("waluigi" , 0666 );
  printf("[SERVER] Pipe created\n");
  
  *client = open ( "waluigi" , O_RDONLY );
  printf ("[SERVER] Connection detected\n");
  
  read(*client, message, MESSAGE_BUFFER_SIZE); 
  printf("[SERVER] Received message: %s\n", message);
  
  //no longer need pipe
  unlink("waluigi");
	
  int toClient = open(message, O_WRONLY);
  
  printf("[SERVER] Connected to private pipe: %s\n", message);
  
  strcpy(message, "hey xd");
  printf("[SERVER] Sending message: %s\n", message);
  write(toClient, message, strlen(message));
  
  return toClient;
}

int client_handshake ( int * server ) {
  
  char message[MESSAGE_BUFFER_SIZE];
  
  printf ("[CLIENT] Handshake started");
  
  char n[10];
  sprintf(n, "%d", getpid());
  mkfifo ( n , 0666 );
  
  printf ("[CLIENT] Pipe %s created\n" , n);
  *server = open ("waluigi", O_WRONLY);
  
  printf ("[CLIENT] Connected to WALUIGI...\n");
  
  int fd = write (*server, n, sizeof(n));
  
  int toServer = open (n, O_RDONLY);
  printf("[CLIENT] Connection detected...\n");
  
  read(toServer, message, MESSAGE_BUFFER_SIZE);
  printf("[CLIENT] Received message: %s\n", message);
  
  remove(n);//getting rid of the unessecary private pipe
  
  return toServer;
    
}
