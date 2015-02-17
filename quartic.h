/*
** quartic.h for raytracer in /u/all/bereng_p/cu/rendu/SVN/raytracer
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Jun  6 04:17:48 2010 philippe berenguel
** Last update Sun Jun  6 21:55:27 2010 philippe berenguel
*/

#ifndef		_QUARTIC_H_
# define	_QUARTIC_H_

typedef struct	s_quartic
{
  double	a;
  double	b;
  double	c;
  double	d;
  double	e;
  double	x;
  double	aa;
  double	bb;
  double	cc;
  double	dd;
  double	z;
  double	u;
  double	res1;
  double	res2;
  double	res3;
  double	res4;
  double	delta;
  double	sub;
  double	bsub;
  double	sqrtsub;
  double	interres;
  double	acar;
  int		sol;
}		t_quartic;

typedef struct	s_cardan
{
  double	a;
  double	b;
  double	c;
  double	d;
  double	p;
  double	q;
  double	x;
  double	u;
  double	v;
  double	t;
  double	interres;
  int		sol;
}		t_cardan;

typedef struct	s_torus
{
  double	vx2;
  double	vy2;
  double	vz2;
  double	ex2;
  double	ey2;
  double	ez2;
  double	vec2;
  double	eye2;
  double	vex;
  double	vey;
  double	vez;
  double	ve;
  double	er2;
  double	r2;
}		t_torus;

/* torus.c */
void		normal_torus(t_vect *p, t_list *list, t_vect *n);
double		inter_torus(t_vect *eye, t_vect *vec, t_list *list,
			    t_var *var);

/* quartic.c */
void		quartic_solving(t_quartic *q);

#endif		/* _QUARTIC_H_ */
