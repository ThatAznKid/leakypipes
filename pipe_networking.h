#pragma once

#define MESSAGE_BUFFER_SIZE 1024

int server_handshake ( int * client );

int client_handshake ( int * server );