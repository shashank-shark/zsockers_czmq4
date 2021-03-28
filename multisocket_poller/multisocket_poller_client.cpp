#include <iostream>
#include <zmq.hpp>
#include <future>
#include <random>

int main (int argc, char *argv[]) {

    // The context remains same for both the connections.
    zmq::context_t poller_context(1);

    zmq::socket_t reciever_socket_puller (poller_context, zmq::socket_type::pull);
    reciever_socket_puller.connect("tcp://localhost:5556");

    zmq::socket_t reciever_socket_sub (poller_context, zmq::socket_type::sub);
    std::string filter = "INFO: ";
    reciever_socket_sub.setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), filter.size());
    reciever_socket_sub.connect("tcp://localhost:5555");

    // set the polling items
    /*
        NOTE: The structure of zmq_pollitem_t

        typedef struct {
            void *socket;
            int fd;
            short events;
            short revents;
        } zmq_pollitem_t;
    */
    zmq::pollitem_t items[] = {
        {static_cast<void*> (reciever_socket_puller), 0, ZMQ_POLLIN, 0},
        {static_cast<void*> (reciever_socket_sub), 1, ZMQ_POLLIN, 0}
    };

    while (true) {

        zmq::message_t msg;
        zmq::poll (&items[0], 2, -1);

        if (items[0].revents & ZMQ_POLLIN) {
            reciever_socket_puller.recv(msg, zmq::recv_flags::none);
            std::cout << "Message Recieved: " << msg.to_string() << std::endl;
        }

        if (items[1].revents & ZMQ_POLLIN) {
            reciever_socket_sub.recv(msg, zmq::recv_flags::none);
            std::cout << "Message Recieved: " << msg.to_string() << std::endl;
        }

        msg.rebuild();
    }

    return 0;
    
}