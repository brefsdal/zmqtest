//
//  subscriber.c
//  ZeromqTest
//
//  Created by Brian Refsdal on 9/6/15.
//  Copyright (c) 2015 Brian Refsdal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "zmq.h"
#include "zhelpers.h"

int main(int argc, const char * argv[]) {
    
    char hostname_and_port[256];
    void *ctx = NULL, *subscriber = NULL;
    int retval = 0, ii = 0;
    
    if (argc < 3) {
        printf("Usage: %s host port", argv[0]);
        exit(1);
    }
    
    sprintf(hostname_and_port, "tcp://%s:%s", argv[1], argv[2]);
    
    ctx = zmq_ctx_new();
    subscriber = zmq_socket(ctx, ZMQ_SUB);
    retval = zmq_bind(subscriber, hostname_and_port);
    
    if (retval != 0) {
        fprintf(stderr, "Unable to connect to zmq socket on host %s port %s\n", argv[1], argv[2]);
        exit(2);
    }
    
    retval = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, NULL, 0);
    
    for (ii = 0; ii < 100; ii++) {
        char *message = (char *) s_recv(subscriber);
        printf("[%d]: '%s'\n", ii+1, message);
        free(message);
    }
    
    zmq_close(subscriber);
    zmq_ctx_destroy(ctx);
    return 0;
}