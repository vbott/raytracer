/*
** reflexion.cx forx raytracer in /home/shotgun/svn/raytracer
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Apr 26 10:20:43 2010 cerisier mickael
** Last update Mon Apr 26 10:20:44 2010 cerisier mickael
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

void		calc_reflexion(t_calc *calc, t_list *obj, t_var *var)
{
  double	scalar;
  t_vect	n;
  t_vect	vec;

  scalar = sqrt(calc->n.x * calc->n.x
		+ calc->n.y * calc->n.y + calc->n.z * calc->n.z);
  n.x = calc->n.x / scalar;
  n.y = calc->n.y / scalar;
  n.z = calc->n.z / scalar;
  scalar = sqrt(calc->vec->x * calc->vec->x + calc->vec->y
		* calc->vec->y + calc->vec->z * calc->vec->z);
  vec.x = calc->vec->x / scalar;
  vec.y = calc->vec->y / scalar;
  vec.z = calc->vec->z / scalar;
  scalar = n.x * vec.x + n.y * vec.y + n.z * vec.z;
  calc->r.x = -2 * n.x * scalar + vec.x;
  calc->r.y = -2 * n.y * scalar + vec.y;
  calc->r.z = -2 * n.z * scalar + vec.z;
  recast_ray(var, calc, obj->reflection);
}
