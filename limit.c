/*
** limit.c for raytracer in /home/shotgun/svn/raytracer
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Apr 26 10:20:11 2010 cerisier mickael
** Last update Mon Apr 26 10:20:12 2010 cerisier mickael
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

int		exceed_limit(double k, t_vect *eye, t_vect *vec, t_list *list)
{
  t_vect	p;

  p.z = eye->z + k * vec->z;
  if (p.z > list->l_top && list->l_top >= 0)
    return (0);
  else if (p.z < -(list->l_bottom) && -(list->l_bottom) < 0)
    return (0);
  return (1);
}

double		limit_k(double *k, t_vect *eye, t_vect *vec, t_list *list)
{
  if (k[1] < k[0])
    {
      if (exceed_limit(k[1], eye, vec, list) == 0)
        {
	  k[1] = 0.0;
          if (exceed_limit(k[0], eye, vec, list) == 0)
            k[0] = 0.0;
          return (k[0]);
        }
    }
  else
    {
      if (exceed_limit(k[0], eye, vec, list) == 0)
        {
	  k[0] = 0.0;
	  if (exceed_limit(k[1], eye, vec, list) == 0)
            k[1] = 0.0;
          return (k[1]);
        }
    }
  return (-1);
}

double		exceed_limit_disk(double *k, t_vect *eye,
				  t_vect *vec, t_list *list)
{
  t_vect	p;

  p.x = eye->x + k[0] * vec->x;
  p.y = eye->y + k[0] * vec->y;
  if ((p.x * p.x + p.y *p.y) < (list->r * list->r))
    return (k[0]);
  k[0] = 0.0;
  return (0.0);
}

double		limit_parallelogram(double *k, t_vect *eye,
				    t_vect *vec, t_list *list)
{
  t_vect	p;
  double	l[2];

  p.x = eye->x + k[0] * vec->x;
  p.y = eye->y + k[0] * vec->y;
  l[1] = list->v1.x * p.y - p.x * list->v1.y;
  l[1] /= list->v2.y * list->v1.x - list->v1.y * list->v2.x;
  l[0] = (p.x - l[1] * list->v2.x) / (list->v1.x);
  if (l[0] >= 0.0f && l[0] <= 2.0f && l[1] >= 0.0f && l[1] <= 2.0f)
    return (k[0]);
  k[0] = 0.0;
  return (0);
}

double		limit_triangle(double *k, t_vect *eye,
			       t_vect *vec, t_list *list)
{
  t_vect        p;
  double        l[2];

  p.x = eye->x + k[0] * vec->x;
  p.y = eye->y + k[0] * vec->y;
  l[1] = list->v1.x * p.y - p.x * list->v1.y;
  l[1] /= list->v2.y * list->v1.x - list->v1.y * list->v2.x;
  l[0] = (p.x - l[1] * list->v2.x) / (list->v1.x);
  if (l[0] >= 0.0f && l[0] <= 2.0f && l[1] >= 0.0f
      && l[1] <= 2.0f && l[0] + l[1] < 1)
    return (k[0]);
  k[0] = 0.0;
  return (0);
}
