//
//  session.h
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#ifndef session_h
#define session_h

#include "frame_head.h"
#pragma pack(1)
typedef  struct mn_session_req_t
{

} mn_session_req;
#pragma pack()

#pragma pack(1)
typedef struct mn_session_rsp_t
{
    uint32_t agent_id;
} mn_session_rsp;
#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif
    int mn_init_sssreq(mn_session_req *sssreq);
    
    int mn_init_sssrsp(mn_session_rsp *sssrsp, uint32_t agent_id);
    
    int mn_pack_sssreq(mn_session_req *sssreq, mn_buffer *buf);
    
    int mn_unpack_sssreq(mn_session_req *sssreq, mn_buffer *buf);
    
    int mn_pack_sssrsp(mn_session_rsp *sssrsp, mn_buffer *buf);
    
    int mn_unpack_sssrsp(mn_session_rsp *sssrsp, mn_buffer *buf);
    
#ifdef __cplusplus
}
#endif

#endif /* session_h */
