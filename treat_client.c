/*
** treat_client.c for raytracer in /home/snap/projects/raytracer/massal
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Mon May 31 12:04:08 2010 botton vivien
** Last update Sun Jun  6 23:02:41 2010 philippe berenguel
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
# include <arpa/inet.h>
# include <netdb.h>
# include <signal.h>
#endif
#include <pthread.h>
#include <fcntl.h>
#include <SDL/SDL.h>
#include "raytracer.h"
#include "xnet.h"

void		fill_client(t_client **next, size_t *nbclients,
			    char *addr, int socketfd)
{
  t_client	*clients;

  *nbclients += 1;
  clients = xmalloc(sizeof(*clients));
  clients->clientfd = socketfd;
  clients->addr = addr;
  clients->done = 0;
  clients->next = *next;
  *next = clients;
}

t_client     	*tryconnect_clients(int ac, char **av,
				    size_t *nbclients, int index)
{
  int		i;
  int		socketfd;
  t_client	*next;

  i = index;
  next = NULL;
  *nbclients  = 0;
  while (i < ac)
    {
      socketfd = connect_to(av[i]);
      if (socketfd != -1)
	fill_client(&next, nbclients, av[i], socketfd);
      i++;
    }
  return (next);
}

void		fill_info(t_client *clients, char *file,
			  size_t size, t_var *data)
{
  clients->screen = data->screen;
  clients->file = xmalloc((size + 1) * sizeof(*file));
  my_memcpy(file, clients->file, size);
  clients->file[size] = '\0';
  clients->sizefile = size;
  clients->sizex = data->sizex;
}

void		treat_clients(t_client *clients, size_t *sizes,
			      char *file, t_var *data)
{
  pthread_t	*thread;
  size_t	starty;
  size_t	decal;
  size_t	i;
  t_client	*cpy;

  thread = xmalloc(sizes[0] * sizeof(*thread));
  starty = 0;
  i = 0;
  decal = data->sizey / sizes[0];
  cpy = clients;
  while (clients)
    {
      clients->list = cpy;
      fill_info(clients, file, sizes[1], data);
      clients->starty = starty;
      clients->endy = starty + decal;
      pthread_create(&thread[i], NULL, (void *(*)(void*))client, clients);
      clients = clients->next;
      starty += decal;
      i++;
    }
  free(file);
  wait_for_thread(thread, sizes[0]);
}
