/*
** get_vector.c for raytracer in /home/audrade/work/raytracer
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sat Jun  5 16:42:19 2010 cailleux carole
** Last update Sat Jun  5 16:42:19 2010 cailleux carole
*/

#include "raytracer.h"

void		fill_vector(int *param, t_vect **vector, char *str, int mode)
{
  if (mode == VECTOR)
    {
      if (*param == 0)
	(*vector)->x = my_getfloat(str);
      else if (*param == 1)
	(*vector)->y = my_getfloat(str);
      else if (*param == 2)
	(*vector)->z = my_getfloat(str);
      *param += 1;
    }
  else if (mode == ANGLE)
    {
      if (*param == 0)
        (*vector)->x = (my_getfloat(str) * PI) / 180.0;
      else if (*param == 1)
        (*vector)->y = (my_getfloat(str) * PI) / 180.0;
      else if (*param == 2)
	(*vector)->z = (my_getfloat(str) * PI) / 180.0;
      *param += 1;
    }
}

void		get_vector(t_vect *vector, char *str, int mode)
{
  int		i;
  int		j;
  int		count;

  if (!str)
    return ;
  i = 0;
  j = 0;
  count = 0;
  while (str[i] && count != 3)
    {
      if (str[i] == ',')
        {
          str[i] = '\0';
	  fill_vector(&count, &vector, &str[j], mode);
	  str[i] = ',';
          i++;
          while (str[i] && str[i] == ' ')
            i++;
          j = i;
        }
      i++;
    }
  fill_vector(&count, &vector, &str[j], mode);
  free(str);
}
