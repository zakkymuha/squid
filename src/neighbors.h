
/*  $Id: neighbors.h,v 1.3 1996/03/27 18:50:24 wessels Exp $ */

#ifndef NEIGHBORS_H
#define NEIGHBORS_H

#define isNeighbor( X ) (((X).type==is_a_neighbor))
#define isParent( X )   ((X).type==is_a_parent)

/* Labels for hierachical log file */
/* put them all here for easier reference when writing a logfile analyzer */

typedef enum {
    HIER_NONE,
    HIER_DIRECT,
    HIER_NEIGHBOR_HIT,
    HIER_PARENT_HIT,
    HIER_SINGLE_PARENT,
    HIER_NO_PARENT_DIRECT,
    HIER_FIRST_PARENT_MISS,
    HIER_LOCAL_IP_DIRECT,
    HIER_DEAD_PARENT,
    HIER_DEAD_NEIGHBOR,
    HIER_REVIVE_PARENT,
    HIER_REVIVE_NEIGHBOR,
    HIER_NO_DIRECT_FAIL,
    HIER_SOURCE_FASTEST,
    HIER_MAX
} hier_code;


/* Mark a neighbor cache as dead if it doesn't answer this many pings */
#define HIER_MAX_DEFICIT  20

typedef struct _dom_list {
    char *domain;
    int do_ping;		/* boolean */
    struct _dom_list *next;
} dom_list;

#define EDGE_MAX_ADDRESSES 10
struct _edge {
    char *host;
    struct sockaddr_in in_addr;
    int rtt;
    int ack_deficit;
    enum {
	is_a_neighbor = 0, is_a_parent = 1
    } type;			/* 0 if neighbor, 1 if parent */

    int num_pings;
    int pings_sent;
    int pings_acked;
    int neighbor_up;		/* 0 if no, 1 if yes */
    int hits;
    int misses;

    int udp_port;
    int ascii_port;
    icp_common_t header;
    dom_list *domains;
    int proxy_only;
    time_t last_fail_time;	/* detect down dumb caches */
    struct in_addr addresses[10];
    int n_addresses;
    struct _edge *next;
};

typedef struct {
    int n;
    int n_parent;
    int n_neighbor;
    edge *edges_head;
    edge *edges_tail;
    edge *first_ping;
    int fd;
} neighbors;

struct neighbor_cf {
    char *host;
    char *type;
    int ascii_port;
    int udp_port;
    int proxy_only;
    dom_list *domains;
    struct neighbor_cf *next;
};

extern edge *getFirstEdge _PARAMS((void));
extern edge *getFirstParent _PARAMS((char *host));
extern edge *getNextEdge _PARAMS((edge *));
extern edge *getSingleParent _PARAMS((char *host, int *n));
extern int neighborsUdpPing _PARAMS((protodispatch_data *));
extern int neighbors_cf_domain _PARAMS((char *, char *));
extern neighbors *neighbors_create _PARAMS(());
extern void hierarchy_log_append _PARAMS((char *, hier_code, int, char *));
extern void neighborsUdpAck _PARAMS((int, char *, icp_common_t *, struct sockaddr_in *, StoreEntry *));
extern void neighbors_cf_add _PARAMS((char *, char *, int, int, int));
extern void neighbors_init _PARAMS((void));
extern void neighbors_open _PARAMS((int));
extern void neighbors_rotate_log _PARAMS((void));

#endif
