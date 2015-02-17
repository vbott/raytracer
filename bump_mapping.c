/*
** bump_mapping.c for raytracer in /home/shotgun/svn/raytracer
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Sun Jun  6 22:21:00 2010 cerisier mickael
** Last update Sun Jun  6 22:21:00 2010 cerisier mickael
*/

#include <math.h>
#include "raytracer.h"

static void	calc_bump(t_vect *calcn, t_vect *n, double temp)
{
  n->x = calcn->x * temp;
  n->y = calcn->y * temp;
  n->z = calcn->z * temp;
}

int		bump_mapping(const t_list *obj, t_calc *calc)
{
  double	temp;
  double	coef[3];
  t_vect	p;
  t_vect	n;

  temp = 1 / sqrt(calc->n.x * calc->n.x
		  + calc->n.y * calc->n.y + calc->n.z * calc->n.z);
  calc_bump(&calc->n, &n, temp);
  p.x = (calc->p.x + 214748364) * 0.1;
  p.y = (calc->p.y + 214748364) * 0.1;
  p.z = (calc->p.z + 214748364) * 0.1;
  coef[0] = noise(p.z, p.x, p.y);
  coef[1] = noise(p.y, p.z, p.x);
  coef[2] = noise(p.x, p.y, p.z);
  calc->n.x = (1.0 - obj->bump) * n.x + obj->bump * coef[0];
  calc->n.y = (1.0 - obj->bump) * n.y + obj->bump * coef[1];
  calc->n.z = (1.0 - obj->bump) * n.z + obj->bump * coef[2];
  temp = calc->n.x * calc->n.x + calc->n.y * calc->n.y + calc->n.z * calc->n.z;
  if (temp < 0.0001 && temp > -0.0001)
    return (-1);
  temp = 1.0 / sqrt(temp);
  calc->n.x *= temp;
  calc->n.y *= temp;
  calc->n.z *= temp;
  return (0);
}
