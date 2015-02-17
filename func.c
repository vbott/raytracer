/*
** func.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:13:50 2010 mickael cerisier
** Last update Mon Mar 15 01:13:51 2010 mickael cerisier
*/

char		is_lowalpha(char c)
{
  if (c >= 'A' && c <= 'Z')
    return (c + 32);
  return (c);
}

int		is_ok(char c)
{
  int		i;
  char		*base;

  i = 0;
  base = "0123456789abcdef";
  while (base[i] != '\0')
    if (is_lowalpha(c) == base[i++])
      return (1);
  return (0);
}
