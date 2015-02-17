/*
** color.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:16:11 2010 mickael cerisier
** Last update Sun Jun  6 10:47:00 2010 philippe berenguel
*/

#include <math.h>
#if defined (WIN32)
# include <libxml/tree.h>
# include <libxml/parser.h>
#else
# include <libxml2/libxml/tree.h>
# include <libxml2/libxml/parser.h>
#endif
#include <SDL/SDL.h>
#include "raytracer.h"

extern t_func	gl_func[];

void		recast_ray(t_var *var, t_calc *calc, double coef)
{
  float		mem;
  t_color	newrgb;

  var->recur_limit++;
  newrgb.r = 0;
  newrgb.g = 0;
  newrgb.b = 0;
  if (var->recur_limit < 20)
    draw_point(&calc->r, var, &newrgb, &calc->p);
  mem = 1 - coef;
  calc->rgb->r = calc->rgb->r * mem + newrgb.r * coef;
  calc->rgb->g = calc->rgb->g * mem + newrgb.g * coef;
  calc->rgb->b = calc->rgb->b * mem + newrgb.b * coef;
  var->recur_limit--;
}

void		invert_norm(t_vect *n)
{
  n->x = -(n->x);
  n->y = -(n->y);
  n->z = -(n->z);
}

static void	wave_normal(t_list *obj, t_vect *n, t_vect *p)
{
  double	norme;

  if (obj->wave.x > 0.0 || obj->wave.y > 0.0 || obj->wave.z > 0.0)
    {
      norme = sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
      if (obj->wave.x > 0.0)
        n->x = n->x + cos(p->x / obj->wave.x) * (norme / obj->wave.x);
      if (obj->wave.y > 0.0)
        n->y = n->y + cos(p->y / obj->wave.y) * (norme / obj->wave.y);
      if (obj->wave.z > 0.0)
        n->z = n->z + cos(p->z / obj->wave.z) * (norme / obj->wave.z);
    }
}

void		calc_color(double k, t_list *list, t_calc *calc, t_var *var)
{
  if (list == 0)
    return ;
  calc->p.x = calc->eye.x + k * calc->simplevec.x;
  calc->p.y = calc->eye.y + k * calc->simplevec.y;
  calc->p.z = calc->eye.z + k * calc->simplevec.z;
  gl_func[list->type].normal(&calc->p, list, &calc->n);
  if (list->img)
    load_texture(&calc->p, &calc->n, list);
  if (list->bump)
    bump_mapping(list, calc);
  wave_normal(list, &calc->n, &calc->p);
  rotate_r(&calc->n, &calc->n, &list->angle);
  if (calc_cosinus(&calc->n, calc->vec) > 0.0)
    invert_norm(&calc->n);
  rotate_r(&calc->p, &calc->p, &list->angle);
  translation_r(&calc->p, &calc->p, &list->pos);
  calc_light(calc, list, var);
  if (list->reflection > 0.00001)
    calc_reflexion(calc, list, var);
  if (list->transparency > 0.00001)
    calc_transparency(calc, list, var);
}
