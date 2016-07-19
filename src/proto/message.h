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

#pragma pack()

#endif /* message_h */
