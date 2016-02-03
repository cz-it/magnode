//
//  session.c
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#include "session.h"
#include "proto.h"

int mn_init_sssreq(mn_session_req *sssreq)
{
    int rst = 0;
    if (NULL == sssreq ) {
        return MN_EARG;
    }
    return rst;
}

int mn_pack_sssreq(mn_session_req *sssreq, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == sssreq || NULL == buf) {
        return MN_EARG;
    }
    
    if ((buf->cap - buf->length) < sizeof(*sssreq)) {
        return MN_EPACKLEN;
    }
    mn_frame_head frame_head;
    mn_init_frame_head(&frame_head, MN_CMD_SSSREQ, sizeof(*sssreq));
    rst = mn_pack_frame_head(&frame_head, buf);
    if (rst < 0) {
        return rst;
    }
    return rst;
}

int mn_unpack_sssreq(mn_session_req *sssreq, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == sssreq || NULL == buf) {
        return MN_EARG;
    }
    return rst;
}

int mn_pack_sssrsp(mn_session_rsp *sssrsp, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == sssrsp || NULL == buf) {
        return MN_EARG;
    }
    return rst;
}

int mn_unpack_sssrsp(mn_session_rsp *sssrsp, mn_buffer *buf)
{
    int rst = 0;
    if (NULL == sssrsp || NULL == buf) {
        return MN_EARG;
    }
    
    rst = mn_buffer_uint32(buf, &sssrsp->agent_id);
    return rst;
}