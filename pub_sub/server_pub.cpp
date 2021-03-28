#include <sstream>
#include <zmq.hpp>
#include <iostream>
#include <future>
#include <random>

int main() {
    zmq::context_t publisher_context;
    zmq::socket_t publisher_socket (publisher_context, zmq::socket_type::pub);
    publisher_socket.bind("tcp://*:5555");


    // wait for publishers to join -> sleep for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));

    const char *filter = "INFO: ";
    int ip1, ip2, ip3;

    // get a random number from a device
    std::random_device rd;  std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(25, 68);

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ip1 = dist(gen);    ip2 = dist(gen);    ip3 = dist(gen);

        std::ostringstream oss;
        oss << filter << ip1 << " " << ip2 << " " << ip3;

        zmq::message_t publisher_data(oss.str());
        publisher_socket.send(publisher_data, zmq::send_flags::none);
    }

    return 0;
}