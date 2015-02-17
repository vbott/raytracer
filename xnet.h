/*
** xnet.h for raytracer in /home/snap/projects/raytracer/clustering
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Wed May 26 13:51:40 2010 botton vivien
** Last update Tue Jun  1 14:44:28 2010 mickael cerisier
*/

#ifndef		_XNET_H_
# define	_XNET_H_

# ifndef	SOCKET
#  define	SOCKET int
# endif		/* !SOCKET */

# ifndef	MSG_NOSIGNAL
#  define	MSG_NOSIGNAL 0
# endif		/* !MSG_NOSIGNAL */

# ifndef	INVALID_SOCKET
#  define	INVALID_SOCKET -1
# endif		/* !INVALID_SOCKET*/

# ifndef	SOCKET_ERROR
#  define	SOCKET_ERROR -1
# endif		/* !SOCKET_ERROR*/

# ifndef	SHUT_RD
#  define	SHUT_RD SD_RECEIVE
# endif		/* !SHUT_RD*/

# ifndef	SHUT_WR
#  define	SHUT_WR SD_SEND
# endif		/* !SHUT_WR */

# if defined (WIN32)
#  define usleep(param) Sleep(param / 1000)
# endif

# if	!defined (__socklen_t_defined) && !defined (_SOCKLEN_T_DECLARED)
typedef int	socklen_t;
# endif		/* !__socklen_t_defined && _SOCKLEN_T_DECLARED */

SOCKET	xsocket(int domain, int type, int protocol);
int	xbind(SOCKET sockfd, const struct sockaddr *addr, socklen_t addrlen);
int	xlisten(SOCKET sockfd, int backlog);
SOCKET	xaccept(SOCKET sockfd, struct sockaddr *addr, socklen_t *addrlen);
int	xconnect(SOCKET sockfd, const struct sockaddr *addr,
		 socklen_t addrlen);
int	xshutdown(SOCKET sockfd, int how);
ssize_t xsend(int sockfd, const void *buf, size_t len, int flags);
ssize_t xrecv(int sockfd, void *buf, size_t len, int flags);

#endif		/* !_XNET_H */
