/*
** posteffect.c for raytracer in /home/snap/projects/raytracer
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sat Jun  5 12:13:35 2010 botton vivien
** Last update Sat Jun  5 12:13:35 2010 botton vivien
*/

#include "raytracer.h"
#include "xsdl.h"

void		reverse_video(t_var *data)
{
  unsigned char	*end;
  unsigned char	*rgb;

  end = (unsigned char *) data->screen->pixels
    + data->screen->h * data->screen->w * data->screen->format->BytesPerPixel;
  rgb = (unsigned char *) data->screen->pixels;
  while (rgb < end)
    {
      rgb[0] = 255 - rgb[0];
      rgb[1] = 255 - rgb[1];
      rgb[2] = 255 - rgb[2];
      rgb += data->screen->format->BytesPerPixel;
    }
  xsdl_flip(data->screen);
}

void		black_and_white(t_var *data)
{
  unsigned char	*end;
  unsigned char	*rgb;
  unsigned char	average;

  end = (unsigned char *) data->screen->pixels
    + data->screen->h * data->screen->w * data->screen->format->BytesPerPixel;
  rgb = (unsigned char *) data->screen->pixels;
  while (rgb < end)
    {
      average = (rgb[0] + rgb[1] + rgb[2]) / 3;
      rgb[0] = average;
      rgb[1] = average;
      rgb[2] = average;
      rgb += data->screen->format->BytesPerPixel;
    }
  xsdl_flip(data->screen);
}
