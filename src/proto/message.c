//
//  message.c
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#include "message.h"

int mn_init_syn_msg(mn_message *msg, uint16_t protobuf, uint16_t channel, uint16_t crypto)
{
    return 0;
}

int mn_init_ack_msg(mn_message *msg, uint16_t channel, uint16_t crypto)
{
    return 0;
}

int mn_init_sssreq_msg(mn_message *msg)
{
    return 0;
}

int mn_init_sssrsp_msg(mn_message *msg, uint32_t agent_id)
{
    return 0;
}

int mn_init_confirm_msg(mn_message *msg, int32_t errno)
{
    return 0;
}

int mn_pack_msg(mn_message *msg, mn_buffer *buf)
{
    return 0;
}

int mn_unpack_msg(mn_message *msg, mn_buffer *buf)
{
    return 0;
}
