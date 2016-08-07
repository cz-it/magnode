//
//  main.c
//  echo
//
//  Created by CZ on 7/25/16.
//  Copyright © 2016 projm. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "magnode.h"

int main(int argc, const char * argv[]) {
    mn_node *node = mn_new();
    mn_init(node);
    mn_connect(node, "tcp://127.0.0.1:8083", 50000);
    char *hello= "hello";
    mn_send(node, hello, strlen(hello), 50000);
    char recvbuf[1024] = {0};
    size_t len = 1024;
    mn_recv(node, recvbuf, &len, 5000);
    printf("len is %zu , buf is %s \n", len, recvbuf);
    
    mn_close(node);
    printf("Hello, World!\n");
    return 0;
}
