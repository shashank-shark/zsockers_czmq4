#include <iostream>
#include <zmq.hpp>

int main () {
    zmq::context_t context (1);
    zmq::socket_t socket (context, zmq::socket_type::req);
    socket.connect("tcp://localhost:5555");

    for (int i = 0; i < 10; i++) {
        zmq::message_t m;
        socket.send(zmq::str_buffer("REQ:QQQ"), zmq::send_flags::none);
        socket.recv(m, zmq::recv_flags::none);
        std::cout << "rec: " << m.to_string() << std::endl;
        m.rebuild();
    }

    return 0;
}