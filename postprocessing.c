/*
** postprocessing.c for raytracer in /home/shotgun/svn/raytracer
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Apr 26 10:21:28 2010 cerisier mickael
** Last update Sun Jun  6 23:03:52 2010 philippe berenguel
*/

#include <SDL/SDL.h>
#if defined (WIN32)
#include <libxml/tree.h>
#include <libxml/parser.h>
#else
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#endif
#include "raytracer.h"

void		sum_colors(SDL_Surface *a, int color[3], int x, int y)
{
  int		nx;
  int		ny;
  Uint8		*pos;

  nx = 0;
  while (nx < SAMPLING)
    {
      ny = 0;
      while (ny < SAMPLING)
	{
	  pos = (Uint8 *)a->pixels + (y + ny) * a->pitch
	    + (x + nx) * a->format->BytesPerPixel;
	  color[0] += pos[0];
	  color[1] += pos[1];
	  color[2] += pos[2];
	  ny++;
	}
      nx++;
    }
  color[0] /= FACTOR;
  color[1] /= FACTOR;
  color[2] /= FACTOR;
  color[0] = color[0] | (color[1] << 8) | (color[2] << 16);
}

void		anti_aliasing(t_var *win)
{
  int		x;
  int		y;
  int		color[3];

  y = 0;
  while (y < PRESAMPLED_Y)
    {
      x = 0;
      while (x < PRESAMPLED_X)
	{
	  color[0] = 0;
	  color[1] = 0;
	  color[2] = 0;
	  sum_colors(win->presample, color, x, y);
	  my_pixel_put_to_image(win->screen, x / SAMPLING,
				y / SAMPLING, color[0]);
	  x += SAMPLING;
	}
      y += SAMPLING;
    }
}
