##
## Makefile for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
## 
## Made by mickael cerisier
## Login   <cerisi_m@epitech.net>
## 
## Started on  Mon Mar 15 01:15:04 2010 mickael cerisier
## Last update Sun Jun  6 21:55:48 2010 philippe berenguel
##

NAME	= rt
SRCS	= main.c			\
	  inter_object.c		\
	  inter_exotic.c		\
	  torus.c			\
	  quartic.c			\
	  raytracer.c			\
	  shadow.c			\
	  get_vector.c			\
	  xsdl.c			\
	  draw.c			\
	  rotate.c			\
	  calc_cosinus.c		\
	  color.c			\
	  bump_mapping.c		\
	  light.c			\
	  my_pixel_put_to_image.c	\
	  create_link.c			\
	  parsing.c			\
	  translation.c			\
	  posteffect.c			\
	  material.c			\
	  perlin.c			\
	  create_list.c			\
	  limit.c			\
	  client.c			\
	  server.c			\
	  treat_client.c		\
	  shutdown.c			\
	  pos.c				\
	  normal.c			\
	  my_getnbr.c			\
	  my_perror.c			\
	  my_getnbr_base.c		\
	  my_str_to_wordtab.c		\
	  func.c			\
	  thread.c			\
	  tga.c				\
	  reflexion.c			\
	  send_conf_file.c		\
	  string.c			\
	  transparency.c		\
	  free.c			\
	  fill_struct.c			\
	  xnet.c			\
	  xnet2.c			\
	  xmalloc.c

OBJS	= $(SRCS:.c=.o)

##ifeq ($(ARG), win)
#NAME	= rt.exe
#CC	= i486-mingw32-gcc
#CFLAGS	= -I /usr/include/windows/
#LDFLAGS = -L /usr/lib/windows/ -L. -lSDL -lSDL_image -lxml2 -lpthread -lws2_32
##else 
LIBCFLAGS = $(shell sdl-config --cflags)
LIBCFLAGS += $(shell xml2-config --cflags)
CFLAGS  = -Wall -Wextra -ansi -pedantic -pipe -O2 $(LIBCFLAGS)
LDFLAGS = `sdl-config --libs` `xml2-config --libs` -lSDL -lSDL_image
##endif

RM	= rm -f

$(NAME)	: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all	: $(NAME)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

