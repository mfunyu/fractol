#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include "libft.h"
# include "mlx.h"
# include "debug.h"
# include "math.h"
# include "X11/Xlib.h"

# define ZOOM_SPEED 30
# define IGNORE_FREQ 100

/*
** default settings
*/
# define SCREEN 800
# define LOOP 100
# define DIVERGE 9.0
# define MIN -2.0
# define SIZE 4.0
# define C_REAL -0.3
# define C_IMAG -0.63

# define UP 4
# define DOWN 5

# if __APPLE__
#  define ESC 65307
#  define RESET 114
#  define INC 65362
#  define DEC 65364
#  define RANGE 119
# else
#  define ESC 0xff1b
# endif

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
	Julia,
	Mandelbrot
}			t_type;

typedef struct s_fractal
{
	t_type	type;
	double	x_min;
	double	y_min;
	double	size;
	double	c_real;
	double	c_imag;
	int		screen;
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

void	init_t_fractal(t_fractal *fractal, t_type type, t_mlx *mlx);
/*
** puts
*/
int		put_fractal(t_mlx *mlx);

void	set_zoom(t_fractal *fractal, int x_fix, int y_fix, int zoom_dir);

int		mandelbrot_set(double x, double y, t_fractal *frac);
int		julia_set(double x, double y, t_fractal *frac);
/*
** color
*/
int		set_gradation_color(double H);

/*
** hooks
*/
int		key_hook(int key, t_mlx *mlx);
int		key_press(int key, t_mlx *mlx);
int		mouse_hook(int button, int x, int y, t_mlx *mlx);

/*
** exit.c
*/
void	exit_print_instruction(char *param);
int		free_exit(t_mlx *mlx);
int		error_exit(char *str);
void	null_free(void **val);

/*
** utils
*/
int		max(int a, int b);
double	min(double a, double b);

#endif
