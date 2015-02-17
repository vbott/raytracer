/*
** thread.c for raytracer in /home/snap/projects/raytracer
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Thu Jun 17 13:15:28 2010 botton vivien
** Last update Thu Jun 17 13:15:28 2010 botton vivien
*/

#include <SDL/SDL.h>
#include <pthread.h>
#include <time.h>
#include "raytracer.h"

t_list			*cpy_list(t_list *list)
{
  t_list		*res;
  t_list		*next;

  next = NULL;
  while (list)
    {
      res = xmalloc(sizeof(*res));
      my_memcpy(list, res, sizeof(*res));
      res->next = next;
      next = res;
      list = list->next;
    }
  return (next);
}

t_var			*cpy_data(t_var *data, size_t starty)
{
  t_var			*res;
  SDL_Surface		*cpy;

  res = xmalloc(sizeof(*res));
  my_memcpy(data, res, sizeof(*res));
  res->starty = starty;
  res->list = cpy_list(data->list);
  res->spot = cpy_list(data->spot);
  cpy = xmalloc(sizeof(*cpy));
  my_memcpy(data->screen, cpy, sizeof(*(res->screen)));
  res->screen = cpy;
  return (res);
}

void		wait_for_thread(pthread_t *thread, size_t nbclients)
{
  size_t	i;

  i = 0;
  while (i < nbclients)
    {
      pthread_join(thread[i], NULL);
      i++;
    }
  free(thread);
}

void			wait_threads(pthread_t *thread, t_var *data)
{
  wait_for_thread(thread, data->thread);
  free_list(data->list, 1);
  free_list(data->spot, 1);
}

void			start_thread(t_var *data, size_t starty, size_t endy)
{
  size_t		i;
  pthread_t		*thread;
  t_var			*cpy;
  size_t		size;
  size_t		threadpos;
  size_t		mod;

  i = 0;
  size = starty;
  thread = xmalloc(data->thread * sizeof(*thread));
  threadpos = (endy - starty) / data->thread;
  mod = (endy - starty) % data->thread;
  while (i < data->thread)
    {
      cpy = cpy_data(data, size);
      cpy->endy  = size + threadpos;
      if (i == 0)
	cpy->endy += mod;
      pthread_create(&thread[i], NULL, draw, cpy);
      size += threadpos;
      if (i == 0)
	size += mod;
      i++;
    }
  wait_threads(thread, data);
}
