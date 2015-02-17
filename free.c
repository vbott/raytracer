/*
** free.c for raytracer in /home/shotgun/svn/raytracer
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Apr 26 10:19:48 2010 cerisier mickael
** Last update Tue Jun  8 09:49:22 2010 vivien botton
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

void		free_list(t_list *list, int free_img)
{
  t_list	*cpy;

  while (list)
    {
      cpy = list;
      list = list->next;
      if (free_img && cpy->img)
	SDL_FreeSurface(cpy->img);
      free(cpy);
    }
}

void		free_win(t_var *win)
{
  free_list(win->list, 0);
  free_list(win->spot, 0);
  free(win);
}

void		free_clients(t_client *clients)
{
  t_client	*cpy;

  while (clients)
    {
      cpy = clients;
      clients = clients->next;
      free(cpy->file);
      free(cpy);
    }
}
