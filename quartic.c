/*
** quartic.c for raytracer in /u/all/bereng_p/cu/rendu/SVN/raytracer/exotic_objects
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Wed May 26 18:32:40 2010 philippe berenguel
** Last update Sun Jun  6 23:03:21 2010 philippe berenguel
*/

#include <math.h>
#include <stdio.h>
#include "raytracer.h"
#include "quartic.h"

static void	cardan_solving_part(t_quartic *q, t_cardan *card)
{
  card->sol = 0;
  card->a = 1.0;
  card->b = -q->aa;
  card->c = -4.0 * q->cc;
  card->d = q->dd;
  card->p = (card->c / card->a) -
    ((card->b * card->b) / (3.0 * (card->a * card->a)));
  card->q = ((card->b * card->b * card->b)
	     / (13.5 * (card->a * card->a * card->a))) + (card->d / card->a)
    - ((card->b * card->c) / (3.0 * (card->a * card->a)));
  q->dd = (card->q * card->q) / 4.0 + ((card->p * card->p * card->p) / 27.0);
  card->interres = (card->b / card->a / 3.0);
}

static void	cardan_delta_cases(t_quartic *q, t_cardan *card, int mode)
{
  card->sol = 3;
  if (mode == 1)
    {
      card->p = -card->p;
      card->u = (2.0 * pow((card->p / 3.0), 0.5));
      card->v = -card->q / 2.0 / pow((card->p / 3.0), 3.0 / 2.0);
      card->t = acos(card->v) / 3.0;
      q->res1 = card->u * cosf(card->t) - card->interres;
      q->res2 = card->u * cosf(card->t + 2.0 * M_PI / 3.0) - card->interres;
      q->res3 = card->u * cosf(card->t + 4.0 * M_PI / 3.0) - card->interres;
    }
  if (mode == 2)
    {
      if (card->p < 0.0)
	{
	  q->res1 = 3.0 * card->q / card->p - card->interres;
	  q->res2 = -3.0 * card->q / 2.0 / card->p - card->interres;
	  q->res3 = q->res2;
	}
      else if (card->p == 0.0)
	{
	  q->res1 = 0.0;
	  card->sol = 1;
	}
    }
}

static void	cardan_solving(t_quartic *q)
{
  t_cardan	card;

  cardan_solving_part(q, &card);
  if (card.p == 0.0 && card.q == 0.0)
    {
      q->res1 = -card.b / (3.0 * card.a);
      q->res2 = q->res1;
      q->res3 = q->res1;
      card.sol = 3;
    }
  else if (card.p == 0.0)
    {
      q->res1 = cbrt(-card.q);
      card.sol = 1;
    }
  else if (q->dd > 0.0)
    {
      card.u = cbrt(-card.q / 2.0 + sqrt(q->dd));
      q->res1 = card.u - card.p / 3.0 / card.u - (card.b / card.a / 3.0);
      card.sol = 1;
    }
  else if (q->dd < 0.0)
    cardan_delta_cases(q, &card, 1);
  else if (q->dd == 0.0)
    cardan_delta_cases(q, &card, 2);
}

static void	quartic_solver(t_quartic *q)
{
  cardan_solving(q);
  q->z = q->bb / 2.0 / (q->res1 - q->aa);
  q->sub = (q->res1 - q->aa);
  q->sqrtsub = sqrt(q->sub);
  q->interres = q->res1 * 0.5;
  q->delta = q->sub - (4.0 * (q->z * q->sqrtsub + q->interres));
  if (q->delta >= 0.0)
    {
      q->delta = sqrt(q->delta);
      q->res1 = (q->sqrtsub + q->delta) * 0.5 - q->bsub;
      q->res2 = (q->sqrtsub - q->delta) * 0.5 - q->bsub;
      q->sol = q->sol + 2;
    }
  q->delta = q->sub - (4.0 * (-q->z * q->sqrtsub + q->interres));
  if (q->delta >= 0.0)
    {
      q->delta = sqrt(q->delta);
      q->res3 = (-q->sqrtsub + q->delta) * 0.5 - q->bsub;
      q->res4 = (-q->sqrtsub - q->delta) * 0.5 - q->bsub;
      q->sol = q->sol + 4;
    }
}

void		quartic_solving(t_quartic *q)
{
  q->sol = 0;
  q->acar = q->a * q->a;
  q->bsub = q->b / 4.0 / q->a;
  q->aa = (-3.0 * q->b * q->b) / (8.0 * q->acar) + (q->c / q->a);
  q->bb = (pow((q->b / 2.0), 3) / (q->acar * q->a))
    - ((0.5 * q->b * q->c) / q->acar) + (q->d / q->a);
  q->cc = -3.0 * (q->bsub * q->bsub * q->bsub * q->bsub)
    + (q->c * (q->b / 4.0) * (q->b / 4.0) / (q->acar * q->a))
    - ((0.25 * q->b * q->d) / q->acar) + (q->e / q->a);
  q->dd = 4.0 * q->aa * q->cc - (q->bb * q->bb);
  quartic_solver(q);
}
