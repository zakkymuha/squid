


typedef enum {
    MGR_NONE,
    MGR_CLIENT_LIST,
    MGR_CONFIG,
    MGR_CONFIG_FILE,
    MGR_DNSSERVERS,
    MGR_FILEDESCRIPTORS,
    MGR_FQDNCACHE,
    MGR_INFO,
    MGR_IO,
    MGR_IPCACHE,
    MGR_LOG_CLEAR,
    MGR_LOG_DISABLE,
    MGR_LOG_ENABLE,
    MGR_LOG_STATUS,
    MGR_LOG_VIEW,
    MGR_NETDB,
    MGR_OBJECTS,
    MGR_REDIRECTORS,
    MGR_REFRESH,
    MGR_REMOVE,
    MGR_REPLY_HDRS,
    MGR_SERVER_LIST,
    MGR_SHUTDOWN,
    MGR_UTILIZATION,
    MGR_VM_OBJECTS,
    MGR_MAX
} objcache_op;

static char *objcacheOpcodeStr[] = {
    "NONE"
    "client_list",
    "config",
    "config_file",
    "dnsservers",
    "filedescriptors",
    "fqdncache",
    "info",
    "io",
    "ipcache",
    "log/clear",
    "log/disable",
    "log/enable",
    "log/status",
    "log/view",
    "netdb",
    "objects",
    "redirectors",
    "refresh",
    "remove",
    "reply_headers",
    "server_list",
    "shutdown",
    "utilization",
    "vm_objects",
    "MAX"
};

