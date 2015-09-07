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

int main(int argc, const char * argv[]) {
    
    char hostname_and_port[256], message_buf[36];
    void *ctx = NULL, *subscriber = NULL;
    int retval = 0, ii = 0, nbytes = 0;
    
    if (argc < 3) {
        printf("Usage: %s host port", argv[0]);
        exit(1);
    }
    
    snprintf(hostname_and_port, 256, "tcp://%s:%s", argv[1], argv[2]);
    
    ctx = zmq_ctx_new();
    subscriber = zmq_socket(ctx, ZMQ_SUB);
    printf("connecting to %s", hostname_and_port);
    retval = zmq_connect(subscriber, hostname_and_port);
    
    if (retval != 0) {
        fprintf(stderr, "ERROR: Unable to connect to zmq socket on host %s port %s\n", argv[1], argv[2]);
        exit(2);
    }
    
    retval = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, NULL, 0);
    
    for (ii = 0; ii < 100; ii++) {
        nbytes = zmq_recv(subscriber, message_buf, 36, 0);
        if (-1 == nbytes) {
            fprintf(stderr, "ERROR: Unable to read bytes on host %s port %s\n", argv[1], argv[2]);
        }
        printf("%s\n", message_buf);
    }
    
    zmq_close(subscriber);
    zmq_ctx_destroy(ctx);
    return 0;
}