#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include "libft.h"
# include "mlx.h"
# include "debug.h"
# include "math.h"
# include "X11/Xlib.h"

# define ZOOM_SPEED 30
# define IGNORE_FREQ 3

/*
** default settings
*/
# define LOOP 30
# define DIVERGE 3.0
# define X_MAX 2
# define X_MIN -2

# define WIDTH 500
# define HEIGHT 500

# define UP 4
# define DOWN 5

# define FOCUS_IN 9
# define BUTTON_PRESS 4
# define MOTION_NOTIFY 6
# define DESTROY_NOTIFY 17

# define FOCUS_CHANGE_MASK 1L << 21
# define BUTTON_PRESS_MASK 1L << 4
# define STRUCTURE_NOTIFY_MASK 1L << 17

# if __APPLE__
#  define ESC 65307
#  define RESET 114
# else
#  define ESC 0xff1b
# endif

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

typedef struct s_fractal
{
	double	x_max;
	double	x_min;
	double	y_max;
	double	y_min;
	double	zoom;
	double		loop;
}				t_fractal;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	t_img		image;
	t_fractal	*fractal;
}				t_mlx;

void	init_t_fractal(t_fractal *fractal);
/*
** puts
*/
int		put_mandelbrot(t_mlx *mlx);

void	set_zoom(t_fractal *fractal, int x_fix, int y_fix);

int		mandelbrot_set(double x, double y, t_fractal *frac);
/*
** color
*/
int		set_gradation_color(double H);

/*
** hooks
*/
int		key_hook(int key, t_mlx *mlx);
int		mouse_hook(int button, int x, int y, t_mlx *mlx);

/*
** exit.c
*/
void	exit_print_instruction(char *param);
int		free_exit(t_mlx *mlx);
void	null_free(void **val);

#endif
