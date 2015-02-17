/*
** translation.c for raytracer in /home/shotgun/svn/raytracer
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Sun Jun  6 20:47:18 2010 cerisier mickael
** Last update Sun Jun  6 20:47:18 2010 cerisier mickael
*/

#include "raytracer.h"

void		translation(t_vect *eye, t_vect *eye_obj, t_vect *pos)
{
  eye_obj->x = eye->x - pos->x;
  eye_obj->y = eye->y - pos->y;
  eye_obj->z = eye->z - pos->z;
}

void		translation_r(t_vect *eye, t_vect *eye_obj, t_vect *pos)
{
  eye_obj->x = eye->x + pos->x;
  eye_obj->y = eye->y + pos->y;
  eye_obj->z = eye->z + pos->z;
}
