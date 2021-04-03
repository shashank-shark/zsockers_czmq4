#include "../zhelpers.h"
#include <unistd.h>


int main (void) {

    void *context = zmq_ctx_new();

    void *worker = zmq_socket(context, ZMQ_REP);
    zmq_connect(worker, "tcp://localhost:5556");

    while (1) {

        char *string = s_recv(worker);

        
        printf ("\033[0;32m");
        printf ("Recieved request from broker : ");
        printf ("\033[0m");
        printf ("%s\n", string);

        sleep(1);

        s_send(worker, "WORLD!");

    }

    zmq_close(worker);
    zmq_ctx_destroy(context);
    return 0;
}