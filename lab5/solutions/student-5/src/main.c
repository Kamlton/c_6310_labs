#include "matrix.h"
#include "libft.h"
#include <unistd.h>

static int	read_number(void)
{
	char	buffer[12];
	int		i;
	int		sign;
	int		result;
	char	c;

	i = 0;
	sign = 1;
	result = 0;
	while (read(0, &c, 1) > 0)
	{
		if (c == '-')
			sign = -1;
		else if (c >= '0' && c <= '9')
			buffer[i++] = c;
		else if (c == ' ' || c == '\n')
			break ;
	}
	buffer[i] = '\0';
	i = 0;
	while (buffer[i] >= '0' && buffer[i] <= '9')
	{
		result = result * 10 + (buffer[i] - '0');
		i++;
	}
	return (result * sign);
}

static void	fill_matrix(matrix_t *A)
{
	int	i;
	int	j;

	if (!A)
		return ;
	i = 0;
	while (i < A->rows)
	{
		j = 0;
		while (j < A->cols)
		{
			ft_putstr_fd("Enter [", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd("][", 1);
			ft_putnbr_fd(j, 1);
			ft_putstr_fd("]: ", 1);
			A->matrix[i][j] = read_number();
			j++;
		}
		i++;
	}
}

int	main(void)
{
	matrix_t	*A;
	matrix_t	*B;
	matrix_t	*C_sum;
	matrix_t	*C_sub;
	int			rows;
	int			cols;

	ft_putendl_fd("=== Matrix Calculator (Variant 1) ===", 1);
	ft_putendl_fd("", 1);
	
	ft_putstr_fd("Enter number of rows: ", 1);
	rows = read_number();
	ft_putstr_fd("Enter number of columns: ", 1);
	cols = read_number();
	
	if (rows <= 0 || cols <= 0)
	{
		ft_putendl_fd("Error: Invalid matrix size!", 1);
		return (1);
	}
	
	A = create_matrix(rows, cols);
	B = create_matrix(rows, cols);
	
	if (!A || !B)
	{
		ft_putendl_fd("Error: Failed to allocate memory!", 1);
		remove_matrix(A);
		remove_matrix(B);
		return (1);
	}
	
	ft_putendl_fd("\n=== Fill matrix A ===", 1);
	fill_matrix(A);
	
	ft_putendl_fd("\n=== Fill matrix B ===", 1);
	fill_matrix(B);
	
	ft_putendl_fd("\n=== Matrix A ===", 1);
	print_matrix(A);
	
	ft_putendl_fd("\n=== Matrix B ===", 1);
	print_matrix(B);
	
	C_sum = sum_matrix(A, B);
	if (C_sum)
	{
		ft_putendl_fd("\n=== A + B ===", 1);
		print_matrix(C_sum);
	}
	else
	{
		ft_putendl_fd("\nError: Cannot sum matrices (different sizes?)", 1);
	}
	
	C_sub = sub_matrix(A, B);
	if (C_sub)
	{
		ft_putendl_fd("\n=== A - B ===", 1);
		print_matrix(C_sub);
	}
	else
	{
		ft_putendl_fd("\nError: Cannot subtract matrices (different sizes?)", 1);
	}
	
	remove_matrix(A);
	remove_matrix(B);
	remove_matrix(C_sum);
	remove_matrix(C_sub);
	
	return (0);
}