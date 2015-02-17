/*
** my_getnbr_base.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:14:20 2010 mickael cerisier
** Last update Mon Mar 15 01:14:20 2010 mickael cerisier
*/

#include <SDL/SDL.h>
#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include "raytracer.h"

int		my_power_rec(int nb, int power)
{
  if (power < 0)
    return (0);
  if (power == 0)
    return (1);
  if (power > 1)
    nb = nb * my_power_rec(nb, power - 1);
  return (nb);
}

int		my_numberbase(char *str, int lennbr)
{
  int		i;
  int		e;
  int		nbr;
  int		number;
  char		*base;

  i = 0;
  nbr = 0;
  base = "0123456789abcdef";
  while (str[i] != '\0')
    {
      e = 0;
      number = -1;
      while (base[e] != '\0' && number == -1)
	{
	  if (is_lowalpha(str[i]) == base[e])
	    number = e;
	  e++;
	}
      if (number == -1)
	return (nbr);
      nbr += (number * my_power_rec(16, (lennbr - i)));
      i++;
    }
  return (nbr);
}

int		my_strlen_getbase(char *str)
{
  int		i;

  i = 0;
  while (is_ok(str[i]))
    i++;
  return (i);
}

int		my_getnbr_base(char *str)
{
  int		nbr;
  int		lennbr;

  nbr = 0;
  while (str[0] != 'x' && str[0] != '\0')
    str++;
  if (str[0] != '\0')
    str++;
  lennbr = my_strlen_getbase(str) - 1;
  if (lennbr == -1)
     return (0xFFFFFF);
  nbr = my_numberbase(str, lennbr);
  return (nbr);
}
