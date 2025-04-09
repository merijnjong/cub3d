/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:56:01 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_printd(int n)
{
	int	chars;

	chars = 0;
	if (n == -2147483648)
	{
		chars += ft_prints("-2147483648");
		return (chars);
	}
	if (n < 0)
	{
		chars += ft_printc('-');
		n = -n;
	}
	if (n >= 10)
	{
		chars += ft_printd(n / 10);
	}
	chars += ft_printc('0' + n % 10);
	return (chars);
}
