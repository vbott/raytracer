/*
** xsdl.c for raytracer in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun Jun  6 19:22:08 2010 cailleux carole
** Last update Sun Jun  6 19:22:08 2010 cailleux carole
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "raytracer.h"

SDL_Surface	*ximg_load(const char *file)
{
  SDL_Surface	*surface;

  surface = IMG_Load(file);
  if (surface == NULL)
    my_perror("IMG_Load failure.\n");
  return (surface);
}

int		xsdl_flip(SDL_Surface *screen)
{
  int		res;

  res = SDL_Flip(screen);
  if (res == -1)
    my_perror("SDL_Flip failure.\n");
  return (res);
}

int		xsdl_init(Uint32 flags)
{
  int		i;

  i = SDL_Init(flags);
  if (i == -1)
    {
      my_perror("SDL_Init failure.\n");
      exit(EXIT_FAILURE);
    }
  return (i);
}

SDL_Surface	*xsdl_setvideomode(int width, int height, int bpp,
                                   Uint32 flags)
{
  SDL_Surface	*surface;

  surface = SDL_SetVideoMode(width, height, bpp, flags);
  if (surface == NULL)
    {
      my_perror("SDL_SetVideoMode failure.\n");
      exit(EXIT_FAILURE);
    }
  return (surface);
}
