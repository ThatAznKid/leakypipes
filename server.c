#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

#include "pipe_networking.h"

void process( char * s );

int main() {

  int to_client, from_client;
  char buffer[MESSAGE_BUFFER_SIZE];
  
  printf ("[SERVER] Initialized server...\n");
  
  to_client = server_handshake( &from_client );
  
  printf("[SERVER] Connected to client...\n");

  read( from_client, buffer, sizeof(buffer) );
  printf("[SERVER] Received client message: %s\n" , buffer);
  
  process( buffer );
  write( to_client, buffer, sizeof(buffer));
  printf("[SERVER] Message sent.\n");
  
  return 0;
}




void process( char * s ) {

  while ( *s ) {
    *s = (*s - 'a' + 13) % 26 + 'a';
    s++;
  }
}
