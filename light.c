/*
** light.c for raytracer in /home/shotgun/svn/raytracer
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Sun Jun  6 20:54:50 2010 cerisier mickael
** Last update Sun Jun  6 20:54:50 2010 cerisier mickael
*/

#include <math.h>
#include "raytracer.h"

static const t_funcmat	gl_effect[] = {
  {0, no_effect},
  {1, turbulence_effect},
  {2, marble_effect},
  {3, damier_effect},
  {0, NULL}
};

void		load_texture(t_vect *p, t_vect *n, t_list *list)
{
  unsigned char	*rgb;
  int		x;
  int		y;
  double	norme;

  if (list->type != 1)
    {
      norme = sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
      x = (asin(n->x / norme) / PI + 0.5) * list->img->w;
      y = (asin(n->y / norme) / PI + 0.5) * list->img->h;
    }
  else
    {
      x = ((int) -p->y) % list->img->w;
      y = ((int) -p->x) % list->img->h;
    }
  if (x < 0)
    x += list->img->w;
  if (y < 0)
    y += list->img->h;
  rgb = (unsigned char *) list->img->pixels
    + x * list->img->format->BytesPerPixel + y * list->img->pitch;
  list->rgb.r = rgb[2] / 255.0f;
  list->rgb.g = rgb[1] / 255.0f;
  list->rgb.b = rgb[0] / 255.0f;
}

static void	average_color_spot(t_color *rgb, int i)
{
  rgb->r /= i;
  rgb->g /= i;
  rgb->b /= i;
}

static void	mult_rgb(t_calc *calc)
{
  calc->rgb->r *= calc->newrgb.r;
  calc->rgb->g *= calc->newrgb.g;
  calc->rgb->b *= calc->newrgb.b;
}

void		calc_light(t_calc *calc, t_list *list, t_var *var)
{
  int		i;
  t_vect	lobj;
  double	cosinus;
  t_list	*spot;

  i = (var->spot) ? 0 : 1;
  spot = var->spot;
  while (spot)
    {
      translation(&spot->pos, &lobj, &calc->p);
      cosinus = calc_cosinus(&lobj, &calc->n);
      if (cosinus > 0)
	{
	  calc->templ = lobj;
	  cosinus *= calc_shadow(list, spot, calc, var);
	  gl_effect[list->material].func(cosinus * spot->bright,
					 calc, list, spot);
	  mult_rgb(calc);
	}
      spot = spot->next;
      i++;
    }
  average_color_spot(calc->rgb, i);
}
