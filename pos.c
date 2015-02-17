/*
** pos.c for raytracer in /home/snap/projects/raytracer/massal
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Mon May 31 11:51:02 2010 botton vivien
** Last update Mon May 31 11:51:02 2010 botton vivien
*/

#if defined (WIN32)
# include <winsock2.h>
# include <stdio.h>
# include <windows.h>
#else
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
#endif
#include <SDL/SDL.h>
#include "raytracer.h"
#include "xnet.h"

static int	get_nb(unsigned char *buffer)
{
  int		res;

  res = buffer[0] << 24;
  res |= buffer[1] << 16;
  res |= buffer[2] << 8;
  res |= buffer[3];
  return (res);
}

int		get_pos(t_client *client)
{
  unsigned char buffer[12];
  int		res;

  res = xrecv(client->clientfd, buffer, 12, 0);
  if (res == -1 || res < 12)
    return (-1);
  client->sizex = get_nb(buffer);
  client->starty = get_nb(&buffer[4]);
  client->endy = get_nb(&buffer[8]);
  return (EXIT_SUCCESS);
}

static void	write_nb(int nb, char *buffer)
{
  buffer[0] = nb >> 24;
  buffer[1] = (nb >> 16) & 255;
  buffer[2] = (nb >> 8) & 255;
  buffer[3] = nb & 255;
}

int		send_pos(t_client *client, char *buffer)
{
  write_nb(client->sizex, buffer);
  write_nb(client->starty, &buffer[4]);
  write_nb(client->endy, &buffer[8]);
  return (xsend(client->clientfd, buffer, 12, 0));
}
