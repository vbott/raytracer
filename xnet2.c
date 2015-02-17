/*
** xnet2.h for raytracer in /home/snap/projects/raytracer/clustering
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Wed May 26 14:14:59 2010 botton vivien
** Last update Wed May 26 14:14:59 2010 botton vivien
*/

#if defined (WIN32)
# include <winsock2.h>
# include <windows.h>
#else
# include <sys/types.h>
# include <sys/socket.h>
#endif
#include <stdio.h>
#include "xnet.h"

ssize_t		xsend(SOCKET sockfd, const void *buf, size_t len, int flags)
{
  ssize_t	res;

  res = send(sockfd, buf, len, flags);
  if (res == -1)
    perror("send");
  return (res);
}

ssize_t		xrecv(SOCKET sockfd, void *buf, size_t len, int flags)
{
  ssize_t	res;

  res = recv(sockfd, buf, len, flags);
  if (res == -1)
    perror("recv");
  return (res);
}

int		xshutdown(SOCKET sockfd, int how)
{
  int		res;

  res = shutdown(sockfd, how);
  if (res == -1)
    perror("shutdown");
  return (res);
}
