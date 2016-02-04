//
//  buffer.c
//  magnode
//
//  Created by apollo on 15/12/30.
//  Copyright © 2015年 proj-m. All rights reserved.
//

#include "buffer.h"
#include "magnode_errcode.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int mn_buffer_init(mn_buffer *buffer, int size)
{
    if (NULL == buffer) {
        return MN_EARG;
    }
    
    buffer->data = (void *) malloc(size);
    if (NULL == buffer->data) {
        mn_buffer_deinit(buffer);
        return MN_ENEWBUF;
    }
    memset(buffer->data, 0, size);
    buffer->cap = size;
    buffer->length = 0;
    buffer->index = 0;
    return 0;
}

int mn_buffer_append_buf(mn_buffer *dest, mn_buffer *src)
{
    if (NULL == dest || NULL == src) {
        return MN_EARG;
    }
    
    if ((dest->cap - dest->length) < src->length) {
        return MN_EBUFLEN;
    }
    memcpy(dest->data+dest->length, src->data, src->length);
    dest->length += src->length;
    return 0;
}

int mn_buffer_reset(mn_buffer *buffer, int size)
{
    if (NULL == buffer) {
        return MN_EARG;
    }
    if (size <= buffer->cap) {
        memset(buffer->data, 0, buffer->cap);
        buffer->cap = size;
        buffer->length = 0;
        return 0;
    }
    
    buffer->data = (void *) realloc(buffer->data, size);
    if (NULL == buffer->data) {
        mn_buffer_deinit(buffer);
        return MN_ENEWBUF;
    }
    memset(buffer->data, 0, size);
    buffer->cap = size;
    buffer->length = 0;
    
    return 0;
}

int mn_buffer_deinit(mn_buffer *buffer)
{
    if (NULL == buffer) {
        return MN_EARG;
    }
    if (buffer->data) {
        free(buffer->data);
    }
    
    buffer->cap  = 0;
    buffer->length    = 0;
    
    return 0;
}

int mn_buffer_align(mn_buffer *buffer, int index)
{
    if (NULL == buffer) {
        return MN_EARG;
    }
    if (0 == index) {
        return 0;
    }

    if (index > buffer->length) {
        return MN_EBUFLEN;
    }
    
    memmove(buffer->data, buffer->data+index, buffer->length-index);
    buffer->length = buffer->length - index;
    return 0;
}

int mn_buffer_uint16(mn_buffer *buffer, uint16_t *dest)
{
    if (NULL == buffer || NULL==dest) {
        return MN_EARG;
    }
    
    if (buffer->length < sizeof(*dest)) {
        return MN_EBUFLEN;
    }
    
    *dest = * ((uint16_t *) buffer->data);
    mn_buffer_align(buffer, sizeof(*dest));
    return 0;
}

int mn_buffer_uint32(mn_buffer *buffer, uint32_t *dest)
{
    if (NULL == buffer || NULL==dest) {
        return MN_EARG;
    }
    
    if (buffer->length < sizeof(*dest)) {
        return MN_EBUFLEN;
    }
    
    *dest = * ((uint32_t *) buffer->data);
    mn_buffer_align(buffer, sizeof(*dest));
    return 0;
}

int mn_buffer_void(mn_buffer *buffer, void *dest, int len)
{
    if (NULL == buffer || NULL==dest) {
        return MN_EARG;
    }
    
    if (buffer->length < len) {
        return MN_EBUFLEN;
    }
    
    memcpy(dest, buffer->data, len);
    mn_buffer_align(buffer, len);
    return 0;
}

int mn_buffer_append(mn_buffer *dest, const void *src, const int len)
{
    if (NULL == dest || NULL==src) {
        return MN_EARG;
    }
    
    if ((dest->cap - dest->length) < len) {
        return MN_EBUFLEN;
    }
    
    memcpy(dest->data+dest->length, src, len);
    dest->length += len;    
    return 0;
}