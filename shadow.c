/*
** calc.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:13:10 2010 mickael cerisier
** Last update Sun Jun  6 23:34:06 2010 mickael cerisier
*/

#include <math.h>
#include <SDL/SDL.h>
#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include "raytracer.h"

extern t_func	gl_func[];

void		mult_color(t_calc *calc, t_list *list, double *coef)
{
  t_vect	n;

  *coef *= list->transparency;
  if (list->img && list->transparency)
    {
      gl_func[list->type].normal(&calc->tempp, list, &n);
      load_texture(&calc->tempp, &n, list);
    }
  calc->newrgb.r -= (1.0f - list->rgb.r) * *coef;
  calc->newrgb.g -= (1.0f - list->rgb.g) * *coef;
  calc->newrgb.b -= (1.0f - list->rgb.b) * *coef;
  if (calc->newrgb.r < 0)
    calc->newrgb.r = 0.0f;
  if (calc->newrgb.g < 0)
    calc->newrgb.g = 0.0f;
  if (calc->newrgb.b < 0)
    calc->newrgb.b = 0.0f;
}

void		find_hitpoint(t_vect *eye_obj, t_vect *l, double k, t_vect *p)
{
  p->x = eye_obj->x + k * l->x;
  p->y = eye_obj->y + k * l->y;
  p->z = eye_obj->z + k * l->z;
}

void		find_vec(t_calc *calc, t_vect *eye_obj,
			 t_vect *test, t_list *list)
{
  translation(&calc->p, eye_obj, &list->pos);
  rotate(eye_obj, eye_obj, &list->angle);
  rotate(&calc->templ, test, &list->angle);
}

void		init_shadow(double *coef, t_calc *calc,
			    t_var *var, t_list *spot)
{
  *coef = 1.0;
  calc->newrgb = spot->rgb;
  calc_neg(&calc->p, &calc->templ, var);
}

double		calc_shadow(t_list *obj, t_list *spot,
			    t_calc *calc, t_var *var)
{
  double	mem;
  t_vect	eye_obj;
  t_vect	test;
  double	coef;
  t_list	*list;

  init_shadow(&coef, calc, var, spot);
  list = var->list;
  while (list && coef)
    {
      if (list != obj && !list->negative)
      	{
	  find_vec(calc, &eye_obj, &test, list);
	  gl_func[list->type].func(&eye_obj, &test, list, 0);
      	  if ((mem = in_neg_obj(list->k, var->list)) > 0.00001 && mem < 1.0)
	    {
	      if (list->img && list->transparency)
		find_hitpoint(&eye_obj, &test, mem, &calc->tempp);
	      mult_color(calc, list, &coef);
	    }
      	}
      list = list->next;
    }
  return (coef);
}
