#include "Board.h"

string MediaInputReader :: read_uart_buffer() {
    static char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    int serial_port = open(port.c_str(), O_RDWR | O_NOCTTY);
    if (serial_port < 0) return "";

    termios tty;
    tcgetattr(serial_port, &tty);

    speed_t speed = (baudrate == 9600) ? B9600 : B115200;
    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);

    tty.c_cflag = CS8 | CREAD | CLOCAL;
    tty.c_lflag = 0;
    tty.c_iflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 1;

    tcsetattr(serial_port, TCSANOW, &tty);

    int num_bytes = read(serial_port, buffer, sizeof(buffer) - 1);
    close(serial_port);

    if (num_bytes > 0) {
        buffer[num_bytes] = '\0';
        return string(buffer);
    }

    return "";
}

void MediaInputReader :: trim_message(string& msg) {
    msg.erase(msg.find_last_not_of(" \n\r\t.") + 1);
}

MediaInputReader :: MediaInputReader(const string& port, int baudrate)
        : port(port), baudrate(baudrate) {}

string MediaInputReader :: listen_once() {
    string message = read_uart_buffer();
    trim_message(message);

    if (message == "P" || message == "N" || message == "S" || message == "T") {
        cout << "[Command]: " << message << endl;
        return message;
    }

    if (regex_match(message, regex("^[0-9.]+$"))) {
        string last_message = message;
        auto last_time = chrono::steady_clock::now();

        while (true) {
            this_thread::sleep_for(chrono::milliseconds(100));
            string next = read_uart_buffer();
            trim_message(next);
        
            if (!next.empty() && regex_match(next, regex("^[0-9.]+$"))) {
                last_message = next;
                last_time = chrono::steady_clock::now();
            }
        
            auto now = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - last_time).count();
        
            if (elapsed > 1200 && !last_message.empty()) {
                size_t lastDot = last_message.find_last_of('.');
                if (lastDot != string::npos && lastDot + 1 < last_message.length()) {
                    string vol = last_message.substr(lastDot + 1);
                    cout << "[Volume]: " << vol << endl;
                    return vol;
                } else {
                    cout << "[Raw Volume String]: " << last_message << endl;
                    return last_message;
                }
            }
        }
        
    }

    if (!message.empty()) {
        cout << "[Unknown]: " << message << endl;
        return message;
    }
    return "";
}
