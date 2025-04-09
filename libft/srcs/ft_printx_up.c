/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:59:06 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_printx_up(long n)
{
	char	*hex;
	int		chars;

	hex = "0123456789ABCDEF";
	chars = 0;
	if (n / 16 > 0)
	{
		chars += ft_printx_up(n / 16);
	}
	chars += ft_printc(hex[n % 16]);
	return (chars);
}
