/*
** my_getnbr.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:14:09 2010 mickael cerisier
** Last update Mon Mar 15 01:14:09 2010 mickael cerisier
*/

int		my_getnbr(char *str)
{
  int		nbr;
  int		signe;

  signe = 1;
  while (*str == ' ' || *str == '+' || *str == '-')
    {
      if (*str == '-')
        signe *= -1;
      str++;
    }
  nbr = 0;
  while (*str >= '0' && *str <= '9')
    {
      nbr *= 10;
      nbr += (*str - '0');
      str++;
    }
  return (signe * nbr);
}

double		my_getfloat(char *s)
{
  int		signe;
  double	coef;
  double	nbr;

  nbr = (double)my_getnbr(s);
  if (nbr < 0)
    {
      nbr *= -1;
      signe = -1;
    }
  else
    signe = 1;
  while (*s == ' ' || *s == '+' || *s == '-' || (*s >= '0' && *s <= '9'))
    s++;
  if (*s == '.')
    {
      coef = 10;
      while (s[1] >= '0' && s[1] <= '9')
	{
	  nbr += (s[1] - '0') / coef;
	  coef *= 10;
	  s++;
	}
    }
  return (nbr * signe);
}
