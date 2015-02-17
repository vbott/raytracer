/*
** tga.c for raytracer in /home/snap/projects/raytracer/massal
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Mon May 31 09:16:11 2010 botton vivien
** Last update Tue Jun  8 09:55:07 2010 vivien botton
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <SDL/SDL.h>
#include "raytracer.h"
#include "tga.h"

char		*remove_ext(char *str)
{
  size_t	i;

  i = my_strlen(str);
  while (i >= 1 && str[i] != '.')
    i--;
  if (str[i] == '.')
    str[i] = '\0';
  return (str);
}

static void	write_header(t_var *data, int fd)
{
  t_tga		header;

  memset(&header, 0, sizeof(header));
  header.datatypecode = 2;
  header.width = data->screen->w;
  header.height = data->screen->h;
  header.bitsperpixel = BCOLOR;
  header.imagedescriptor = 32;
  write(fd, &header, sizeof(header));
}

void		dump_to_tga(t_var *data)
{
  int		fd;
  char		*file;

  file = my_strcat(my_strdup(data->filename), ".tga");
  fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  if (fd != -1)
    {
      write_header(data, fd);
      write(fd, data->screen->pixels,  data->screen->w *
	    data->screen->h * data->screen->format->BytesPerPixel);
      printf("File saved in %s\n", file);
      close(fd);
    }
  free(file);
}
