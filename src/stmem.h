
/*  $Id: stmem.h,v 1.3 1996/03/28 03:02:11 wessels Exp $ */

#ifndef STMEM_H
#define STMEM_H

typedef struct mem_n *mem_node;
typedef struct mem_n {
    char *data;
    int len;
    mem_node next;
} Mem_Node;

typedef struct mem_hdr {
    mem_node head;
    mem_node tail;
    int origin_offset;
    void (*mem_free) _PARAMS((mem_ptr mem));
    void (*mem_free_data) _PARAMS((mem_ptr mem));
    int (*mem_free_data_upto) _PARAMS((mem_ptr mem, int target_offset));
    int (*mem_append) _PARAMS((mem_ptr mem, char *data, int len));
    int (*mem_copy) _PARAMS((mem_ptr mem, int offset, char *buf, int size));
    int (*mem_grep) _PARAMS((mem_ptr mem, char *string, int nbytes));
} Mem_Hdr;

/* To reduce memory fragmentation, we now store the memory version of an
 * object in fixed size blocks of size PAGE_SIZE and instead of calling 
 * malloc and free, we manage our own fixed block free list.   
 */

#define SM_PAGE_SIZE 4096
#define DISK_PAGE_SIZE  8192

/* Memory allocator routines for fixed size blocks */
typedef struct _stmem_stats {
    int total_pages_allocated;
    int page_size;
    int n_pages_free;
    int n_pages_in_use;
    Stack free_page_stack;
} stmem_stats;

stmem_stats sm_stats;
stmem_stats disk_stats;

extern char *get_free_4k_page _PARAMS((void));
extern char *get_free_8k_page _PARAMS((void));
extern mem_ptr memInit _PARAMS((void));
extern void put_free_4k_page _PARAMS((char *));
extern void put_free_8k_page _PARAMS((char *));
extern void stmemInit _PARAMS((void));

#endif
