//
//  magnode.c
//  magnode
//
//  Created by apollo on 15/9/23.
//  Copyright © 2015年 proj-m. All rights reserved.
//


#include "magnode_inner.h"

#if defined MN_APPLE  || defined MN_ANDROID
#include <sys/time.h>
#endif
#include <stdlib.h>
#include <string.h>



mn_node *mn_new()
{
    // just like golang's new . new with 0 memory
    void *buf =(void *) malloc(sizeof(mn_node));
    memset(buf,0,sizeof(mn_node));
    mn_node *node = (mn_node *)buf;
    return node;
}

int mn_init(mn_node *node)
{
    int rst = 0;
    if (NULL == node){
        LOG_E("mn_init: node is NULL");
        return MN_EARG;
    }
    LOG_I("mn_init(node %p)", node);
    
    node->agent_id = 0;
    
    rst = mn_buffer_init(&node->sendbuf, MN_MAX_PROTO_SIZE);
    if (rst ) {
        LOG_E("Init send buffer error");
        mn_deinit(node);
        return rst;
    }
    
    rst = mn_buffer_init(&node->recvbuf, MN_MAX_PROTO_SIZE *2 );
    if (rst ) {
        LOG_E("Init recv buffer error");
        mn_deinit(node);
        return rst;
    }
    
    rst = mn_buffer_init(&node->packbuf, MN_MAX_PROTO_SIZE );
    if (rst ) {
        LOG_E("Init pack buffer error");
        mn_deinit(node);
        return rst;
    }
    
    memset(&node->socket, 0, sizeof(node->socket));
    return 0;
}

int mn_deinit(mn_node *node)
{
    if (NULL == node){
        LOG_E("mn_deinit: node is NULL");
        return MN_EARG;
    }
    LOG_I("mn_deinit(node %p)", node);
    
    mn_buffer_deinit(&node->sendbuf);
    mn_buffer_deinit(&node->recvbuf);
    mn_buffer_deinit(&node->packbuf);
    node->agent_id = 0;
    return 0;
}

int mn_connect(mn_node *node,const char *url, uint32_t timeout)
{
    int rst;
    if (NULL == node || NULL==url ){
        LOG_E("mn_connect: node is NULL or url is NULL");
        return MN_EARG;
    }
    LOG_I("mn_connect(node %p,url %s, timeout %llu)", node, url, timeout);
    
    struct timeval btime;
    gettimeofday(&btime, NULL);
    rst = mn_net_connect(&node->socket, url, timeout);
    LOG_D("net connect with %d rst", rst);
    if (rst != 0 ) {
        if (rst == MN__ETIMEOUT) {
            return MN_ETIMEOUT;
        } else {
            return MN_ECONN;
        }
        
    }
    
    uint32_t rt = mn_cal_remain_time(btime, timeout);
    if ( 0 == rt) {
        LOG_I("mn_connect timeout");
        return MN_ETIMEOUT;
    }
    rst = mn_connect_transaction(node, rt);
    if (rst < 0) {
        if (MN_ETIMEOUT ==rst ) {
            return MN_ETIMEOUT;
        } else {
            return rst;
        }
    }
    
    return 0;
}

int mn_reconnect(mn_node *node, uint32_t timeout)
{
    if (NULL == node){
        LOG_E("mn_reconnect: node is NULL");
        return MN_EARG;
    }
    LOG_I("mn_reconnect(node %p, timeout %llu)", node, timeout);
    
    return 0;
}

int mn_send(mn_node *node,const void *buf,size_t length,uint32_t timeout)
{
    int rst;
    if (NULL == node || NULL==buf ){
        LOG_E("mn_send: node is NULL or buf is NULL");
        return MN_EARG;
    }
    
    rst = mn_send_nodemsg(node, buf, length, timeout);
    LOG_D("net mn_send_msg with %d rst", rst);
    if (rst != 0 ) {
        if (rst == MN__ETIMEOUT) {
            return MN_ETIMEOUT;
        } else {
            return MN_ECONN;
        }
    }
    
    return 0;
}

int mn_recv(mn_node *node,void *buf,size_t *length,uint32_t timeout)
{
    int rst;
    if (NULL == node || NULL==buf ){
        LOG_E("mn_recv: node is NULL or buf is NULL");
        return MN_EARG;
    }
    
    struct timeval btime;
    gettimeofday(&btime, NULL);
    rst = mn_recv_knotmsg(node, buf, length, timeout);
    LOG_D("net mn_recv_msg with %d rst", rst);
    if (rst != 0 ) {
        if (rst == MN__ETIMEOUT) {
            return MN_ETIMEOUT;
        } else {
            return MN_ECONN;
        }
    }
    
    return 0;
}

int mn_close(mn_node *node)
{
    int rst;
    if (NULL == node ){
        LOG_E("mn_recv: node  is NULL");
        return MN_EARG;
    }
    
    rst = mn_send_disconn(node, 200); // 100ms is a magic number
    LOG_D("net mn_send_disconn with %d rst", rst);
    if (rst != 0 ) {
        if (rst == MN__ETIMEOUT) {
            return MN_ETIMEOUT;
        } else {
            return MN_ECONN;
        }
    }
    return 0;
}