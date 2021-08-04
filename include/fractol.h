#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include "libft.h"
# include "mlx.h"
# include "math.h"
# include "X11/Xlib.h"

# define ZOOM_SPEED 30
# define IGNORE_FREQ 100

/*
** default settings
*/
# define SCREEN 600
# define LOOP 100
# define LOOP_MIN 15
# define DIVERGE 9.0
# define MIN -2.0
# define SIZE 4.0
# define C_REAL -0.3
# define C_IMAG -0.63

# define UP 4
# define DOWN 5

# define INSTRUCTIONS "usage: ./fractol fractal-name [-s size] [-r type]\n\n \
  available fractals: \n \
    Julia\n \
    Mandelbrot\n\n \
  basic user options, with defaults in [ ]:\n \
    -s --screen-size=<size> size > 0 [600]\n \
    -r --resolution=high|mid|low [mid]\n"

#  define ESC 65307
#  define RESET 114
#  define INC 65362
#  define DEC 65364
#  define INFO 105
#  define COLOR 99

# define CLEAR_SCREEN "\033[1J"
# define R 0
# define G 1
# define B 2

typedef struct s_img
{
	void		*image;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef enum e_type
{
	Invalid,
	Julia,
	Mandelbrot
}			t_type;

typedef enum e_color
{
	Gradation,
	Reverse,
	Blue,
	Monochrome,
	Num_colors
}			t_color;

typedef struct s_fractal
{
	t_type	type;
	double	x_min;
	double	y_min;
	double	size;
	double	c_real;
	double	c_imag;
	int		screen;
	int		resolution;
	int		color;
	int		loop;
}				t_fractal;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	t_img		image;
	t_fractal	*fractal;
	int			screen;
}				t_mlx;

void	init_t_fractal(t_fractal *fractal, t_mlx *mlx);

int		put_fractal(t_mlx *mlx);

int		calc_loop(t_fractal *fractal);
void	set_zoom(t_fractal *fractal, int x_fix, int y_fix, int zoom_dir);

/*
** params
*/
void	check_params(int ac, char **av);
t_type	set_fractal_type(char *param);
int		set_screen_size(t_mlx *mlx, char *param);
int		set_resolution(char *param);

int		set_color(t_fractal *fractal, int n);
char	*t_color_to_char(t_color color);

/*
** fractal
*/
int		mandelbrot_set(double x, double y, t_fractal *frac);
int		julia_set(double x, double y, t_fractal *frac);

/*
** hooks
*/
int		key_hook(int key, t_mlx *mlx);
int		key_press(int key, t_mlx *mlx);
int		mouse_hook(int button, int x, int y, t_mlx *mlx);

/*
** exit
*/
void	exit_print_instruction(char *param, char *option);
int		just_exit(void);
int		error_exit(char *str);
void	null_free(void **val);

/*
** utils
*/
int		max(int a, int b);
double	min(double a, double b);

#endif
