/*
** raytracer.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:13:20 2010 mickael cerisier
** Last update Sun Jun  6 21:54:46 2010 philippe berenguel
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
#include "quartic.h"

const t_func		gl_func[] = {
  {0, 0, 0},
  {1, inter_plan, normal_plan},
  {2, inter_sphere, normal_sphere},
  {3, inter_cylinder, normal_cylinder},
  {4, inter_cone, normal_cone},
  {5, inter_paraboloid, normal_paraboloid},
  {6, inter_hyperboloid, normal_cylinder},
  {7, inter_plan, normal_plan},
  {8, inter_plan, normal_plan},
  {9, inter_torus, normal_torus},
  {0, 0, 0}
};

void		sort_coef(double *k)
{
  int		i;
  int		e;
  double	mem;

  i = 0;
  while (i < 4)
    {
      e = i + 1;
      while (e < 4)
	{
	  if (k[e] < k[i] && k[e] > 0.0001)
	    {
	      mem = k[i];
	      k[i] = k[e];
	      k[e] = mem;
	    }
	  e++;
	}
      i++;
    }
}

double		in_neg_obj(double *k, t_list *list)
{
  int		i;
  int		e;
  double	mem[2];

  sort_coef(k);
  mem[0] = k[0];
  mem[1] = k[0];
  i = 0;
  while (list && mem[0] > 0.0)
    {
      e = -1;
      while (list->negative && i != e && k[i] > 0.0 && mem[0] == k[i])
	{
	  e = i;
	  if ((k[i] > list->k[0] && k[i] < list->k[1])
	      || (list->k[3] > 0.0 && k[i] > list->k[2] && k[i] < list->k[3]))
	    {
	      mem[0] = k[++i];
              mem[1] = (list->negative != 2) ? k[i] :
		(k[i] < list->k[1]) ? list->k[1] : list->k[3];
	    }
	}
      list = list->next;
    }
  return ((i == 4) ? 0.0 : mem[1]);
}

void		calc_neg(t_vect *eye, t_vect *vec, t_var *var)
{
  t_list	*list;
  t_vect	vec_obj;
  t_vect	eye_obj;

  list = var->list;
  while (list)
    {
      list->k[0] = -1.0;
      list->k[1] = -1.0;
      list->k[2] = -1.0;
      list->k[3] = -1.0;
      if (list->negative)
        {
          translation(eye, &eye_obj, &list->pos);
          rotate(&eye_obj, &eye_obj, &list->angle);
          rotate(vec, &vec_obj, &list->angle);
          gl_func[list->type].func(&eye_obj, &vec_obj, list, var);
	  sort_coef(list->k);
        }
      list = list->next;
    }
}

static void	draw_point_2(t_temp *data, t_calc *calc)
{
  data->k = data->mem;
  calc->simplevec = data->vecobj;
  calc->eye = data->eyeobj;
  data->memlist = data->l;
}

void		draw_point(t_vect *vec, t_var *var, t_color *rgb, t_vect *eye)
{
  t_temp	data;
  t_calc	calc;

  calc.vec = vec;
  calc.rgb = rgb;
  data.memlist = 0;
  data.mem = 0.0;
  data.k = -1.0;
  calc_neg(eye, vec, var);
  data.l = var->list;
  while (data.l)
    {
      if (data.l->negative == 0)
	{
	  translation(eye, &data.eyeobj, &data.l->pos);
	  rotate(&data.eyeobj, &data.eyeobj, &data.l->angle);
	  rotate(vec, &data.vecobj, &data.l->angle);
	  gl_func[data.l->type].func(&data.eyeobj, &data.vecobj, data.l, var);
	  data.mem = in_neg_obj(data.l->k, var->list);
	  if (data.mem > 0.00001 && (data.k == -1 || data.mem < data.k))
	    draw_point_2(&data, &calc);
	}
      data.l = data.l->next;
    }
  calc_color(data.k, data.memlist, &calc, var);
}
