#include <sstream>
#include <zmq.hpp>
#include <iostream>
#include <future>

int main() {
    zmq::context_t publisher_context;
    zmq::socket_t publisher_socket (publisher_context, zmq::socket_type::pub);
    publisher_socket.bind("tcp://*:5555");


    // wait for publishers to join -> sleep for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));

    const char *filter = "INFO: ";
    int ip1, ip2, ip3;
    

}