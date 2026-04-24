#include "matrix.h"
#include "libft.h"

void	print_matrix(matrix_t *A)
{
	int	i;
	int	j;

	if (!A || !A->matrix)
		return;
	i = 0;
	while (i < A->rows)
	{
		j = 0;
		while (j < A->cols)
		{
			ft_putnbr_fd(A->matrix[i][j], 1);
			if (j < A->cols - 1)
				ft_putchar_fd(' ', 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}