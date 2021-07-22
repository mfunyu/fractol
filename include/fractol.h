#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include "libft.h"
# include "mlx.h"
# include "debug.h"
# include "math.h"

# define LOOP 20
# define DIVERGE 4.0

# define X_MAX 2
# define X_MIN -2
# define Y_MAX 2
# define Y_MIN -2

# define WIDTH 600
# define HEIGHT 600

# define FOCUS_IN 9
# define DESTROY_NOTIFY 17

# define FOCUS_CHANGE_MASK 1L << 21
# define STRUCTURE_NOTIFY_MASK 1L << 17

# if __APPLE__
#  define ESC 65307
# else
#  define ESC 0xff1b
# endif

typedef struct s_img
{
	void		*image;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_img	image;
}				t_mlx;

/*
** puts
*/
void	put_mandelbrot(t_mlx *mlx);

/*
** hooks
*/
int		key_hook(int key, t_mlx *mlx);

/*
** exit.c
*/
void	exit_print_instruction(char *param);
int		free_exit(t_mlx *mlx);

#endif
