//
//  buffer.h
//  magnode
//
//  Created by apollo on 15/12/30.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#ifndef buffer_h
#define buffer_h

#include <stdint.h>

typedef  struct mn_buffer_t {
    void *data;
    int length;
    int index;
    int cap;
} mn_buffer;

#ifdef __cplusplus
extern "C" {
#endif

    int mn_buffer_init(mn_buffer *buffer, int size);

    int mn_buffer_reset(mn_buffer *buffer, int size);

    int mn_buffer_deinit(mn_buffer *buffer);

    int mn_buffer_align(mn_buffer *buffer, int index);
    
    int mn_buffer_append(mn_buffer *dest, const void *src, const int len);
    
    int mn_buffer_append_buf(mn_buffer *dest, mn_buffer *src);
    
    int mn_buffer_uint16(mn_buffer *buffer, uint16_t *dest);
    
    int mn_buffer_uint32(mn_buffer *buffer, uint32_t *dest);
    
    int mn_buffer_int32(mn_buffer *buffer, int *dest);
    
    int mn_buffer_void(mn_buffer *buffer, void *dest, int len);
    
#ifdef __cplusplus
}
#endif

#endif /* buffer_h */
