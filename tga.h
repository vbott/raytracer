/*
** tga.h for raytracer in /home/snap/projects/raytracer
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Fri Jun  4 12:46:29 2010 botton vivien
** Last update Tue Jun  8 09:48:05 2010 vivien botton
*/

#ifndef		_TGA_H_
# define	_TGA_H_

#pragma pack(1)
typedef struct		s_tga
{
  char			idlength;
  char			colourmaptype;
  char			datatypecode;
  short int		colourmaporigin;
  short int		colourmaplength;
  char			colourmapdepth;
  short int		x_origin;
  short int		y_origin;
  short			width;
  short			height;
  char			bitsperpixel;
  unsigned char		imagedescriptor;
}			t_tga;
#pragma pack()

#endif		/* !_TGA_H_ */
