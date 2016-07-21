/*******************************************************************************\
** magnode:disconn.h
** Created by CZ(cz.devnet@gmail.com) on 7/22/16
**
**  Copyright © 2016 proj-m. All rights reserved.
\*******************************************************************************/


#ifndef magnode_disconn_h_
#define magnode_disconn_h_

#include "frame_head.h"
#pragma pack(1)
typedef  struct mn_disconn_t
{

} mn_disconn;
#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif
    int mn_init_disconn(mn_disconn *disconn);
    
    int mn_pack_disconn(mn_disconn *disconn, mn_buffer *buf);
    
    int mn_unpack_disconn(mn_disconn *disconn, mn_buffer *buf);
    
#ifdef __cplusplus
}
#endif


#endif /* magnode_disconn_h_ */
