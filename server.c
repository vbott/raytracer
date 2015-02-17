/*
** server.c for raytracer in /home/snap/projects/raytracer/clustering
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Mon May  3 16:41:27 2010 botton vivien
** Last update Tue Jun  8 09:48:54 2010 vivien botton
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
#include "xsdl.h"
#include "raytracer.h"
#include "xnet.h"

int		init_listen(int port, struct sockaddr_in *sa, socklen_t sizesa)
{
  int			socketfd;

  if ((socketfd = xsocket(AF_INET, SOCK_STREAM, 0)) < 0)
    exit(EXIT_FAILURE);
  memset(sa, 0, sizesa);
  sa->sin_family = AF_INET;
  sa->sin_addr.s_addr = INADDR_ANY;
  sa->sin_port = htons(port);
  if (xbind(socketfd, (struct sockaddr *)sa, sizesa) == -1)
    exit(EXIT_FAILURE);
  if (xlisten(socketfd, 2) == -1)
    exit(EXIT_FAILURE);
  printf("service started on port %d\n", port);
  return (socketfd);
}

char		*get_conf_file(t_client *client)
{
  char		*file;
  char	       	buffer[PACKET_LEN + 1];
  ssize_t	len;
  int		cont;

  file = NULL;
  cont = 1;
  len = -1;
  if (get_pos(client) == -1)
    return (NULL);
  printf("Receive file ...\n");
  while (cont &&
	 (len = xrecv(client->clientfd, buffer, PACKET_LEN, MSG_NOSIGNAL)) != -1
	 && len)
    {
      if (buffer[len - 1] != 0)
		buffer[len] = '\0';
      else
		cont = 0;
      file = my_strcat(file, buffer);
    }
  if (len != -1)
    xshutdown(client->clientfd, SHUT_RD);
  printf("%s\n", (len != -1) ? "done" : "error in receiving");
  return ((len != -1) ? file : NULL);
}

void		send_img(SDL_Surface *img, int clientfd)
{
  /*size_t	mod;
  size_t	i;*/
  int		sended;
  size_t	len;

  len = img->w * img->h * img->format->BytesPerPixel;
  /*mod = len % PACKET_LEN;
  i = 0;*/
  sended = 0;
  printf("Send image ...\n");
  /*while (sended != -1 && i < (len - mod))
    {
      sended = xsend(clientfd, (char *) img->pixels + i,
		     PACKET_LEN, MSG_NOSIGNAL);
      i += sended;
    }
  if (mod && sended != -1)
    sended = xsend(clientfd, (char *)
		   img->pixels + i, mod, MSG_NOSIGNAL);*/
  sended = xsend(clientfd, (char *) img->pixels, len, MSG_NOSIGNAL);
  if (sended != -1)
    xshutdown(clientfd, SHUT_WR);
  printf("%s\n", (sended != -1) ? "done" : "error in sending");
}

void		calculate(t_client *client, t_var *data)
{
  if (!init_data(client->file, data,
		 client->sizex, client->endy - client->starty))
    {
      data->realstarty = client->starty;
      data->sizex = client->sizex;
      printf("Calculating ...\n");
      start_thread(data, client->starty, client->endy);
      printf("done\n");
      send_img(data->screen, client->clientfd);
      SDL_FreeSurface(data->screen);
    }
  close(client->clientfd);
}

int		listen_rt(t_var *data, int port)
{
  int			socketfd;
  t_client		client;
  struct sockaddr_in	sa;
  socklen_t		len;

  len = sizeof(sa);
  socketfd = init_listen(port, &sa, len);
  xsdl_init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
  while (len)
    {
      client.clientfd = xaccept(socketfd, (struct sockaddr *)&sa, &len);
      if (client.clientfd != -1)
	{
	  client.file = get_conf_file(&client);
	  if (client.file && my_strcmp(client.file, "shutdown"))
	    calculate(&client, data);
	  else if (client.file)
	    len = 0;
	}
    }
  close(socketfd);
  SDL_Quit();
  return (EXIT_SUCCESS);
}
