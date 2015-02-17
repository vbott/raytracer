/*
** xmalloc.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:15:20 2010 mickael cerisier
** Last update Mon Mar 15 01:15:20 2010 mickael cerisier
*/

#include <stdlib.h>

void		*xmalloc(int size)
{
  void		*data;

  data = malloc(size);
  if (data == NULL)
    exit(1);
  return (data);
}
