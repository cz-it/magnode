/*******************************************************************************\
** magnode:nodemsg.h
** Created by CZ(cz.devnet@gmail.com) on 7/21/16
**
**  Copyright © 2016 proj-m. All rights reserved.
\*******************************************************************************/


#ifndef magnode_nodemsg_h_
#define magnode_nodemsg_h_

#include "frame_head.h"
#pragma pack(1)
typedef  struct mn_nodemsg_t
{
    void *data;
    size_t len;
} mn_nodemsg;
#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif
    int mn_init_nodemsg(mn_nodemsg *nodemsg, void *data, size_t len);
    
    int mn_pack_nodemsg(mn_nodemsg *nodemsg, mn_buffer *buf);
    
    int mn_unpack_nodemsg(mn_nodemsg *nodemsg, mn_buffer *buf);
    
#ifdef __cplusplus
}
#endif

#endif /* magnode_nodemsg_h_ */
