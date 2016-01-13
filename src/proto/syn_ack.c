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

    mn_init_frame_head(&syn->frame_head, MN_CMD_SYN, sizeof(*syn) - sizeof(syn->frame_head));
    return 0;
}

int mn_pack_syn(mn_syn *syn, void *buf, int len)
{
    int rst = 0;
    if (NULL == syn || NULL == buf) {
        return MN_EARG;
    }
    
    if (len < sizeof(*syn)) {
        return MN_EPACKLEN;
    }
    
    rst = mn_pack_frame_head(&syn->frame_head, buf, len);
    if (rst < 0) {
        return rst;
    }
    
    memcpy(buf+rst, syn, sizeof(*syn));
    rst +=sizeof(*syn);
    return rst;
}

int mn_unpack_syn(mn_syn *syn, const void *buf, int len)
{
    return 0;
}

int mn_pack_ack(mn_ack *ack, void *buf, int len)
{
    return 0;
}

int mn_unpack_ack(mn_ack *ack, const void *buf, int len)
{
    if (NULL == ack || NULL == buf) {
        return MN_EARG;
    }
    
    if (len < sizeof(uint16_t)) {
        return MN_EPACKLEN;
    }
    
    ack->channel = *(uint16_t *)buf;
    ack->crypto  = *((uint16_t *)buf +1);
    return 0;
}