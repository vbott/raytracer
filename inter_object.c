/*
** inter_object.c for raytracer in /home/snap/projects/raytracer
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sun Jun  6 08:16:52 2010 botton vivien
** Last update Sun Jun  6 08:16:52 2010 botton vivien
*/

#include <SDL/SDL.h>
#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include <math.h>
#include "raytracer.h"

double		inter_sphere(t_vect *eye, t_vect *vec,
			     t_list *list, t_var *var)
{
  double	delta;
  t_vect	param;
  double	ret_val;

  param.x = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
  param.y = 2 * (eye->x * vec->x + eye->y * vec->y + eye->z * vec->z);
  param.z = eye->x * eye->x + eye->y * eye->y
    + eye->z * eye->z - list->r * list->r;
  delta = param.y * param.y - 4 * param.x * param.z;
  if (delta < 0.0)
    return (0.0);
  list->k[0] = (-param.y + sqrt(delta)) / (2 * param.x);
  list->k[1] = (-param.y - sqrt(delta)) / (2 * param.x);
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

double		inter_cylinder(t_vect *eye, t_vect *vec,
			       t_list *list, t_var *var)
{
  double	delta;
  t_vect	param;
  double	ret_val;

  param.x = vec->x * vec->x + vec->y * vec->y;
  param.y = 2 * (eye->x * vec->x + eye->y * vec->y);
  param.z = eye->x * eye->x + eye->y * eye->y - list->r * list->r;
  delta = param.y * param.y - 4.0 * param.x * param.z;
  if (delta < 0.0)
    return (0.0);
  list->k[0] = (-param.y + sqrt(delta)) / (2.0 * param.x);
  list->k[1] = (-param.y - sqrt(delta)) / (2.0 * param.x);
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

double		inter_cone(t_vect *eye, t_vect *vec,
			   t_list *list, t_var *var)
{
  double	delta;
  t_vect	param;
  double	ret_val;

  param.x = vec->x * vec->x + vec->y * vec->y - vec->z * vec->z * list->r;
  param.y = 2 * (eye->x * vec->x + eye->y * vec->y
		 - eye->z * vec->z * list->r);
  param.z = eye->x * eye->x + eye->y * eye->y - eye->z * eye->z * list->r;
  delta = param.y * param.y - 4 * param.x * param.z;
  if (delta < 0.0)
    return (0.0);
  list->k[0] = (-param.y + sqrt(delta)) / (2 * param.x);
  list->k[1] = (-param.y - sqrt(delta)) / (2 * param.x);
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

double		inter_plan(t_vect *eye, t_vect *vec, __attribute__((unused))
			   t_list *list, __attribute__((unused))t_var *var)
{
  double	ret_val;

  if (vec->z > 0.00001 || vec->z < -0.00001)
    {
      list->k[0] = -(eye->z / vec->z);
      if (list->type == 7 && list->r > 0)
	{
	  if ((ret_val = exceed_limit_disk(list->k, eye, vec, list)) != -1)
	    return (ret_val);
	}
      else if (list->type == 8)
	{
	  if ((ret_val = limit_parallelogram(list->k, eye, vec, list)) != -1)
	    return (ret_val);
	}
      if (list->k[0] > 0.00001)
        return (list->k[0]);
    }
  return (0.0);
}

double		inter_paraboloid(t_vect *eye, t_vect *vec, t_list *list,
				      t_var *var)
{
  double	delta;
  t_vect	param;
  int		ret_val;

  param.x = vec->x * vec->x + vec->y * vec->y;
  param.y = 2 * (eye->x * vec->x + eye->y * vec->y) - list->cte * vec->z;
  param.z = eye->x * eye->x + eye->y * eye->y - list->cte * eye->z;
  delta = param.y * param.y - 4 * param.x * param.z;
  if (delta < 0.0)
    return (0.0);
  list->k[0] = (-param.y + sqrt(delta)) / (2 * param.x);
  list->k[1] = (-param.y - sqrt(delta)) / (2 * param.x);
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
