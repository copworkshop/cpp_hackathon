/**
 * @file PWCommDef.h
 * @brief This file contains the definitions and includes for Windows socket communication.
 */

#pragma once

// Undefine UNICODE to use ANSI Windows functions
#undef UNICODE 

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN 

#include <windows.h> 
#include <winsock2.h> 
#include <ws2tcpip.h> 
#include <stdlib.h> 
#include <stdio.h> 

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512 ///< Define default buffer length for socket communication
#define DEFAULT_PORT "27015" ///< Define default port for socket communication