/*
** rtv1.h for rtv1 in /u/all/cerisi_m/cu/rendu/c/rtv1
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon Mar 15 01:14:51 2010 mickael cerisier
** Last update Mon Mar 15 04:47:27 2010 mickael cerisier
*/

#ifndef		_RTV1_H_
# define	_RTV1_H_

# define	SIZE_X 640
# define	SIZE_Y 480
# define	BCOLOR 32
# define	RM 0x000000FF
# define	GM 0x0000FF00
# define	BM 0x00FF0000
# define	AM 0xFF000000
# define	MAXTHREAD 8
# define	TITLE "Raytracer"
# define	LISTEN 1
# define	SEND 2
# define	SHUTDOWN 3
# define	PACKET_LEN 1024
# define	PORT 7777

# define	MIN(Nb1, Nb2) (((Nb1) < (Nb2)) ? (Nb1) : (Nb2))
# define	MAX(Nb1, Nb2) (((Nb1) > (Nb2)) ? (Nb1) : (Nb2))
# define	invsqrtf(x) (1.0f / sqrtf(x))

typedef struct  s_point
{
  int           x;
  int           y;
}               t_point;

typedef struct	s_vect
{
  double	x;
  double	y;
  double	z;
}		t_vect;

typedef struct	s_calc
{
  t_vect	p;
  t_vect	n;
  t_vect	r;
  t_vect	*vec;
}		t_calc;

typedef struct	s_list
{
  int		type;
  int		color;
  t_vect	pos;
  int		r;
  t_vect	angle;
  double	bright;
  int		l_top;
  int		l_bottom;
  double	mirror;
  double	transparency;
  double	refractindex;
  struct s_list	*next;
}		t_list;

typedef struct	s_var
{
  SDL_Surface	*screen;
  t_list	*list;
  t_list	*spot;
  t_vect	oeil;
  int		realstarty;
  int		sizex;
  int		sizey;
  int		starty;
  int		endy;
  int		antialiasing;
  int		invert_n;
  int		recur_limit;
  SDL_mutex	*lock;
}		t_var;

typedef struct	s_func
{
  int		type;
  double	(*func)(t_vect *oeil, t_vect *vec, t_list *list, t_var *var);
}		t_func;

typedef struct	s_object
{
  int		type;
  char		*object;
}		t_object;

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

/* calc.c */
void	calc_n(t_vect *p, t_list *list, t_vect *n);
double	calc_shadow(t_vect *p, t_vect *l, t_list *list, t_list *obj);
double	calc_cosinus(t_vect *lobj, t_vect *n, t_list *list);

/* color.c */
void	fill_color(int *color, t_list *list, t_list *spot, double cosi);
void	recast_ray(t_var *var, t_calc *c, double coef, int *color);
int	calc_color(t_vect *vec, double k, t_list *list, t_var *var);

/* server.c */
int		listen_rt(t_var *data, int port);

/* client.c */
int		send_rt(int ac, char **av, t_var *data);
int		connect_to(char *addr);

/* create_list.c */
void		separate_list(t_var *var);

/* create_link.c */
void		create_link(t_list **list);
void		init_list(t_list *new);

/* func.c */
char	is_lowalpha(char c);
int	is_ok(char c);

/* free.c */
void	free_list(t_list *list);
void	free_win(t_var *win);

/* get_next_line.c */
char	*get_next_line(const int fd);

/* inter_object.c */
double	inter_sphere(t_vect *oeil, t_vect *vec, t_list *list, t_var *var);
double	inter_cylinder(t_vect *oeil, t_vect *vec, t_list *list, t_var *var);
double	inter_cone(t_vect *oeil, t_vect *vec, t_list *list, t_var *var);
double	inter_plan(t_vect *oeil, t_vect *vec, __attribute__((unused))
		   t_list *list, __attribute__((unused))t_var *var);

/* limit.c */
int	exceed_limit(double k, t_vect *oeil, t_vect *vec, t_list *list);
double	limit_k(double *k, t_vect *oeil, t_vect *vec, t_list *list);

/* main.c */
int	expose(void *param);
int	gere_key(int keycode, void *param);
void	fill_data_addr(t_var *var);
void	init_win(t_var *win, char *file);

/* my_getnbr.c */
int	my_getnbr(char *str);
double	my_getfloat(char *s);

/* my_getnbr_base.c */
int	my_power_rec(int nb, int power);
int	my_numberbase(char *str, int lennbr);
int	my_strlen_getbase(char *str);
int	my_getnbr_base(char *str);

/* fill_struct.c */
int		f_int(t_list *list, char *value, char *type);
int		f_float(t_list *list, char *value, char *type);
int		f_special(t_list *list, char *value, char *type);
void		init_micellanous(t_var *win);

/* my_pixel_put_to_image */
void	my_pixel_put_to_image(SDL_Surface *surface, int x, int y, int pixel);

/* my_str_to_wordtab.c */
int	my_isalphanumeric(char c, char s);
char	**my_write_tab(char *str, int taille, int lenmalloc, char c);
char	**my_str_to_wordtab(char *str, char c);

/* postprocessing.c */
void	anti_aliasing(t_var *win);

/* raytracer.c */
void	translation(t_vect *oeil, t_vect *oeil_obj, t_vect *pos);
void	calc_light(t_calc *calc, t_list *list, t_var *var, int *color);
int	calc(t_vect *vec, t_var *var);
void	fill_img(t_var *win);

/* reflexion.c */
void	calc_reflexion(t_calc *calc, t_list *obj, int *color, t_var *var);

/* rotate.c */
void	matrix_around_x(t_vect *pt, double rad);
void	matrix_around_y(t_vect *pt, double rad);
void	matrix_around_z(t_vect *pt, double rad);
void	rotate(t_vect *pt, t_vect *dest, t_vect *angle);
void	rotate_r(t_vect *pt, t_vect *dest, t_vect *angle);

/* parsing.c */
t_list	*parsing(char *path, t_var *win);

/* str.c */
int	my_strcmp(const char *s1, const char *s2);
int	my_strncmp(char *str, char *str2, int len);
size_t	my_strlen(const char *s);
void	my_putstr(const char *str);
ssize_t	xwrite(int fd, const void *buf, size_t count);

/* shutdown.c */
int		shutdown_rt(int ac, char **av);

/* thread.c */
void		start_thread(t_var *data, size_t starty, size_t endy);
void		wait_for_thread(pthread_t *thread, size_t nbclients,
				int to_free);

/* treat_client.c */
t_client     	*tryconnect_clients(int ac, char **av, size_t *nbclients,
				    int index);

/* transparency.c */
void	calc_transparency(t_calc *calc, t_list *obj, int *color, t_var *var);

/* tga.c */
void		dump_to_tga(t_var *data);

/* xmalloc.c */
void	*xmalloc(int size);

/* my_perror.c */
void	my_perror(char *str);

#endif		/* _RTV1_H_ */
