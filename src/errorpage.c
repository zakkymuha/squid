/* $Id: errorpage.c,v 1.5 1996/03/29 01:07:35 wessels Exp $ */

#include "squid.h"



#define CACHED_ERROR_MSG_P1 "\
<TITLE>ERROR: The requested URL could not be retrieved</TITLE>\n\
<H2>The requested URL could not be retrieved</H2>\n\
<HR>\n\
<P>\n\
While trying to retrieve the URL:\n\
<A HREF=\"%s\">%s</A>\n\
<P>\n\
The following error was encountered:\n\
<UL>\n\
<LI><STRONG>%s</STRONG>\n\
</UL>\n\
"

#define CACHED_ERROR_MSG_P2 "\
<P>The system returned:\n\
<PRE><I>    %s</I></PRE>\n\
"

#define CACHED_ERROR_MSG_P3 "\
<P>This means that:\n\
<PRE>\n\
    %s\n\
</PRE>\n\
<P> <HR>\n\
<ADDRESS>\n\
Generated by cached/%s@%s\n\
</ADDRESS>\n\
\n"

typedef struct {
    char *tag;
    char *shrt;
    char *lng;
} error_data;

error_data ErrorData[] =
{
    {"ERR_NONE",
	"Non Error",
	"You should never see this."},
    {"ERR_READ_TIMEOUT",
	"Read Timeout",
	"The remote site or network may be down.  Please try again."},
    {"ERR_LIFETIME_EXP",
	"Transaction Timeout",
	"The network or remote site may be down or too slow.  Try again later."},
    {"ERR_NO_CLIENTS_BIG_OBJ",
	"No Client",
	"All Clients went away before tranmission completed and the object is too big to cache."},
    {"ERR_READ_ERROR",
	"Read Error",
	"The remote site or network may be down.  Please try again."},
    {"ERR_CLIENT_ABORT",
	"Client Aborted",
	"Client(s) dropped connection before transmission completed.\nObject fetching is aborted.",},
    {"ERR_CONNECT_FAIL",
	"Connection Failed",
	"The remote site or server may be down.  Please try again soon."},
    {"ERR_INVALID_URL",
	"Invalid URL syntax",
	"Please double check it, or ask for assistance."},
    {"ERR_NO_FDS",
	"Out of file descriptors",
	"The cache is currently very busy.  Please try again."},
    {"ERR_DNS_FAIL",
	"DNS name lookup failure",
	"The named host probably does not exist."},
    {"ERR_NOT_IMPLEMENTED",
	"Protocol Not Supported",
	"The cache does not know about the requested protocol."},
    {"ERR_CANNOT_FETCH",
	"Unable to Retrieve",
	"The requested URL can not currently be retrieved."},
    {"ERR_NO_RELAY",
	"No WAIS Relay",
	"There is no WAIS relay host defined for this cache."},
    {"ERR_DISK_IO",
	"Cache Disk I/O Failure",
	"The system disk is out of space or failing."},
    {"ERR_URL_BLOCKED",
	"Access Denied",
	"You are not allowed to access this URL."},
    {"ERR_MAX"
	"",
	""}
};

/* GLOBAL */
char tmp_error_buf[BUFSIZ];

/* LOCAL */
static char tbuf[BUFSIZ];

int log_errors = 1;


void cached_error_entry(entry, type, msg)
     StoreEntry *entry;
     error_t type;
     char *msg;
{
    if (type == ERR_NONE || type > ERR_MAX)
	return;
    sprintf(tmp_error_buf, CACHED_ERROR_MSG_P1,
	entry->url,
	entry->url,
	ErrorData[type].shrt);
    if (msg) {
	sprintf(tbuf, CACHED_ERROR_MSG_P2, msg);
	strcat(tmp_error_buf, tbuf);
    }
    sprintf(tbuf, CACHED_ERROR_MSG_P3,
	ErrorData[type].lng,
	SQUID_VERSION,
	getMyHostname());
    strcat(tmp_error_buf, tbuf);
    storeAbort(entry, tmp_error_buf);
    if (!log_errors)
	return;
    CacheInfo->log_append(CacheInfo,
	entry->url,
	"0.0.0.0",
	entry->mem_obj->e_current_len,
	ErrorData[type].tag,
	"GET");
}



char *cached_error_url(url, type, msg)
     char *url;
     error_t type;
     char *msg;
{
    tmp_error_buf[0] = '\0';

    if (type == ERR_NONE || type > ERR_MAX)
	return tmp_error_buf;
    sprintf(tmp_error_buf, CACHED_ERROR_MSG_P1,
	url,
	url,
	ErrorData[type].shrt);

    if (msg) {
	sprintf(tbuf, CACHED_ERROR_MSG_P2, msg);
	strcat(tmp_error_buf, tbuf);
    }
    sprintf(tbuf, CACHED_ERROR_MSG_P3,
	ErrorData[type].lng,
	SQUID_VERSION,
	getMyHostname());
    if (!log_errors)
	return tmp_error_buf;
    CacheInfo->log_append(CacheInfo,
	url,
	"0.0.0.0",
	0,
	ErrorData[type].tag,
	"GET");
    return tmp_error_buf;
}
