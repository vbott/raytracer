/*
** shutdown.c for raytracer in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Jun  3 20:46:59 2010 cailleux carole
** Last update Thu Jun  3 20:46:59 2010 cailleux carole
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
#include <SDL/SDL.h>
#include "raytracer.h"
#include "xnet.h"

int		shutdown_rt(int ac, char **av)
{
  t_client	*clients;
  t_client	*cpy;
  size_t	nbclients;

  clients = tryconnect_clients(ac, av, &nbclients, 2);
  while (clients)
    {
      cpy = clients;
      xsend(clients->clientfd, "000000000000shutdown", 20, MSG_NOSIGNAL);
      close(clients->clientfd);
      clients = clients->next;
      free(cpy);
    }
  return (EXIT_SUCCESS);
}
