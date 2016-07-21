//
//  confirm.h
//  magnode
//
//  Created by apollo on 15/12/29.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#ifndef confirm_h
#define confirm_h

#include "frame_head.h"

#pragma pack(1)
typedef struct mn_confirm_t
{
    int32_t errno;
} mn_confirm;
#pragma pack()

int mn_init_confirm(mn_confirm *confirm, int32_t errno);

int mn_pack_confirm(mn_confirm *confirm, mn_buffer *buf);

int mn_unpack_confirm(mn_confirm *confirm, mn_buffer *buf);

#endif /* confirm_h */
