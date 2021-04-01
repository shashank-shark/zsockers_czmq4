#include <iostream>
#include <future>
#include <sstream>
#include <zmq.hpp>
#include <zmq_addon.hpp>
#define ZMQ_BUILD_DRAFT_API 1

int main (int argc, char *argv[])  {

    zmq::context_t main_ctx(1);
    
    zmq::socket_t frontend (main_ctx, zmq::socket_type::router);
    zmq::socket_t worker_end (main_ctx, zmq::socket_type::dealer);

    frontend.bind("tcp://*:5555");
    worker_end.bind("tcp://*:5556");

    zmq::pollitem_t items[] {
        {static_cast<void*>(frontend), 0, ZMQ_POLLIN, 0},
        {static_cast<void*>(worker_end), 1, ZMQ_POLLIN, 0}
    };

    

    while (true) {
        zmq::message_t reqMsg;
        int more;

        reqMsg.rebuild();

        // start polling
        zmq::poll (&items[0], 2, -1);

        if (items[0].revents & ZMQ_POLLIN) {
            frontend.recv (reqMsg, zmq::recv_flags::none);
            std::cout << "Request recieved from client through frontend: " << reqMsg.to_string() << std::endl;
            std::cout << "Passing the request: " << reqMsg.to_string() << " to backend via dealer " << std::endl;
            reqMsg.rebuild();
            frontend.send(zmq::str_buffer("SERV_RESP"), zmq::send_flags::none);
            std::cout << "Sent message to client: " << std::endl;
        }

        if (items[1].revents & ZMQ_POLLIN) {
            worker_end.recv(reqMsg, zmq::recv_flags::none);
            std::cout << "Recieved request from dealer: " << reqMsg.to_string() << std::endl;
            reqMsg.rebuild();
            break;
        }
    }

    return 0;

}