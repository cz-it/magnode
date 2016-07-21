/*****************************************************************************\
** magnode:knotmsg.c
** Created by CZ(cz.devnet@gmail.com) on 7/21/16
**
**  Copyright © 2016 proj-m. All rights reserved.
\*****************************************************************************/

#include "knotmsg.h"
#include "log.h"
#include "proto.h"


int mn_init_knotmsg(mn_knotmsg *knotmsg, void *data, size_t len)
{
    int rst = 0;
    if (NULL == knotmsg || NULL == data) {
        return MN_EARG;
    }

    knotmsg->data = data;
    knotmsg->len = len;
    return rst;
}

int mn_pack_knotmsg(mn_knotmsg *knotmsg, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == knotmsg || NULL == buf) {
        return MN_EARG;
    }
    return rst;
}

int mn_unpack_knotmsg(mn_knotmsg *knotmsg, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == knotmsg || NULL == buf) {
        return MN_EARG;
    }
    
    if (buf->length > knotmsg->len) {
        return MN_EBUFLEN;
    }
    knotmsg->len = buf->length;
    rst = mn_buffer_void(buf, knotmsg->data, buf->length);
    if (rst < 0) {
        return rst;
    }

    return rst;
}