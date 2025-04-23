#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <regex>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
class MediaInputReader {
    private:
        string port;
        int baudrate;
    public:
        string read_uart_buffer();
        
        void trim_message(string& msg);
    
        MediaInputReader(const string& port, int baudrate);

        string listen_once();
    };

#endif
    