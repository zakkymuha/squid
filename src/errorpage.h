
/*
 * $Id: errorpage.h,v 1.23 1997/06/19 22:51:49 wessels Exp $
 *
 * AUTHOR: Duane Wessels
 *
 * SQUID Internet Object Cache  http://squid.nlanr.net/Squid/
 * --------------------------------------------------------
 *
 *  Squid is the result of efforts by numerous individuals from the
 *  Internet community.  Development is led by Duane Wessels of the
 *  National Laboratory for Applied Network Research and funded by
 *  the National Science Foundation.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *  
 */

extern char *squid_error_url _PARAMS((const char *, int, int, const char *, int, const char *));
extern char *squid_error_request _PARAMS((const char *, int, int));
extern void errorInitialize _PARAMS((void));
extern char *access_denied_msg _PARAMS((int, int, const char *, const char *));
extern char *access_denied_redirect _PARAMS((int, int, const char *, const char *, const char *));
#if USE_PROXY_AUTH
extern char *proxy_denied_msg _PARAMS((int, int, const char *, const char *));
#endif /* USE_PROXY_AUTH */
extern char *authorization_needed_msg _PARAMS((const request_t *, const char *));
extern void errorpageFreeMemory _PARAMS((void));

extern char *tmp_error_buf;
