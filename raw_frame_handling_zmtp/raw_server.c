#include <czmq.h>
#include <stdio.h>
int main() {

	zsock_t *raw_stream_sock = zsock_new(ZMQ_STREAM);
	int rc = zsock_bind(raw_stream_sock, "tcp://*:5555");
	assert(rc != -1);
	printf ("RAW Server ready at local port : 5555\n");

	zmsg_t *msg = zmsg_recv(raw_stream_sock);
	assert(msg);

	char *str = zmsg_popstr(msg);
	printf ("RAW MESSAGE : %s\n", str);

	zsock_destroy(& raw_stream_sock);
	return 0;
}
