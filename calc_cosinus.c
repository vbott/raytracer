/*
** calc_cosinus.c for raytracer in /home/snap/projects/raytracer
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sun Jun  6 23:31:42 2010 botton vivien
** Last update Sun Jun  6 23:31:42 2010 botton vivien
*/

#include <math.h>
#include "raytracer.h"

double		calc_cosinus(t_vect *lobj, t_vect *n)
{
  double	cosinus;

  cosinus = n->x * lobj->x + n->y * lobj->y + n->z * lobj->z;
  cosinus /= sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
  cosinus /= sqrt(lobj->x * lobj->x + lobj->y * lobj->y + lobj->z * lobj->z);
  return (cosinus);
}
