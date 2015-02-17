/*
** rtv1.h for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:14:51 2010 mickael cerisier
** Last update Sun Jun  6 20:44:17 2010 philippe berenguel
*/

#ifndef			_RAYTRACER_H_
# define		_RAYTRACER_H_

# ifndef		_SDL_H
#  include <SDL/SDL.h>
# endif			/* !_SDL_H */

# ifndef		__XML_PARSER_H_
#  if defined (WIN32)
#   include <libxml/parser.h>
#  else
#   include <libxml2/libxml/parser.h>
#  endif
# endif			/* !__XML_PARSER_H__ */

# ifndef		_PTHREAD_H_
#  include <pthread.h>
# endif			/* !_PTHREAD_H_ */

# define		VECTOR 0
# define		ANGLE 1
# define		PARALLELOGRAM 8
# define		BCOLOR 24
# define		RM 0x000000FF
# define		GM 0x0000FF00
# define		BM 0x00FF0000
# define		AM 0xFF000000
# define		PI 3.14159265358979323846
# define		MAXTHREAD 256
# define		TITLE "Raytracer"
# define		USAGE "usage: ./rt [-f] [file] "\
	"[-l [port]][-s hosts ...] [-h file hosts ...]\n"
# define		DISTANCE 3000.0
# define		FULLSCREEN 1
# define		LISTEN 2
# define		SEND 4
# define		SHUTDOWN 8
# define		PACKET_LEN 1024
# define		PORT 7777

# define		MIN(Nb1, Nb2) (((Nb1) < (Nb2)) ? (Nb1) : (Nb2))
# define		MAX(Nb1, Nb2) (((Nb1) > (Nb2)) ? (Nb1) : (Nb2))

typedef struct		s_point
{
  int			x;
  int			y;
}			t_point;

typedef struct		s_vect
{
  double		x;
  double		y;
  double		z;
}			t_vect;

typedef struct		s_color
{
  float			r;
  float			g;
  float			b;
}			t_color;

typedef struct		s_calc
{
  t_color		*rgb;
  t_color		newrgb;
  t_vect		tempp;
  t_vect		templ;
  t_vect		p;
  t_vect		n;
  t_vect		r;
  t_vect		eye;
  t_vect		simplevec;
  t_vect		*vec;
}			t_calc;

typedef struct		s_list
{
  int			type;
  t_color		rgb;
  t_color		noise;
  t_vect		pos;
  int			r;
  t_vect		angle;
  double		bright;
  int			l_top;
  int			l_bottom;
  double		reflection;
  double		transparency;
  double		refract_index;
  double		bump;
  int			material;
  int			cte;
  double		k[4];
  int			negative;
  t_vect		wave;
  t_vect		v1;
  t_vect		v2;
  SDL_Surface           *img;
  struct s_list		*next;
}			t_list;

typedef struct		s_var
{
  SDL_Surface		*screen;
  t_list		*list;
  t_list		*spot;
  t_vect		eye;
  t_vect		eye_rotation;
  int			realstarty;
  size_t		thread;
  int			sizex;
  int			sizey;
  int			starty;
  int			endy;
  int			antialiasing;
  int			invert_n;
  int			recur_limit;
  char			*filename;
}			t_var;

typedef struct		s_func
{
  int			type;
  double		(*func)(t_vect *oeil, t_vect *vec, t_list *list, t_var *var);
  void			(*normal)(t_vect *p, t_list *list, t_vect *n);
}			t_func;

typedef struct		s_object
{
  int			type;
  char			*object;
}			t_object;

typedef struct		s_client
{
  int			clientfd;
  int			done;
  SDL_Surface		*screen;
  char			*file;
  char			*addr;
  size_t		sizefile;
  size_t		sizex;
  size_t		starty;
  size_t		endy;
  SDL_mutex		*lock;
  struct s_client	*list;
  struct s_client	*next;
}			t_client;

