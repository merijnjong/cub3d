/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:11:34 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(char **array, int low, int high, int (*cmp)(const char *,
	const char *))
{
	char	*pivot;
	int		i;
	int		j;

	pivot = array[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (cmp(array[j], pivot) < 0)
		{
			i++;
			swap(&array[i], &array[j]);
		}
		j++;
	}
	swap(&array[i + 1], &array[high]);
	return (i + 1);
}

void	ft_qsort(char **array, int low, int high, int (*cmp)(const char *,
	const char *))
{
	int	pivot_index;

	if (low < high)
	{
		pivot_index = partition(array, low, high, cmp);
		ft_qsort(array, low, pivot_index - 1, cmp);
		ft_qsort(array, pivot_index + 1, high, cmp);
	}
}
