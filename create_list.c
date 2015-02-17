/*
** create_list.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:13:40 2010 mickael cerisier
** Last update Mon Mar 15 01:13:40 2010 mickael cerisier
*/

#include <stdlib.h>
#include <SDL/SDL.h>
#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include "raytracer.h"

int		sizeof_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}

void		separate_list(t_var *var)
{
  t_list	*mem;
  t_list	*list;

  var->spot = 0;
  list = 0;
  while (var->list)
    {
      mem = var->list->next;
      if (var->list->type == 0)
	{
	  var->list->next = var->spot;
	  var->spot = var->list;
	}
      else
	{
	  var->list->next = list;
	  list = var->list;
	}
      var->list = mem;
    }
  var->list = list;
}
