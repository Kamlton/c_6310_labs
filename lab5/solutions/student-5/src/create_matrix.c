#include "matrix.h"
#include "libft.h"

matrix_t	*create_matrix(int rows, int cols)
{
	matrix_t	*new;
	int			i;

	if (rows <= 0 || cols <= 0)
		return (NULL);
	new = (matrix_t *)malloc(sizeof(matrix_t));
	if (!new)
		return (NULL);
	new->matrix = (int **)malloc(sizeof(int *) * rows);
	if (!new->matrix)
	{
		free(new);
		return (NULL);
	}
	i = 0;
	while (i < rows)
	{
		new->matrix[i] = (int *)malloc(sizeof(int) * cols);
		if (!new->matrix[i])
		{
			while (--i >= 0)
				free(new->matrix[i]);
			free(new->matrix);
			free(new);
			return (NULL);
		}
		i++;
	}
	new->rows = rows;
	new->cols = cols;
	return (new);
}