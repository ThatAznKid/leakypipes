#pragma once

#define MESSAGE_BUFFER_SIZE 1000

int server_handshake ( int * client );

int client_handshake ( int * server );