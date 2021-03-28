#include <iostream>
#include <zmq.hpp>
#include <string>
#include <sstream>

int main() {
    std::cout << "Starting the Server" << std::endl;
    zmq::context_t server (1);
    zmq::socket_t server_socket(server, ZMQ_REP);
    server_socket.bind("tcp://*:5555");

    while (true) {
        zmq::message_t message_from_client;
        server_socket.recv(message_from_client, zmq::recv_flags::none);
        std::cout << static_cast<char*>(message_from_client.data()) << " Recieved from Client: " << std::endl;
        zmq_sleep(1);
        server_socket.send(zmq::str_buffer("WORLD"), zmq::send_flags::none);
    }

    return 0;
}