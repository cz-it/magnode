//
//  message.h
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#ifndef message_h
#define message_h

#include <stdio.h>

#include "frame_head.h"
#include "syn_ack.h"
#include "session.h"
#include "confirm.h"

typedef union mn_message_body_t {
    mn_syn syn;
    mn_ack ack;
    mn_session_req sssnreq;
    mn_session_rsp sssnrsp;
} mn_message_body;

#pragma pack(1)
typedef  struct mn_message_t
{
    mn_frame_head head;
    mn_message_body body;
} mn_message;

int mn_init_syn_msg(mn_message *msg, uint16_t protobuf, uint16_t channel, uint16_t crypto);

int mn_init_ack_msg(mn_message *msg, uint16_t channel, uint16_t crypto);

int mn_init_sssreq_msg(mn_message *msg);

int mn_init_sssrsp_msg(mn_message *msg, uint32_t agent_id);

int mn_init_confirm_msg(mn_message *msg, int32_t errno);

int mn_pack_msg(mn_message *msg, mn_buffer *buf);

int mn_unpack_msg(mn_message *msg, mn_buffer *buf);

#pragma pack()

#endif /* message_h */
