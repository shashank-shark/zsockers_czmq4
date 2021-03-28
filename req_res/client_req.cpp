#include <zmq.hpp>
#include <string>
#include <iostream>
#include <sstream>

int  main() {
    
    std::cout << "Starting the Client" << std::endl;
    zmq::context_t context(1);
    zmq::socket_t reqsocket (context, ZMQ_REQ);
    reqsocket.connect("tcp://localhost:5555");

   for (int i = 0; i < 10; i++) {
        zmq::message_t message;
        reqsocket.send(zmq::str_buffer("HELLO"), zmq::send_flags::none);
        reqsocket.recv(message, zmq::recv_flags::none);
        std::istringstream iss(static_cast<char*>(message.data())); std::string str;
        iss >> str;
        std::cout << str.substr(0,5) << " Recieved from server : " << std::endl;
    }
    
    return 0;
}