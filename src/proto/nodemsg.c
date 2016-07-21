/*****************************************************************************\
** magnode:nodemsg.c
** Created by CZ(cz.devnet@gmail.com) on 7/21/16
**
**  Copyright © 2016 proj-m. All rights reserved.
\*****************************************************************************/

#include "nodemsg.h"
#include "log.h"
#include "proto.h"


int mn_init_nodemsg(mn_nodemsg *nodemsg, void *data, size_t len)
{
    int rst = 0;
    if (NULL == nodemsg || NULL == data) {
        return MN_EARG;
    }
    nodemsg->data = data;
    nodemsg->len = len;
    return rst;
}

int mn_pack_nodemsg(mn_nodemsg *nodemsg, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == nodemsg || NULL == buf) {
        return MN_EARG;
    }
    
    if ((buf->cap - buf->length) < nodemsg->len+sizeof(mn_frame_head)) {
        return MN_EPACKLEN;
    }
    mn_frame_head frame_head;
    mn_init_frame_head(&frame_head, MN_CMD_NODEMSG, nodemsg->len);
    rst = mn_pack_frame_head(&frame_head, buf);
    if (rst < 0) {
        return rst;
    }
    
    rst = mn_buffer_append(buf, nodemsg->data, nodemsg->len);
    if (rst < 0) {
        return rst;
    }
    
    return rst;
}

int mn_unpack_nodemsg(mn_nodemsg *nodemsg, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == nodemsg || NULL == buf) {
        return MN_EARG;
    }
    return rst;
}