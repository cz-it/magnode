/*****************************************************************************\
** magnode:disconn.c
** Created by CZ(cz.devnet@gmail.com) on 7/22/16
**
**  Copyright © 2016 proj-m. All rights reserved.
\*****************************************************************************/

#include "disconn.h"
#include "log.h"
#include "proto.h"

int mn_init_disconn(mn_disconn *disconn)
{
    int rst = 0;
    if (NULL == disconn) {
        return MN_EARG;
    }
    return rst;
}

int mn_pack_disconn(mn_disconn *disconn, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == disconn) {
        return MN_EARG;
    }
    
    if ((buf->cap - buf->length) < sizeof(mn_frame_head)) {
        return MN_EPACKLEN;
    }
    mn_frame_head frame_head;
    mn_init_frame_head(&frame_head, MN_CMD_DISCONN, 0);
    rst = mn_pack_frame_head(&frame_head, buf);
    if (rst < 0) {
        return rst;
    }
    
    return rst;
}

int mn_unpack_disconn(mn_disconn *disconn, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == disconn) {
        return MN_EARG;
    }
    return rst;

}
