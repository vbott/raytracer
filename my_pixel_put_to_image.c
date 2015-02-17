/*
** my_pixel_put_to_image.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:15:36 2010 mickael cerisier
** Last update Sun Jun  6 23:04:13 2010 philippe berenguel
*/

#include <SDL/SDL.h>
#if defined (WIN32)
# include <libxml/tree.h>
# include <libxml/parser.h>
#else
# include <libxml2/libxml/tree.h>
# include <libxml2/libxml/parser.h>
#endif
#include "raytracer.h"

void		my_pixel_put_to_image(SDL_Surface *surface, int x,
				      int y, int pixel)
{
  int		bpp;
  Uint8		*p;

  bpp = surface->format->BytesPerPixel;
  p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  if (bpp == 4)
    *(Uint32 *)p = pixel;
  else if (bpp == 3)
    {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
  else if (bpp == 3 && SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    }
  else if (bpp == 2)
    *(Uint16 *)p = pixel;
  else if (bpp == 1)
    *p = pixel;
}
