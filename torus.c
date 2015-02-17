/*
** torus.c for raytracer in /u/all/bereng_p/cu/rendu/SVN/raytracer
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Jun  6 02:52:26 2010 philippe berenguel
** Last update Sun Jun  6 22:07:20 2010 philippe berenguel
*/

#include <stdio.h>
#include "raytracer.h"
#include "quartic.h"

static void	prepare_torus(t_torus *tor, t_vect *eye, t_vect *vec,
			      t_list *list)
{
  tor->vx2 = vec->x * vec->x;
  tor->vy2 = vec->y * vec->y;
  tor->vz2 = vec->z * vec->z;
  tor->ex2 = eye->x * eye->x;
  tor->ey2 = eye->y * eye->y;
  tor->ez2 = eye->z * eye->z;
  tor->vec2 = tor->vx2 + tor->vy2 + tor->vz2;
  tor->eye2 = tor->ex2 + tor->ey2 + tor->ez2;
  tor->vex = vec->x * eye->x;
  tor->vey = vec->y * eye->y;
  tor->vez = vec->z * eye->z;
  tor->ve = tor->vex + tor->vey + tor->vez;
  tor->er2 = list->cte * list->cte;
  tor->r2 = list->r * list->r;
}

void		normal_torus(t_vect *p, t_list *list, t_vect *n)
{
  double		k;

  k = 4 * (p->x * p->x + p->y * p->y + p->z * p->z + list->r * list->r -
	   list->cte * list->cte);
  n->x = p->x * k - 8 * list->r * list->r * p->x;
  n->y = p->y * k;
  n->z = p->z * k - 8 * list->r * list->r * p->z;
}

static void	torus_resolution(t_list *list, t_quartic *q)
{
  if (q->sol == 0)
    return ;
  else if (q->sol == 2)
    {
      list->k[0] = q->res1;
      list->k[1] = q->res2;
    }
  else if (q->sol == 4)
    {
      list->k[0] = q->res3;
      list->k[1] = q->res4;
    }
  else if (q->sol == 6)
    {
      list->k[0] = q->res1;
      list->k[1] = q->res2;
      list->k[2] = q->res3;
      list->k[3] = q->res4;
    }
}

double		inter_torus(t_vect *eye, t_vect *vec, t_list *list,
			    __attribute__((unused)) t_var *var)
{
  double	k;
  t_quartic	q;
  t_torus	tor;

  k = 0.0;
  prepare_torus(&tor, eye, vec, list);
  q.a = tor.vec2 * tor.vec2;
  q.b = 2.0 * tor.vec2 * (2.0 * tor.ve);
  q.c = 2.0 * tor.vec2 * (tor.eye2 + tor.r2 - tor.er2)
    + (2.0 * tor.ve * 2.0 * tor.ve)
    - ((4.0 * tor.r2) * (vec->x * vec->x + vec->z * vec->z));
  q.d = 2.0 * (2.0 * tor.ve) * (tor.eye2 + tor.r2 - tor.er2)
    - ((4.0 * tor.r2) * 2 * (vec->x * eye->x + vec->z * eye->z));
  q.e = (tor.eye2 + tor.r2 - tor.er2) * (tor.eye2 + tor.r2 - tor.er2)
    - ((4.0 * tor.r2) * (eye->x * eye->x + eye->z * eye->z));
  quartic_solving(&q);
  torus_resolution(list, &q);
  return (0.0);
}
