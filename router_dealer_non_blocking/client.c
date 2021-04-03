#include "../zhelpers.h"

int main (void) {

    void *context = zmq_ctx_new();

    void *client = zmq_socket(context, ZMQ_REQ);
    zmq_connect(client, "tcp://localhost:5555");

    int req_num = 0;
    for (req_num = 0; req_num < 10; req_num ++) {

        s_send(client, "HELLO!");
        char *string = s_recv(client);

        printf ("\033[0;32m");
        printf ("Recieved reply from broker : ");
        printf ("\033[0m");
        printf ("%s\n", string);

        free(string);
    }

    zmq_close(client);
    zmq_ctx_destroy(context);

    return 0;
}