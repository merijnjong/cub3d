/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx_lo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:58:36 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_printx_lo(long n)
{
	char	*hex;
	int		chars;

	hex = "0123456789abcdef";
	chars = 0;
	if (n / 16 > 0)
	{
		chars += ft_printx_lo(n / 16);
	}
	chars += ft_printc(hex[n % 16]);
	return (chars);
}
