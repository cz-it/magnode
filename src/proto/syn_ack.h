//
//  syn_ack.h
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#ifndef syn_ack_h
#define syn_ack_h

#include "frame_head.h"
#pragma pack(1)
typedef  struct mn_syn_t
{
    uint16_t protobuf;
    uint16_t channel;
    uint16_t crypto;
} mn_syn;
#pragma pack()

#pragma pack(1)
typedef struct mn_ack_t
{
    uint16_t channel;
    uint16_t crypto;
} mn_ack;
#pragma pack()


#ifdef __cplusplus
extern "C" {
#endif
    int mn_init_syn(mn_syn *syn, uint16_t protobuf, uint16_t channel, uint16_t crypto);
    
    int mn_init_ack(mn_ack *ack, uint16_t channel, uint16_t crypto);
    
    int mn_pack_syn(mn_syn *syn, mn_buffer *buf);
    
    int mn_unpack_syn(mn_syn *syn, mn_buffer *buf);
    
    int mn_pack_ack(mn_ack *ack, mn_buffer *buf);
    
    int mn_unpack_ack(mn_ack *ack, mn_buffer *buf);
    
#ifdef __cplusplus
}
#endif
#endif /* syn_ack_h */
