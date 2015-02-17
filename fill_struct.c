/*
** fill_struct.c for raytracer in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun May 30 18:24:15 2010 cailleux carole
** Last update Sun Jun  6 21:54:53 2010 philippe berenguel
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
#include <SDL/SDL_image.h>
#include "xsdl.h"
#include "raytracer.h"

static const t_object	gl_object[] = {
  {0, "light"},
  {1, "plan"},
  {2, "sphere"},
  {3, "cylinder"},
  {4, "cone"},
  {5, "paraboloid"},
  {6, "hyperboloid"},
  {7, "disk"},
  {8, "parallelogram"},
  {9, "torus"},
  {0, 0}
};

int		get_object_type(char *type)
{
  int		i;

  i = 0;
  while (gl_object[i].object)
    {
      if (!my_strcmp(type, gl_object[i].object))
	return (gl_object[i].type);
      i++;
    }
  xwrite(2, type, my_strlen(type));
  xwrite(2, ": bad object type.\n", 19);
  exit(EXIT_FAILURE);
}

int		f_int(t_list *list, char *value, char *type)
{
  int		content_nbr;

  content_nbr = my_getnbr(value);
  if (!my_strcmp(type, "radius"))
    list->r = content_nbr;
  else if (!my_strcmp(type, "limit_x"))
    list->l_top = content_nbr;
  else if (!my_strcmp(type, "limit_y"))
    list->l_bottom = content_nbr;
  else if (!my_strcmp(type, "pos"))
    get_vector(&(list->pos), my_strdup(value), VECTOR);
  else if (!my_strcmp(type, "material"))
    list->material = (content_nbr < 0 || content_nbr > 3) ? 0 : content_nbr;
  else if (!my_strcmp(type, "cte"))
    list->cte = content_nbr;
  else if (!my_strcmp(type, "negative"))
    list->negative = content_nbr;
  else
    return (0);
  return (1);
}

int		f_float(t_list *list, char *value, char *type)
{
  float		content_nbr;

  content_nbr = my_getfloat(value);
  if (!my_strcmp(type, "brightness"))
    list->bright = content_nbr;
  else if (!my_strcmp(type, "reflection"))
    list->reflection = content_nbr;
  else if (!my_strcmp(type, "transparency"))
    list->transparency = content_nbr;
  else if (!my_strcmp(type, "refract_index"))
    list->refract_index = content_nbr;
  else if (!my_strcmp(type, "rotation"))
    get_vector(&(list->angle), my_strdup(value), ANGLE);
  else if (!my_strcmp(type, "bump"))
    list->bump = (double) content_nbr;
  else if (!my_strcmp(type, "img") && !list->img && list->type)
    list->img = ximg_load(value);
  else if (!my_strcmp(type, "wave"))
    get_vector(&(list->wave), my_strdup(value), VECTOR);
  else
    return (0);
  return (1);
}

int		f_special(t_list *list, char *value, char *type)
{
  int		color;

  if (!my_strcmp((char *)type, "type"))
    list->type = get_object_type(value);
  else if (!my_strcmp(type, "color"))
    {
      color = my_getnbr_base(value);
      list->rgb.b = (color & 255) / 255.0f;
      list->rgb.g = ((color >> 8) & 255) / 255.0f;
      list->rgb.r = ((color >> 16) & 255) / 255.0f;
    }
  else if (!my_strcmp(type, "noise"))
    {
      color = my_getnbr_base(value);
      list->noise.b = (color & 255) / 255.0f;
      list->noise.g = ((color >> 8) & 255) / 255.0f;
      list->noise.r = ((color >> 16) & 255) / 255.0f;
    }
  else if (!my_strcmp(type, "v1"))
    get_vector(&(list->v1), my_strdup(value), VECTOR);
  else if (!my_strcmp(type, "v2"))
    get_vector(&(list->v2), my_strdup(value), VECTOR);
  else
    return (0);
  return (1);
}

int		f_attribute(xmlNodePtr root, xmlDocPtr doc, t_var *data)
{
  xmlChar	*key;
  int		nb;

  key = xmlNodeListGetString(doc, root->xmlChildrenNode, 1);
  nb = my_getnbr((char *)key);
  if (!xmlStrcmp(root->name, (const xmlChar *) "winx"))
    data->sizex = nb;
  else if (!xmlStrcmp(root->name, (const xmlChar *) "winy"))
    data->sizey = nb;
  else if (!xmlStrcmp(root->name, (const xmlChar *) "antialiasing"))
    data->antialiasing = (nb < 1) ? 1 : nb;
  else if (!xmlStrcmp(root->name, (const xmlChar *) "thread"))
    data->thread = (nb < 1 || nb > MAXTHREAD) ? 8 : nb;
  else if (!xmlStrcmp(root->name, (const xmlChar *) "eye"))
    get_vector(&(data->eye), my_strdup((char *)key), VECTOR);
  else if (!xmlStrcmp(root->name, (const xmlChar *) "eye_rotation"))
    get_vector(&(data->eye_rotation), my_strdup((char *)key), ANGLE);
  else
    {
      xmlFree(key);
      return (1);
    }
  xmlFree(key);
  return (0);
}
