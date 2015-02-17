/*
** transparency.c for raytracer in /home/shotgun/svn/raytracer
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Apr 26 10:21:07 2010 cerisier mickael
** Last update Mon Apr 26 10:21:07 2010 cerisier mickael
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

void		calc_transparency(t_calc *calc, t_list *obj, t_var *var)
{
  double	norme;
  t_vect	vec;

  norme = 1.0 / sqrt(calc->vec->x * calc->vec->x
  		     + calc->vec->y * calc->vec->y
		     + calc->vec->z * calc->vec->z);
  vec.x = calc->vec->x * norme;
  vec.y = calc->vec->y * norme;
  vec.z = calc->vec->z * norme;
  calc->r.x = vec.x;
  calc->r.y = vec.y;
  calc->r.z = vec.z;
  recast_ray(var, calc, obj->transparency);
}
