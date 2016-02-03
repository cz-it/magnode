 //
//  magnode_inner.c
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#include "magnode_inner.h"
#include "magnode.h"

int mn_recv_framehead(mn_node *node, uint32_t timeout)
{
    int rst = 0;
    if (NULL == node ) {
        return MN_ENULLNODE;
    }
    
    if (node->recvbuf.length >= sizeof(mn_frame_head)) {
        return 0;
    }
    size_t len =sizeof(mn_frame_head) - node->recvbuf.length;
    rst = mn_net_recv(&node->socket, node->recvbuf.data, &len, timeout);
    if (rst<0) {
        LOG_E("mn_net_recv error!");
        node->recvbuf.length +=len;
        return rst;
    }
    node->recvbuf.length +=len;
    return 0;
}

int mn_recv_message(mn_node *node,int msglen, uint32_t timeout)
{
    int rst = 0;
    if (NULL == node ) {
        return MN_ENULLNODE;
    }
    
    if (node->recvbuf.length >= sizeof(mn_frame_head) + msglen) {
        return 0;
    }
    int unnecessary =  node->recvbuf.length-sizeof(mn_frame_head);
    if (unnecessary <0) {
        return -1;
    }
    size_t len =msglen - unnecessary;
    rst = mn_net_recv(&node->socket, &node->recvbuf.data, &len, timeout);
    if (rst<0) {
        LOG_E("mn_net_recv error!");
        node->recvbuf.length +=len;
        return rst;
    }
    node->recvbuf.length +=len;
    
    return 0;
}

int mn_clear_legacy_sendbuf(mn_node *node)
{
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    
    if ( 0 ==  node->sendbuf.length ) {
        return 0;
    }
    size_t ts = node->sendbuf.length;
    int rst = mn_net_send(&node->socket, node->sendbuf.data, &ts, 0);
    if (ts == node->sendbuf.length) {
        node->sendbuf.length = 0;
    } else {
        mn_buffer_align(&node->sendbuf,(int) ts);
    }
    if (rst) {
        return rst;
    }

    return 0;
}

int mn_unpack_legacy_recvbuf(mn_node *node)
{
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    
    if ( 0 ==  node->recvbuf.length ) {
        return 0;
    }
    
    return 0;
}

int mn_send_packbuf(mn_node *node)
{
    int rst = 0;
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    
    if ((node->sendbuf.cap - node->sendbuf.length)<node->packbuf.length) {
        return MN_EPACKLEN;
    }
    rst = mn_buffer_append_buf(&node->sendbuf, &node->packbuf);
    if (rst <0) {
        return rst;
    }
    rst = mn_clear_legacy_sendbuf(node);
    if (rst < 0) {
        return rst;
    }
    return 0;
}

uint32_t mn_cal_remain_time(struct timeval begintime, uint32_t timeout)
{
    uint32_t remain = 0;
    struct timeval now;
    gettimeofday(&now, NULL);
    long elapse = timeval_min_usec(&now, &begintime);
    remain = timeout - (uint32_t)elapse;
    remain = remain>0 ? remain : 0;
    return remain;
}

int mn_send_syn(mn_node *node, uint32_t timeout)
{
    int rst = 0;
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    
    rst = mn_clear_legacy_sendbuf(node);
    if (rst) {
        LOG_E("Clear send buffer's legacy error");
        return rst;
    }
    
    mn_syn syn;
    rst = mn_init_syn(&syn, MN_PB_BIN, MN_CHANNEL_NONE, MN_CRYPTO_NONE);
    if (rst <0) {
        LOG_E("init syn error with %d", rst);
        return rst;
    }
    
    mn_buffer_reset(&node->packbuf, MN_MAX_PROTO_SIZE);
    rst = mn_pack_syn(&syn, &node->packbuf);
    if (rst < 0 ) {
        LOG_E("pack syn error ");
        return -1;
    }
    node->packbuf.length += rst;
    rst = mn_send_packbuf(node);
    if (rst < 0) {
        LOG_E("send syn error with %d", rst);
        return rst;
    }
    return 0;
}



int mn_recv_ack(mn_node *node, mn_ack *ack, uint32_t timeout)
{
    int rst =0;
    uint32_t rt = timeout;
    
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    
    struct timeval btime;
    gettimeofday(&btime, NULL);
    if ( node->recvbuf.length < sizeof(mn_frame_head)) {
        rst = mn_recv_framehead(node, timeout);
        if (rst < 0) {
            return rst;
        }
    }
    mn_frame_head frame_head;
    rst = mn_unpack_frame_head(&frame_head, &node->recvbuf);
    if (rst <0) {
        LOG_E("upack frame head error!");
        return rst;
    }
    rt = mn_cal_remain_time(btime, timeout);
    rst = mn_recv_message(node, frame_head.length, rt);
    if (rst < 0) {
        LOG_E("Recv Message Error !");
        return rst;
    }
    
    rst = mn_unpack_ack(ack, &node->recvbuf);
    if (rst < 0) {
        LOG_E("Unpack ACK error !");
        return rst;
    }
    
    return 0;
}

