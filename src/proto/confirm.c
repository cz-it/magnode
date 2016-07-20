//
//  confirm.c
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#include "confirm.h"

int mn_init_confirm(mn_confirm *confirm, int32_t errno)
{
    if (NULL == confirm) {
        return MN_EARG;
    }
    confirm->errno = errno;
    return 0;
}

int mn_pack_confirm(mn_confirm *confirm, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == confirm || NULL == buf) {
        return MN_EARG;
    }
    return 0;
}

int mn_unpack_confirm(mn_confirm *confirm, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == confirm || NULL == buf) {
        return MN_EARG;
    }
    
    if (buf->length < sizeof(int32_t)) {
        return MN_EPACKLEN;
    }
    
    rst = mn_buffer_int32(buf, &confirm->errno);
    if (rst < 0) {
        return rst;
    }
    return rst;
}