typedef struct		s_funcmat
{
  int			type;
  void			(*func)(const double lambert, t_calc *calc,
				const t_list *obj, const t_list *spot);
}			t_funcmat;

typedef struct		s_temp
{
  t_vect		eyeobj;
  t_vect		vecobj;
  double		k;
  double		mem;
  t_list		*l;
  t_list		*memlist;
}			t_temp;

void			load_texture(t_vect *p, t_vect *n, t_list *list);

/* bump_mapping.c */
int			bump_mapping(const t_list *obj, t_calc *calc);

/* calc.c */
double			calc_shadow(t_list *obj, t_list *spot,
				    t_calc *calc, t_var *var);
double			calc_cosinus(t_vect *lobj, t_vect *n);

/* color.c */
void			recast_ray(t_var *var, t_calc *c, double coef);
void			calc_color(double k, t_list *list, t_calc *calc,
				   t_var *var);

/* normal.c */
void			normal_plan(t_vect *p, t_list *list, t_vect *n);
void			normal_sphere(t_vect *p, t_list *list, t_vect *n);
void			normal_cylinder(t_vect *p, t_list *list, t_vect *n);
void			normal_cone(t_vect *p, t_list *list, t_vect *n);
void			normal_paraboloid(t_vect *p, t_list *list, t_vect *n);

/* triangles.c */
void			normal_triangle(t_vect *p, t_list *list, t_vect *n);
void			inter_triangle(t_vect *eye, t_vect *vec, t_list *list,
				       t_var *var);

/* draw.c */
void			*draw(void *arg);

/* server.c */
int			listen_rt(t_var *data, int port);

/* client.c */
int			send_rt(int ac, char **av, int mode, t_var *data);
int			connect_to(char *addr);
void			client(void *arg);

/* create_list.c */
int			sizeof_tab(char **tab);
void			separate_list(t_var *var);

/* create_link.c */
void			create_link(t_var *data);
void			init_list(t_list *new);

/* func.c */
char			is_lowalpha(char c);
int			is_ok(char c);

/* string.c */
void			my_memcpy(const void *src, void *dest, int n);
char			*my_strcat(char *s1, const char *s2);
int			my_strcmp(const char *s1, const char *s2);
size_t			my_strlen(const char *str);
char			*my_strdup(const char *str);

/* free.c */
void			free_list(t_list *list, int free_img);
void			free_win(t_var *win);
void			free_clients(t_client *clients);

/* posteffect.c */
void			reverse_video(t_var *data);
void			black_and_white(t_var *data);

/* inter_object.c */
double			inter_sphere(t_vect *oeil, t_vect *vec, t_list *list,
				     t_var *var);
double			inter_cylinder(t_vect *oeil, t_vect *vec,
				       t_list *list, t_var *var);
double			inter_cone(t_vect *oeil, t_vect *vec, t_list *list,
				   t_var *var);
double			inter_plan(t_vect *oeil, t_vect *vec,
				   __attribute__((unused))t_list *list,
				   __attribute__((unused))t_var *var);
double			inter_paraboloid(t_vect *oeil, t_vect *vec,
					 t_list *list, t_var *var);

/* inter_exotic.c */
double			inter_hyperboloid(t_vect *oeil, t_vect *vec,
					  t_list *list, t_var *var);
/* light.c */
void			calc_light(t_calc *calc, t_list *list, t_var *var);

/* limit.c */
int			exceed_limit(double k, t_vect *oeil,
				     t_vect *vec, t_list *list);
double			limit_k(double *k, t_vect *oeil,
				t_vect *vec, t_list *list);
double			exceed_limit_disk(double *k, t_vect *oeil,
					  t_vect *vec, t_list *list);
double			limit_parallelogram(double *k, t_vect *oeil,
					    t_vect *vec, t_list *list);

