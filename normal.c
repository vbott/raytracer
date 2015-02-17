/*
** normal.c for raytracer in /home/snap/projects/raytracer
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Fri Jun  4 12:12:11 2010 botton vivien
** Last update Fri Jun  4 12:12:11 2010 botton vivien
*/

#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include "raytracer.h"

void		normal_plan(t_vect *p, t_list *list, t_vect *n)
{
  (void) p;
  (void) list;
  n->x = 0;
  n->y = 0;
  n->z = 100;
}

void		normal_sphere(t_vect *p, t_list *list, t_vect *n)
{
  (void) list;
  n->x = p->x;
  n->y = p->y;
  n->z = p->z;
}

void		normal_cylinder(t_vect *p, t_list *list, t_vect *n)
{
  (void) list;
  n->x = p->x;
  n->y = p->y;
  n->z = 0;
}

void		normal_cone(t_vect *p, t_list *list, t_vect *n)
{
  n->x = p->x;
  n->y = p->y;
  n->z = -list->r * p->z;
}

void		normal_paraboloid(t_vect *p, t_list *list, t_vect *n)
{
  n->x = p->x;
  n->y = p->y;
  n->z = -list->cte;
}
