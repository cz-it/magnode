//
//  main.m
//  test_magnode
//
//  Created by apollo on 16/1/12.
//  Copyright © 2016年 proj-m. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "magnode.h"

int main(int argc, const char * argv[]) {
    
    mn_node *node = mn_new();
    mn_init(node);
    mn_connect(node, "tcp://127.0.0.1:8082", 50000);
    
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
    }
    return 0;
}
