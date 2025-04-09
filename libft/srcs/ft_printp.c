/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:54:55 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_printp(void *p)
{
	unsigned long	num;
	int				chars;

	num = (unsigned long)p;
	chars = 0;
	if (num == 0)
	{
		chars += write(1, "(nil)", 5);
	}
	else
	{
		chars += write(1, "0x", 2);
		chars += ft_printp2(p);
	}
	return (chars);
}

int	ft_printp2(void *p)
{
	char			*hex;
	int				chars;
	unsigned long	num;

	hex = "0123456789abcdef";
	chars = 0;
	num = (unsigned long)p;
	if (num / 16 > 0)
	{
		chars += ft_printp2((void *)(num / 16));
	}
	chars += ft_printc(hex[num % 16]);
	return (chars);
}
