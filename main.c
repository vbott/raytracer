/*
** main.c for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:12:59 2010 mickael cerisier
** Last update Mon Mar 15 04:51:15 2010 mickael cerisier
*/

#if defined (WIN32)
# include <winsock2.h>
# include <stdio.h>
# include <windows.h>
#else
# include <stdlib.h>
# include <unistd.h>
#endif
#include <fcntl.h>
#include <SDL/SDL.h>
#include "xsdl.h"
#include "raytracer.h"

int		init_data(char *file, t_var *data, int sizex, int sizey)
{
  int		flag;

  if (sizex == -1)
    {
      if (!parsing(file, data, 0))
	return (-1);
      flag = SDL_SWSURFACE | SDL_DOUBLEBUF;
      if (sizey & FULLSCREEN)
	flag |= SDL_FULLSCREEN;
      data->screen = xsdl_setvideomode(data->sizex, data->sizey, BCOLOR, flag);
      SDL_WM_SetCaption(TITLE, NULL);
    }
  else
    {
      if (!parsing(file, data, my_strlen(file)))
	return (-1);
      data->screen = SDL_CreateRGBSurface(SDL_SWSURFACE, sizex,
					  sizey, BCOLOR, RM, GM, BM, AM);
    }
  separate_list(data);
  data->realstarty = 0;
  return (0);
}

void		handle_keys(t_var *data)
{
  int		quit;
  SDL_Event	event;

  quit = 1;
  while (quit)
    {
      if (SDL_WaitEvent(&event))
	{
	  if (event.type == SDL_KEYDOWN)
	    {
	      if (event.key.keysym.sym == SDLK_ESCAPE)
		quit = 0;
	      else if (event.key.keysym.sym == 's')
		dump_to_tga(data);
	      else if (event.key.keysym.sym == 'i')
		reverse_video(data);
	      else if (event.key.keysym.sym == 'b')
		black_and_white(data);
	    }
	  if (event.type == SDL_QUIT)
	    quit = 0;
	}
    }
}

void		handle_param(int ac, char **av, int *mode, t_var *data)
{
  int		i;

  i = 1;
  *mode = 0;
  memset(data, 0, sizeof(*data));
  while (i < ac && *mode != -1 && av[i][0] == '-')
    {
      if (!my_strcmp(av[i], "-l") && !*mode)
	*mode |= LISTEN;
      else if (!my_strcmp(av[i], "-h"))
	*mode |= SEND;
      else if (!my_strcmp(av[i], "-s"))
	*mode |= SHUTDOWN;
      else if (!my_strcmp(av[i], "-f") && !(*mode & LISTEN))
	*mode |= FULLSCREEN;
      else
	*mode = -1;
      i++;
    }
  if (*mode == -1 || ac == 1)
    write(2, USAGE, 71);
}

int		main(int ac, char **av)
{
  t_var		data;
  int		mode;

  handle_param(ac, av, &mode, &data);
  if (mode == -1)
    return (EXIT_FAILURE);
  if ((ac == 2 && !mode) || (ac == 3 && mode == FULLSCREEN))
    {
      xsdl_init(SDL_INIT_VIDEO);
      if (init_data((mode & FULLSCREEN) ? av[2] : av[1],
		    &data, -1, mode & FULLSCREEN))
	return (EXIT_FAILURE);
      start_thread(&data, 0, data.sizey);
      xsdl_flip(data.screen);
      handle_keys(&data);
      SDL_Quit();
      return (EXIT_SUCCESS);
    }
  else if (mode & LISTEN)
    return (listen_rt(&data, (ac == 3) ? atoi(av[2]) : PORT));
  else if (mode & SEND && ac >= 4)
    return (send_rt(ac, av, mode, &data));
  else if (mode & SHUTDOWN && ac >= 3)
    return (shutdown_rt(ac, av));
  return (EXIT_FAILURE);
}

# if defined (WIN32)
int WINAPI	WinMain(HINSTANCE hInstance,
			HINSTANCE hPrevInstance, LPSTR lpCmdLine,
			int nCmdShow)
{
  char		**args;
  WSADATA	wsaData;
  int		res;

  res = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (res != NO_ERROR)
    printf("Error at WSAStartup()\n");
  args = my_explode(my_strdup(GetCommandLine()), ' ');
  if (res == NO_ERROR)
    {
      main(sizeof_tab(args), args);
      WSACleanup();
    }
  return (EXIT_FAILURE);
}
# endif
