/*
** material.c for raytracer in /home/shotgun/svn/raytracer/massal
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Tue Jun  1 17:42:10 2010 cerisier mickael
** Last update Tue Jun  1 17:42:10 2010 cerisier mickael
*/

#include <math.h>
#include "raytracer.h"

void		turbulence_effect(const double lambert, t_calc *calc,
				  const t_list *obj, const t_list *spot)
{
  int		level;
  double	noisecoef;
  double	bright;

  level = 1;
  noisecoef = 0.0;
  while (level < 10)
    {
      noisecoef += (1.0 / level)
	* fabs((noise(level * 0.1 * (calc->p.z + 214748364),
		      level * 0.1 * (calc->p.x + 214748364),
		      level * 0.1 * (calc->p.y + 214748364))));
      level++;
    }
  bright = 1.0 - obj->bright;
  calc->rgb->r += lambert * ((spot->rgb.r * obj->bright)
			     + ((noisecoef * obj->rgb.r + (1.0 - noisecoef)
				 * obj->noise.r) * bright));
  calc->rgb->g += lambert * ((spot->rgb.g * obj->bright)
			     + ((noisecoef * obj->rgb.g + (1.0 - noisecoef)
				 * obj->noise.g) * bright));
  calc->rgb->b += lambert * ((spot->rgb.b * obj->bright)
			     + ((noisecoef * obj->rgb.b + (1.0 - noisecoef)
				 * obj->noise.b) * bright));
}

void		marble_effect(const double lambert, t_calc *calc,
			      const t_list *obj, const t_list *spot)
{
  int		level;
  double	noisecoef;
  double	bright;

  level = 1;
  noisecoef = 0.0f;
  while (level < 10)
    {
      noisecoef += (1.0 / level)
	* fabs((noise(level * 0.05 * (calc->p.z + 214748364),
		      level * 0.05 * (calc->p.x + 214748364),
		      level * 0.05 * (calc->p.y + 214748364))));
      level++;
    }
  noisecoef = 0.5 * sin((calc->p.x + calc->p.y) * 0.05 + noisecoef) + 0.5;
  bright = 1.0 - obj->bright;
  calc->rgb->r += lambert * ((spot->rgb.r * obj->bright)
			     + ((noisecoef * obj->rgb.r + (1.0 - noisecoef)
				 * obj->noise.r) * bright));
  calc->rgb->g += lambert * ((spot->rgb.g * obj->bright)
			     + ((noisecoef * obj->rgb.g + (1.0 - noisecoef)
				 * obj->noise.g) * bright));
  calc->rgb->b += lambert * ((spot->rgb.b * obj->bright)
			     + ((noisecoef * obj->rgb.b + (1.0 - noisecoef)
				 * obj->noise.b) * bright));
}

void		damier_effect(const double lambert, t_calc *calc,
			      const t_list *obj, const t_list *spot)
{
  float		bright;
  int	 	modx;
  int		mody;

  bright = 1.0f - obj->bright;
  modx = (calc->p.x < 0) ? (int) (-calc->p.x + 50) % 100 : (int)calc->p.x % 100;
  mody = (calc->p.y < 0) ? (int) (-calc->p.y + 50) % 100 : (int)calc->p.y % 100;
  if ((modx >= 50 && mody >= 50) || (modx < 50 && mody < 50))
    {
      calc->rgb->r += lambert *
	(obj->bright * spot->rgb.r + bright * obj->rgb.r);
      calc->rgb->g += lambert *
	(obj->bright * spot->rgb.g + bright * obj->rgb.g);
      calc->rgb->b += lambert *
	(obj->bright * spot->rgb.b + bright * obj->rgb.b);
    }
  else
    {
      calc->rgb->r += lambert *
	(obj->bright * spot->rgb.r + bright * obj->noise.r);
      calc->rgb->g += lambert *
	(obj->bright * spot->rgb.g + bright * obj->noise.g);
      calc->rgb->b += lambert *
	(obj->bright * spot->rgb.b + bright * obj->noise.b);
    }
}

void		no_effect(const double lambert, t_calc *calc,
			  const t_list *obj, const t_list *spot)
{
  float		bright;

  bright = 1.0f - obj->bright;
  calc->rgb->r += lambert * (obj->bright * spot->rgb.r + bright * obj->rgb.r);
  calc->rgb->g += lambert * (obj->bright * spot->rgb.g + bright * obj->rgb.g);
  calc->rgb->b += lambert * (obj->bright * spot->rgb.b + bright * obj->rgb.b);
}
