#include <../zhelpers.h>

int main (void) {

    void *context = zmq_ctx_new();
    void *reciever = zmq_socket(context, ZMQ_REQ);
}