int mn_send_session_req(mn_node *node, uint32_t timeout)
{
    int rst = 0;
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    
    rst = mn_clear_legacy_sendbuf(node);
    if (rst) {
        LOG_E("Clear send buffer's legacy error");
        return rst;
    }
    
    mn_session_req sssreq;
    rst = mn_init_sssreq(&sssreq);
    if (rst <0) {
        LOG_E("init session request error with %d", rst);
        return rst;
    }
    
    mn_buffer_reset(&node->packbuf, MN_MAX_PROTO_SIZE);
    rst = mn_pack_sssreq(&sssreq, &node->packbuf);
    if (rst < 0 ) {
        LOG_E("pack syn error ");
        return -1;
    }
    node->packbuf.length += rst;
    rst = mn_send_packbuf(node);
    if (rst < 0) {
        LOG_E("send syn error with %d", rst);
        return rst;
    }
    return 0;
}

int mn_recv_session_rsp(mn_node *node, mn_session_rsp *sssrsp, uint32_t timeout)
{

    int rst =0;
    uint32_t rt = timeout;
    
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    
    struct timeval btime;
    gettimeofday(&btime, NULL);
    if ( node->recvbuf.length < sizeof(mn_frame_head)) {
        rst = mn_recv_framehead(node, timeout);
        if (rst < 0) {
            return rst;
        }
    }
    mn_frame_head frame_head;
    rst = mn_unpack_frame_head(&frame_head, &node->recvbuf);
    if (rst <0) {
        LOG_E("upack frame head error!");
        return rst;
    }
    rt = mn_cal_remain_time(btime, timeout);
    rst = mn_recv_message(node, frame_head.length, rt);
    if (rst < 0) {
        LOG_E("Recv Message Error !");
        return rst;
    }
    
    rst = mn_unpack_sssrsp(sssrsp, &node->recvbuf);
    if (rst < 0) {
        LOG_E("Unpack Session Rsp error !");
        return rst;
    }
    return 0;
}

int mn_send_auth_req(mn_node *node, uint32_t timeout)
{
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    return 0;
}

int mn_recv_auth_rsp(mn_node *node, uint32_t timeout)
{
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    return 0;
}

int mn_recv_confirm(mn_node *node, uint32_t timeout)
{
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    return 0;
}

int mn_connect_transaction(mn_node *node, uint32_t timeout)
{
    int rst = 0;
    uint32_t rt = timeout;
    
    if (NULL == node) {
        return MN_ENULLNODE;
    }
    
    struct timeval btime;
    gettimeofday(&btime, NULL);
    // 1. send syn
    rst = mn_send_syn(node, rt);
    if (rst <0 ) {
        LOG_E("send syn error");
        if (MN_ETIMEOUT == rst ) {
            return rst;
        } else {
            return MN_ESYN;
        }
    }
    
    // 2. recv ack
    rt = mn_cal_remain_time(btime, timeout);
    mn_ack ack;
    rst = mn_recv_ack(node, &ack, rt);
    if (rst <0 ) {
        LOG_E("send syn error");
        if (MN_ETIMEOUT == rst ) {
            return rst;
        } else {
            return MN_EACK;
        }
    }
    
    // send session req
    rt = mn_cal_remain_time(btime, timeout);
    rst = mn_send_session_req(node, rt);
    if (rst <0 ) {
        LOG_E("send session request error");
        if (MN_ETIMEOUT == rst ) {
            return rst;
        } else {
            return MN_ESSSREQ;
        }
    }
    
    // recv session rsp
    rt = mn_cal_remain_time(btime, timeout);
    mn_session_rsp sssrsp;
    rst = mn_recv_session_rsp(node, &sssrsp, rt);
    if (rst <0 ) {
        LOG_E("recv session response error");
        if (MN_ETIMEOUT == rst ) {
            return rst;
        } else {
            return MN_ESSSRSP;
        }
    }
    
    // send auth
    rt = mn_cal_remain_time(btime, timeout);
    rst = mn_send_auth_req(node, rt);
    if (rst <0 ) {
        LOG_E("send auth request error");
        if (MN_ETIMEOUT == rst ) {
            return rst;
        } else {
            return MN_EAUTHREQ;
        }
    }
    
    // recv auth
    rt = mn_cal_remain_time(btime, timeout);
    rst = mn_recv_auth_rsp(node, rt);
    if (rst <0 ) {
        LOG_E("recv auth response error");
        if (MN_ETIMEOUT == rst ) {
            return rst;
        } else {
            return MN_EAUTHRSP;
        }
    }
    
    // recv confirm
    rt = mn_cal_remain_time(btime, timeout);
    rst = mn_recv_confirm(node, rt);
    if (rst <0 ) {
        LOG_E("recv confirm error");
        if (MN_ETIMEOUT == rst ) {
            return rst;
        } else {
            return MN_ECONFIRM;
        }
    }
    
    return 0;
}