/* main.c */
void			handle_keys(t_var *data);
int			init_data(char *file, t_var *data, int sizex,
				  int sizey);

/* my_getnbr.c */
int			my_getnbr(char *str);
double			my_getfloat(char *s);

/* my_getnbr_base.c */
int			my_power_rec(int nb, int power);
int			my_numberbase(char *str, int lennbr);
int			my_strlen_getbase(char *str);
int			my_getnbr_base(char *str);

/* fill_struct.c */
int			f_int(t_list *list, char *value, char *type);
int			f_float(t_list *list, char *value, char *type);
int			f_special(t_list *list, char *value, char *type);
int			f_attribute(xmlNodePtr root, xmlDocPtr doc,
				    t_var *data);

/* material.c */
void			turbulence_effect(const double lambert, t_calc *calc,
					  const t_list *obj,
					  const t_list *spot);
void			marble_effect(const double lambert, t_calc *calc,
				      const t_list *obj, const t_list *spot);
void			no_effect(const double lambert, t_calc *calc,
				  const t_list *obj, const t_list *spot);
void			damier_effect(const double lambert, t_calc *calc,
				      const t_list *obj, const t_list *spot);

/* my_pixel_put_to_image */
void			my_pixel_put_to_image(SDL_Surface *surface,
					      int x, int y, int pixel);

/* my_str_to_wordtab.c */
int			my_isalphanumeric(char c, char s);
char			**my_write_tab(char *str, int taille, int lenmalloc,
				       char c);
char			**my_explode(char *str, char c);

/* perlin.c */
double			noise(double x, double y, double z);

/* postprocessing.c */
void			anti_aliasing(t_var *win);

/* pos.c */
int			send_pos(t_client *client, char *buffer);
int			get_pos(t_client *client);

/* raytracer.c */
double			in_neg_obj(double *k, t_list *list);
void			calc_neg(t_vect *eye, t_vect *vec, t_var *var);
void			draw_point(t_vect *vec, t_var *var, t_color *rgb,
				   t_vect *eye);

/* reflexion.c */
void			calc_reflexion(t_calc *calc, t_list *obj, t_var *var);

/* rotate.c */
void			matrix_around_x(t_vect *pt, double rad);
void			matrix_around_y(t_vect *pt, double rad);
void			matrix_around_z(t_vect *pt, double rad);
void			rotate(t_vect *pt, t_vect *dest, t_vect *angle);
void			rotate_r(t_vect *pt, t_vect *dest, t_vect *angle);

/* parsing.c */
t_list			*parsing(char *path, t_var *data, int len);

/* shutdown.c */
int			shutdown_rt(int ac, char **av);

/* send_conf_file.c */
char			*read_conf_file(char *path, size_t *size);
int			send_conf_file(t_client *client);
void			get_resolution(char *file, size_t size, t_var *data);

/* thread.c */
void			start_thread(t_var *data, size_t starty, size_t endy);
void			wait_for_thread(pthread_t *thread, size_t nbclients);

/* translattion */
void			translation(t_vect *oeil, t_vect *oeil_obj,
				    t_vect *pos);
void			translation_r(t_vect *eye, t_vect *eye_obj,
				      t_vect *pos);

/* transparency.c */
void			calc_transparency(t_calc *calc, t_list *obj,
					  t_var *var);
/* treat_client.c */
t_client		*tryconnect_clients(int ac, char **av,
					    size_t *nbclients, int index);
void			treat_clients(t_client *clients, size_t *sizes,
				      char *file, t_var *data);

/* tga.c */
char			*remove_ext(char *str);
void			dump_to_tga(t_var *data);

/* xmalloc.c */
void			*xmalloc(int size);

/* my_perror.c */
void			my_perror(char *str);
ssize_t			xwrite(int fd, const void *buf, size_t count);

/* get_vector.c */
void			get_vector(t_vect *vector, char *str, int mode);

#endif			/* _RAYTRACER_H_ */
