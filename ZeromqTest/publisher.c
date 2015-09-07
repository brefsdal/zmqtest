//
//  publisher.c
//  ZeromqTest
//
//  Created by Brian Refsdal on 9/6/15.
//  Copyright (c) 2015 Brian Refsdal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zmq.h"
//#include "zhelpers.h"

int main(int argc, const char * argv[]) {

    char hostname_and_port[256], time_buf[26], message_buf[36];
    void *ctx = NULL, *publisher = NULL;
    int retval = 0, nbytes;
    long lucky_number;
    time_t current_time;
    
    if (argc < 3) {
        printf("Usage: %s host port", argv[0]);
        exit(1);
    }
    
    snprintf(hostname_and_port, 256, "tcp://%s:%s", argv[1], argv[2]);
    
    ctx = zmq_ctx_new();
    publisher = zmq_socket(ctx, ZMQ_PUB);
    printf("binding to %s", hostname_and_port);
    retval = zmq_bind(publisher, hostname_and_port);
    
    if (retval != 0) {
        fprintf(stderr, "Unable to bind zmq socket on host %s port %s\n", argv[1], argv[2]);
        exit(2);
    }
    
    srandom(42);
    while(1) {
        current_time = time(NULL);
        lucky_number = rand();
        ctime_r(&current_time, time_buf);
        time_buf[24] = '\0';
        snprintf(message_buf, 36, "%s %ld", time_buf, lucky_number % 1000000L);
        nbytes = zmq_send(publisher, message_buf, 36, 0);
        if (nbytes != 36) {
            fprintf(stderr, "ERROR: Unable to send 36 bytes to host %s port %s\n", argv[1], argv[2]);
        }
    }
    
    zmq_close(publisher);
    zmq_ctx_destroy(ctx);
    return 0;
}