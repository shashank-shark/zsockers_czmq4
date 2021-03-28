#include <iostream>
#include <sstream>
#include <zmq.hpp>

int main() {
    
    std::cout << "Starting the subscriber: " << std::endl;
    zmq::context_t sub_ctx; zmq::socket_t sub_sockt(sub_ctx, zmq::socket_type::sub);
    
    
}