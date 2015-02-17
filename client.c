/*
** server.c for raytracer in /home/snap/projects/raytracer/clustering
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Mon May  3 16:41:27 2010 botton vivien
** Last update Sun Jun  6 23:07:02 2010 philippe berenguel
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
#include <SDL/SDL.h>
#include "raytracer.h"
#include "xnet.h"
#include "xsdl.h"

int			connect_to(char *addr)
{
  int			socketfd;
  char			*dup;
  char			**tab;
  struct sockaddr_in    sa;

  dup = my_strdup(addr);
  tab = my_explode(dup, ':');
  if (sizeof_tab(tab) != 2)
    return (-1);
  if ((socketfd = xsocket(AF_INET, SOCK_STREAM, 0)) < 0)
    return (-1);
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr(tab[0]);
  sa.sin_port = htons(atoi(tab[1]));
  if (xconnect(socketfd, (struct sockaddr*)&sa, sizeof(sa)) == -1)
    {
      close(socketfd);
      return (-1);
    }
  return (socketfd);
}

int			recv_img(t_client *client)
{
  ssize_t		len;
  size_t		decal;
  size_t		size_img;
  char			buffer[PACKET_LEN];
  char			*begin;

  if (send_pos(client, buffer) == -1 || send_conf_file(client) == -1)
    return (EXIT_FAILURE);
  decal = 0;
  len = 1;
  printf("Receive image ...\n");
  size_img = (client->endy - client->starty) * client->screen->w *
    client->screen->format->BytesPerPixel;
  begin = (char *)client->screen->pixels + client->starty * client->screen->w
    * client->screen->format->BytesPerPixel;
  while (len > 0 && decal < size_img)
    {
      len = xrecv(client->clientfd, begin + decal, PACKET_LEN, MSG_NOSIGNAL);
      decal += len;
    }
  close(client->clientfd);
  printf("done\n");
  return (decal - size_img);
}

void			retry_connect(t_client *clients,
				      t_client *this, int count)
{
  int			sockfd;

  sockfd = -1;
  while (clients && sockfd == -1)
    {
      if ((clients->done && clients != this) || count > 97)
		sockfd = connect_to(clients->addr);
      if (sockfd == -1)
		clients = clients->next;
    }
  if (clients && sockfd != -1)
    {
      this->clientfd = sockfd;
      client(this);
    }
  else
    {
      count++;
      usleep(80000);
     if (count < 100)
		retry_connect(this->list, this, count);
    }
}

void			client(void *arg)
{
  t_client              *client;

  client = (t_client*)arg;
  if (recv_img(client))
    {
      printf("failure\n");
      retry_connect(client->list, client, 0);
    }
  else
    client->done = 1;
}

int		send_rt(int ac, char **av, int mode, t_var *data)
{
  t_client		*clients;
  char			*file;
  size_t		sizes[2];

  clients = tryconnect_clients(ac, av, &sizes[0], 3 + (mode & FULLSCREEN));
  if (clients)
    file = read_conf_file(av[2 + (mode & FULLSCREEN)], &sizes[1]);
  else
    return (EXIT_FAILURE);
  xsdl_init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
  SDL_WM_SetCaption(TITLE, NULL);
  data->filename = remove_ext(av[2]);
  data->sizex = 1024;
  data->sizey = 768;
  mode = (mode & FULLSCREEN)? SDL_SWSURFACE | SDL_DOUBLEBUF
    | SDL_FULLSCREEN : SDL_SWSURFACE | SDL_DOUBLEBUF;
  get_resolution(file, sizes[1], data);
  data->screen = xsdl_setvideomode(data->sizex, data->sizey, BCOLOR, mode);
  treat_clients(clients, sizes, file, data);
  xsdl_flip(data->screen);
  free_clients(clients);
  handle_keys(data);
  SDL_Quit();
  return (EXIT_SUCCESS);
}
