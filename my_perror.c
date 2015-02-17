/*
** my_perror.c for raytracer in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun May 30 19:18:50 2010 cailleux carole
** Last update Sun May 30 19:18:50 2010 cailleux carole
*/

#include <stdio.h>
#include <stdlib.h>
#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include <SDL/SDL.h>
#include <unistd.h>
#include "raytracer.h"

ssize_t		xwrite(int fd, const void *buf, size_t count)
{
  int		i;

  i = write(fd, buf, count);
  if (i == -1)
    my_perror("write failure\n");
  return (i);
}

void		my_perror(char *str)
{
  xwrite(2, str, my_strlen(str));
}
