/*
** send_conf_file.c for raytracer in /home/snap/projects/raytracer
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sun Jun  6 21:44:55 2010 botton vivien
** Last update Sun Jun  6 21:44:55 2010 botton vivien
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
# include <sys/stat.h>
# include <sys/mman.h>
#endif
#include <fcntl.h>
#include "raytracer.h"
#include "xnet.h"

char		*read_conf_file(char *path, size_t *size)
{
  int		filefd;
  char		*file;
  struct stat sb;

  filefd = open(path, O_RDONLY);
  if (filefd == -1)
	return (NULL);
  fstat(filefd, &sb);
  *size = sb.st_size;
  file = (char*)mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, filefd, 0);
  return (file);
}

int			send_conf_file(t_client *client)
{
  size_t		i;
  int			sended;

  sended = 0;
  printf("Send file ...\n");
  i = 0;
  sended = xsend(client->clientfd, client->file, client->sizefile, MSG_NOSIGNAL);
  if (sended != -1)
    sended = xsend(client->clientfd, &i, 2, MSG_NOSIGNAL);
  printf("%s\n", (sended != -1) ? "done" : "error in sending file");
  if (sended != -1)
    xshutdown(client->clientfd, SHUT_WR);
  return (sended);
}

void		get_resolution(char *file, size_t size, t_var *data)
{
  size_t	i;
  int		found;

  i = 0;
  found = 0;
  size -= 6;
  while (i < size && found < 2)
    {
      if (!strncmp("<winx>", &file[i], 6))
	{
	  data->sizex = my_getnbr(&file[i + 6]);
	  found++;
	}
      else if (!strncmp("<winy>", &file[i], 6))
	{
	  data->sizey = my_getnbr(&file[i + 6]);
	  found++;
	}
      i++;
    }
}
