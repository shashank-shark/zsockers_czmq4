#include <iostream>
#include <sstream>
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main() {
    
    std::cout << "Starting the subscriber: " << std::endl;
    zmq::context_t sub_ctx; zmq::socket_t sub_sockt(sub_ctx, zmq::socket_type::sub);
    std::string filter("INFO: ");
    sub_sockt.setsockopt(ZMQ_SUBSCRIBE, "INFO: ", filter.size());
    sub_sockt.connect("tcp://localhost:5555");

    while (true) {
        zmq::message_t sub_msg;
        sub_sockt.recv(sub_msg, zmq::recv_flags::none);
        std::cout << sub_msg.to_string() << std::endl;
    }
    

    return 0;
}