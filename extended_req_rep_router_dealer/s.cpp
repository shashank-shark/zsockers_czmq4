#define ZMQ_BUILD_DRAFT_API 1
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main () {

    zmq::message_t m;
    uint routingId = m.routing_id();

    zmq::poller_t<> in_poller, out_poller;

    std::vector<zmq::poller_event<>> in_events;
    std::vector<zmq::poller_event<>> out_events;

    return 0;
}