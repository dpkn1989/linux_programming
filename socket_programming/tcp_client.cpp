#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>  
#include <cerrno>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Proper usage is: " << argv[0] << " server_ip port_number" << std::endl;
        return -1;
    }

    const char* server_ip = argv[1];
    int port = std::stoi(argv[2]);
    int client_fd = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char* msg = "JaiSriRam from client";

    // Creating socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Converting IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Connecting to the server
    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        close(client_fd);
        return -1;
    }

    // Sending data to the server
    send(client_fd, msg, strlen(msg), 0);
    std::cout << "Message sent to server." << std::endl;

    // Reading data from the server
    int valread = read(client_fd, buffer, sizeof(buffer));
    //std::cout << "Message received from server: " << std::string(buffer, valread) << std::endl;
    std::cout << "Message received from server: " << buffer << std::endl;

    close(client_fd);
    return 0;
}