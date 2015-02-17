/*
** inter_exotic.c for  in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Fri Jun  4 20:40:20 2010 cailleux carole
** Last update Fri Jun  4 20:40:20 2010 cailleux carole
*/

#include <SDL/SDL.h>
#if defined (WIN32)
# include <libxml/tree.h>
# include <libxml/parser.h>
#else
# include <libxml2/libxml/tree.h>
# include <libxml2/libxml/parser.h>
#endif
#include <math.h>
#include "raytracer.h"

double		inter_hyperboloid(t_vect *eye, t_vect *vec,
				  t_list *list, t_var *var)
{
  double	delta;
  t_vect	arg;
  double	ret_val;

  arg.x = vec->x * vec->x + vec->y * vec->y - vec->z * vec->z * list->r;
  arg.y = 2 * (eye->x * vec->x + eye->y * vec->y - eye->z * vec->z * list->r);
  arg.z = eye->x * eye->x + eye->y * eye->y
    - eye->z * eye->z * list->r - list->cte;
  delta = arg.y * arg.y - 4 * arg.x * arg.z;
  if (delta < 0.0)
    return (0.0);
  list->k[0] = (-arg.y + sqrt(delta)) / (2 * arg.x);
  list->k[1] = (-arg.y - sqrt(delta)) / (2 * arg.x);
  if (var)
    if ((ret_val = limit_k(list->k, eye, vec, list)) != -1)
      return (ret_val);
  if ((list->k[0] < list->k[1] || list->k[1] < -0.001) && list->k[0] > 0.001)
    return (list->k[0]);
  if ((list->k[1] < list->k[0] || list->k[0] < -0.001) && list->k[1] > 0.001)
    {
      if (var)
        var->invert_n = 1;
      return (list->k[1]);
    }
  return (0.0);
}
