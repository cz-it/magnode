//
//  syn_ack.c
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#include "syn_ack.h"
#include "magnode.h"
#include "log.h"
#include "proto.h"

int mn_init_syn(mn_syn *syn, uint16_t protobuf, uint16_t channel, uint16_t crypto)
{
    if (NULL == syn) {
        return MN_EARG;
    }
    syn->crypto = crypto;
    syn->channel = channel;
    syn->protobuf = protobuf;

    return 0;
}

int mn_init_ack(mn_ack *ack, uint16_t channel, uint16_t crypto)
{
    if (NULL == ack) {
        return MN_EARG;
    }
    ack->channel = channel;
    ack->crypto = crypto;
    return 0;
}

int mn_pack_syn(mn_syn *syn, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == syn || NULL == buf) {
        return MN_EARG;
    }
    
    if ((buf->cap - buf->length) < sizeof(*syn)) {
        return MN_EPACKLEN;
    }
    mn_frame_head frame_head;
    mn_init_frame_head(&frame_head, MN_CMD_SYN, sizeof(*syn));
    rst = mn_pack_frame_head(&frame_head, buf);
    if (rst < 0) {
        return rst;
    }

    rst = mn_buffer_append(buf, &syn->protobuf, sizeof(syn->protobuf));
    if (rst < 0) {
        return rst;
    }
    rst = mn_buffer_append(buf, &syn->channel, sizeof(syn->channel));
    if (rst < 0) {
        return rst;
    }
    rst = mn_buffer_append(buf, &syn->crypto, sizeof(syn->crypto));
    if (rst < 0) {
        return rst;
    }

    return rst;
}

int mn_unpack_syn(mn_syn *syn, mn_buffer *buf)
{
    return 0;
}

int mn_pack_ack(mn_ack *ack, mn_buffer *buf)
{
    return 0;
}

int mn_unpack_ack(mn_ack *ack, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == ack || NULL == buf) {
        return MN_EARG;
    }
    
    if (buf->length < sizeof(uint16_t)) {
        return MN_EPACKLEN;
    }
    
    rst = mn_buffer_uint16(buf, &ack->channel);
    if (rst < 0) {
        return rst;
    }
    rst = mn_buffer_uint16(buf, &ack->crypto);
    if (rst < 0) {
        return rst;
    }
    return rst;
}