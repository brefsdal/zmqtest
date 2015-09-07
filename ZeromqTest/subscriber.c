//
//  subscriber.c
//  ZeromqTest
//
//  Created by Brian Refsdal on 9/6/15.
//  Copyright (c) 2015 Brian Refsdal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "zmq.h"

#define MSGSIZE (32)

int main(int argc, const char * argv[]) {
    
    char message[MSGSIZE];
    void *ctx = NULL, *subscriber = NULL;
    int retval = 0, ii = 0, nbytes = 0;
    
    ctx = zmq_ctx_new();

    subscriber = zmq_socket(ctx, ZMQ_SUB);

    retval = zmq_connect(subscriber, "tcp://localhost:9000");
    if (retval != 0) {
        fprintf(stderr, "ERROR: Unable to connect to zmq publisher socket\n");
        exit(2);
    }
    
    /* Important! Set the subscribe filter */
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, NULL, 0);

    for (ii = 0; ii < 100; ii++) {
        nbytes = zmq_recv(subscriber, message, MSGSIZE, 0);
        if (-1 == nbytes) {
            fprintf(stderr, "ERROR: Unable to read bytes on host %s port %s\n", argv[1], argv[2]);
        }
        
        printf("%s\n", message);
    }
    
    zmq_close(subscriber);
    zmq_ctx_destroy(ctx);
    return 0;
}