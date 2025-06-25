/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:04:32 by mjong             #+#    #+#             */
/*   Updated: 2025/06/25 14:47:10 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	print_dbl_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		ft_printf("%s\n", ptr[i]);
		i++;
	}
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	exit_and_print(int code, char *message)
{
	ft_printf(message);
	exit(code);
}
