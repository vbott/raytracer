/*
** rotate.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:20:12 2010 mickael cerisier
** Last update Mon Mar 15 01:20:13 2010 mickael cerisier
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

void		matrix_around_x(t_vect *pt, double rad)
{
  double	cosinus;
  double	sinus;
  double	mem[2];

  cosinus = cos(rad);
  sinus = sin(rad);
  mem[0] = pt->y;
  mem[1] = pt->z;
  pt->y = cosinus * mem[0] - sinus * mem[1];
  pt->z = sinus * mem[0] + cosinus * mem[1];
}

void		matrix_around_y(t_vect *pt, double rad)
{
  double	cosinus;
  double	sinus;
  double	mem[2];

  cosinus = cos(rad);
  sinus = sin(rad);
  mem[0] = pt->x;
  mem[1] = pt->z;
  pt->x = cosinus * mem[0] + sinus * mem[1];
  pt->z = -sinus * mem[0] + cosinus * mem[1];
}

void		matrix_around_z(t_vect *pt, double rad)
{
  double	cosinus;
  double	sinus;
  double	mem[2];

  cosinus = cos(rad);
  sinus = sin(rad);
  mem[0] = pt->x;
  mem[1] = pt->y;
  pt->x = cosinus * mem[0] - sinus * mem[1];
  pt->y = sinus * mem[0] + cosinus * mem[1];
}

void		rotate(t_vect *pt, t_vect *dest, t_vect *angle)
{
  dest->x = pt->x;
  dest->y = pt->y;
  dest->z = pt->z;
  matrix_around_x(dest, angle->x);
  matrix_around_y(dest, angle->y);
  matrix_around_z(dest, angle->z);
}

void		rotate_r(t_vect *pt, t_vect *dest, t_vect *angle)
{
  dest->x = pt->x;
  dest->y = pt->y;
  dest->z = pt->z;
  matrix_around_z(dest, -angle->z);
  matrix_around_y(dest, -angle->y);
  matrix_around_x(dest, -angle->x);
}
