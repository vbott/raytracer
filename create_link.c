/*
** create_link.c for raytracer in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun May 30 17:03:12 2010 cailleux carole
** Last update Sun May 30 17:03:12 2010 cailleux carole
*/

#include <stdlib.h>
#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include <libxml/xpath.h>
#include <SDL/SDL.h>
#include "raytracer.h"

void		init_list(t_list *new)
{
  memset(new, 0, sizeof(*new));
  new->l_top = -1;
  new->l_bottom = -1;
}

void		create_link(t_var *data)
{
  t_list	*new;

  new = xmalloc(sizeof(*new));
  init_list(new);
  new->next = data->list;
  data->list = new;
}
