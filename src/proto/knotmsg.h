/*******************************************************************************\
** magnode:knotmsg.h
** Created by CZ(cz.devnet@gmail.com) on 7/21/16
**
**  Copyright © 2016 proj-m. All rights reserved.
\*******************************************************************************/


#ifndef magnode_knotmsg_h_
#define magnode_knotmsg_h_

#include "frame_head.h"
#pragma pack(1)
typedef  struct mn_knotmsg_t
{
    void *data;
    size_t len;
} mn_knotmsg;
#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif
    int mn_init_knotmsg(mn_knotmsg *knotmsg, void *data, size_t len);
    
    int mn_pack_knotmsg(mn_knotmsg *knotmsg, mn_buffer *buf);
    
    int mn_unpack_knotmsg(mn_knotmsg *knotmsg, mn_buffer *buf);
    
#ifdef __cplusplus
}
#endif

#endif /* magnode_knotmsg_h_ */
