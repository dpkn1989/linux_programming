#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <cerrno>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Proper usage is: " << argv[0] << " port_number" << std::endl;
        return -1;
    }

    int port = std::stoi(argv[1]);
    int server_fd, new_socket;
    struct sockaddr_in address;
    // int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* msg = "JaiSriRam from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Attaching socket to the port
    // if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    //     perror("Setsockopt failed");
    //     close(server_fd);
    //     return -1;
    // }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Binding the socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Socket Bind failed");
        close(server_fd);
        return -1;
    }

    // Listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        return -1;
    }

    std::cout << "Server listening on port " << port << std::endl;

    // Accepting a connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        return -1;
    }

    // Reading data from the client
    read(new_socket, buffer, sizeof(buffer));
    std::cout << "Message from client: " << buffer << std::endl;

    // Sending response to the client
    send(new_socket, msg, strlen(msg), 0);
    std::cout << "Response message sent." << std::endl;

    // Closing the socket
    close(new_socket);
    close(server_fd);
    return 0;
}