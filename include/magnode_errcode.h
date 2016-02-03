//
//  magnode_errcode.h
//  magnode
//
//  Created by CZ on 7/23/15.
//  Copyright (c) 2015 proj-m. All rights reserved.
//

#ifndef magnode_magnode_errcode_h
#define magnode_magnode_errcode_h

#ifdef __cplusplus
extern  "C" {
#endif
    
#define MN_ERRNO_BASE 10000
    
    enum mn_errno {
        MN_EARG         = -(MN_ERRNO_BASE + 1),
        MN_ETIMEOUT     = -(MN_ERRNO_BASE + 2),
        MN_ECONN        = -(MN_ERRNO_BASE + 3),
        MN_EBODYLEN     = -(MN_ERRNO_BASE + 4),
        MN_EHEAD        = -(MN_ERRNO_BASE + 5),
        MN_ECMD         = -(MN_ERRNO_BASE + 6),
        MN_EALLOC       = -(MN_ERRNO_BASE + 7),
        MN_ESEND        = -(MN_ERRNO_BASE + 8),
        MN_ERECV        = -(MN_ERRNO_BASE + 9),
        MN_EPARSE       = -(MN_ERRNO_BASE + 10),
        MN_EUNPARSE     = -(MN_ERRNO_BASE + 11),
        MN_ESYN         = -(MN_ERRNO_BASE + 12),
        MN_ENULLNODE    = -(MN_ERRNO_BASE + 13),
        MN_EACK         = -(MN_ERRNO_BASE + 14),
        MN_ENEWBUF      = -(MN_ERRNO_BASE + 15),
        MN_EPACKLEN     = -(MN_ERRNO_BASE + 16),
        MN_EUNKNOWNACK  = -(MN_ERRNO_BASE + 17),
        MN_EBUFLEN      = -(MN_ERRNO_BASE + 18),
        MN_ESSSREQ      = -(MN_ERRNO_BASE + 19),
        MN_ESSSRSP      = -(MN_ERRNO_BASE + 20),
        MN_EAUTHREQ     = -(MN_ERRNO_BASE + 21),
        MN_EAUTHRSP     = -(MN_ERRNO_BASE + 22),
        MN_ECONFIRM     = -(MN_ERRNO_BASE + 23),
    };
    
#ifdef __cplusplus
}
#endif

#endif
