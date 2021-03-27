#include <czmq.h>
#include <stdio.h>

int main() {
	zsock_t *publisher = zsock_new(ZMQ_PUB);
	zsock_set_curve_server(publisher, true);
	puts("hello, shashank!");
	zsock_destroy(&publisher);
	return 0;
}
