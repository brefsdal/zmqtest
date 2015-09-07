//
//  publisher.c
//  ZeromqTest
//
//  Created by Brian Refsdal on 9/6/15.
//  Copyright (c) 2015 Brian Refsdal. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "zmq.h"

#define TIMESIZE (26)
#define MSGSIZE (32)

int main(int argc, const char * argv[]) {

    char time_buf[TIMESIZE], message[MSGSIZE];
    void *ctx = NULL, *publisher = NULL;
    int retval = 0, nbytes = 0, lucky_number = 0;
    time_t current_time;
    
    ctx = zmq_ctx_new();
    
    publisher = zmq_socket(ctx, ZMQ_PUB);
    
    retval = zmq_bind(publisher, "tcp://*:9000");    
    if (retval != 0) {
        fprintf(stderr, "Unable to bind zmq socket on port 9000\n");
        exit(1);
    }
    
    srandom(42);
    while(1) {
        current_time = time(NULL);
        ctime_r(&current_time, time_buf);

        // Remove the newline added by ctime_r
        time_buf[24] = '\0';
        
        lucky_number = (int) (rand() % 1000000L);
        
        sprintf(message, "%s %06d", time_buf, lucky_number);
        
        nbytes = zmq_send(publisher, message, MSGSIZE, 0);
        if (nbytes != MSGSIZE) {
            fprintf(stderr, "ERROR: Unable to send bytes to subscriber\n");
        }
        
        sleep(1);
    }
    
    zmq_close(publisher);
    zmq_ctx_destroy(ctx);
    return 0;
}