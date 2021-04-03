#include "../zhelpers.h"

int main(void) {

    void *context = zmq_ctx_new();
    void *frontend = zmq_socket(context, ZMQ_ROUTER); // for clients to connect
    void *backend = zmq_socket(context, ZMQ_DEALER); // for workers to connect

    // bind the sockets
    zmq_bind(frontend, "tcp://*:5555");
    zmq_bind(backend, "tcp://*:5556");

    zmq_pollitem_t items[] = {
        {frontend, 0, ZMQ_POLLIN, 0},
        {backend, 0, ZMQ_POLLIN, 0}
    };

    while (1) {

        zmq_msg_t msg;
        zmq_poll(items, 2, -1);

        if (items[0].revents & ZMQ_POLLIN) {
           while (1) {
                zmq_msg_init(&msg);
                zmq_msg_recv(&msg, frontend, 0);

                int more = zmq_msg_more(&msg);
                zmq_msg_send(&msg, backend, more ? ZMQ_SNDMORE : 0);
                zmq_msg_close(&msg);

                if (! more) {
                    break;
                }
           }
        }

        if (items[1].revents & ZMQ_POLLIN) {
            while (1) {

                zmq_msg_init(&msg);
                zmq_msg_recv(&msg, backend, 0);
                
                int more = zmq_msg_more(&msg);
                zmq_msg_send(&msg, frontend, more ? ZMQ_SNDMORE : 0);
                zmq_msg_close(&msg);

                if (! more) {
                    break;
                }
            }
        }

    }

    zmq_close(frontend);
    zmq_close(backend);
    zmq_ctx_destroy(context);

    return 0;
}