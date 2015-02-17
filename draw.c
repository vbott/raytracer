/*
** draw.c for raytracer in /home/snap/projects/raytracer
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Thu Jun  3 19:30:10 2010 botton vivien
** Last update Sun Jun  6 23:05:43 2010 philippe berenguel
*/

#include <SDL/SDL.h>
#include "raytracer.h"

static void	launch_radius(t_vect *vec, t_color *res, t_var *data)
{
  t_color	rgb;
  t_vect	tvec;

  memset(&rgb, 0, sizeof(rgb));
  rotate(vec, &tvec, &(data->eye_rotation));
  data->recur_limit = 0;
  draw_point(&tvec, data, &rgb, &(data->eye));
  res->r += rgb.r;
  res->g += rgb.g;
  res->b += rgb.b;
}

static void	init_alias(int *alias, float *coefalias,
			   t_color *res, t_var *data)
{
  *alias = data->antialiasing;
  *coefalias = 1.0f / *alias;
  *alias *= *alias;
  memset(res, 0, sizeof(*res));
}

static int	antialiasing(t_vect *vec, t_point *pt, t_var *data)
{
  float		xa;
  float		ya;
  int		alias;
  float		coefalias;
  t_color	res;

  init_alias(&alias, &coefalias, &res, data);
  xa = 0;
  while (xa < 1)
    {
      ya = 0;
      vec->y = data->sizex / 2 - (pt->x + xa);
      while (ya < 1)
	{
	  vec->z = data->sizey / 2 - (pt->y + ya);
	  launch_radius(vec, &res, data);
	  ya += coefalias;
	}
      xa += coefalias;
    }
  res.r = (res.r > alias) ? 1 : res.r / alias;
  res.g = (res.g > alias) ? 1 : res.g / alias;
  res.b = (res.b > alias) ? 1 : res.b / alias;
  return ((int) (res.b * 255)
	  | (int) (res.g * 255) << 8 | (int) (res.r * 255) << 16);
}

void		*draw(void *arg)
{
  int		color;
  t_point	pt;
  t_vect	vec;
  t_var		*win;

  win = (t_var*)arg;
  pt.y = win->starty;
  vec.x = win->sizex * 2;
  while (pt.y < win->endy)
    {
      pt.x = 0;
      while (pt.x < win->sizex)
        {
	  color = antialiasing(&vec, &pt, win);
	  my_pixel_put_to_image(win->screen, pt.x,
				pt.y - win->realstarty, color);
          pt.x++;
        }
      pt.y++;
    }
  free_win(win);
  return (EXIT_SUCCESS);
}
