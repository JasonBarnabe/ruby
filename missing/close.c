/* Ignore ECONNRESET of FreeBSD */
#include "ruby/missing.h"
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int
ruby_getpeername(int s, struct sockaddr * name,
         socklen_t * namelen)
{
    int err = errno;
    errno = 0;
    s = getpeername(s, name, namelen);
    if (errno == ECONNRESET) {
	errno = 0;
	s = 0;
    }
    else if (errno == 0)
	errno = err;
    return s;
}

int
ruby_getsockname(int s, struct sockaddr * name,
         socklen_t * namelen)
{
    int err = errno;
    errno = 0;
    s = getsockname(s, name, namelen);
    if (errno == ECONNRESET) {
	errno = 0;
	s = 0;
    }
    else if (errno == 0)
	errno = err;
    return s;
}

int
ruby_shutdown(int s, int how)
{
    int err = errno;
    errno = 0;
    s = shutdown(s, how);
    if (errno == ECONNRESET) {
	errno = 0;
	s = 0;
    }
    else if (errno == 0)
	errno = err;
    return s;
}

int
ruby_close(int s)
{
    int err = errno;
    errno = 0;
#undef close
    s = close(s);
    if (errno == ECONNRESET) {
	errno = 0;
	s = 0;
    }
    else if (errno == 0)
	errno = err;
    return s;
}
