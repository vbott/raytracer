/*
** string.c for raytracer in /home/snap/projects/raytracer/massal
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sun May 30 16:44:20 2010 botton vivien
** Last update Sun May 30 16:44:20 2010 botton vivien
*/

#include <stdlib.h>
#include "raytracer.h"

int		my_strcmp(const char *s1, const char *s2)
{
  int		i;

  i = 0;
  while (s1[i] && s2[i] && s1[i] == s2[i])
    i++;
  return (s1[i] - s2[i]);
}

size_t		my_strlen(const char *str)
{
  size_t	i;

  if (!str)
    return (0);
  i = 0;
  while (str[i])
    i++;
  return (i);
}

char		*my_strcat(char *s1, const char *s2)
{
  int		i;
  int		j;
  char		*res;

  res = xmalloc((my_strlen(s1) + my_strlen(s2) + 1) * sizeof(*res));
  i = 0;
  while (s1 && s1[i])
    {
      res[i] = s1[i];
      i++;
    }
  j = 0;
  while (s2 && s2[j])
    {
      res[i] = s2[j];
      i++;
      j++;
    }
  if (s1)
    free(s1);
  res[i] = '\0';
  return (res);
}

char		*my_strdup(const char *str)
{
  char		*res;
  size_t	i;

  res = xmalloc((my_strlen(str) + 1) * sizeof(*res));
  i = 0;
  while (str[i])
    {
      res[i] = str[i];
      i++;
    }
  res[i] = '\0';
  return (res);
}

void			my_memcpy(const void *src, void *dest, int n)
{
  int			i;
  char			*a;
  char			*b;

  if (n <= 0)
    return ;
  i = 0;
  a = (char*)src;
  b = (char*)dest;
  while (i < n)
    {
      b[i] = a[i];
      i++;
    }
}
