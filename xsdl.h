/*
** xsdl.h for raytracer in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun Jun  6 19:38:01 2010 cailleux carole
** Last update Sun Jun  6 19:38:01 2010 cailleux carole
*/

#ifndef		_XSDL_H_
# define	_XSDL_H_

/* xsdl.c */
SDL_Surface	*ximg_load(const char *file);
int		xsdl_flip(SDL_Surface *screen);
int		xsdl_init(Uint32 flags);
SDL_Surface	*xsdl_setvideomode(int width, int height, int bpp,
				   Uint32 flags);
#endif
