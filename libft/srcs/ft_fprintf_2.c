/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:42:44 by dkros             #+#    #+#             */
/*   Updated: 2024/12/24 13:59:01 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_fprintp2(int fd, void *p)
{
	char			*hex;
	int				chars;
	unsigned long	num;

	hex = "0123456789abcdef";
	chars = 0;
	num = (unsigned long)p;
	if (num / 16 > 0)
	{
		chars += ft_fprintp2(fd, (void *)(num / 16));
	}
	chars += ft_fprintc(fd, hex[num % 16]);
	return (chars);
}

int	ft_fprintp(int fd, void *p)
{
	unsigned long	num;
	int				chars;

	num = (unsigned long)p;
	chars = 0;
	if (num == 0)
	{
		chars += write(fd, "(nil)", 5);
	}
	else
	{
		chars += write(fd, "0x", 2);
		chars += ft_fprintp2(fd, p);
	}
	return (chars);
}

int	ft_fprintu(int fd, unsigned int n)
{
	int	chars;

	chars = 0;
	if (n >= 10)
	{
		chars += ft_fprintd(fd, (n / 10));
	}
	chars += ft_fprintc(fd, '0' + n % 10);
	return (chars);
}

int	ft_fprintx_up(int fd, long n)
{
	char	*hex;
	int		chars;

	hex = "0123456789ABCDEF";
	chars = 0;
	if (n / 16 > 0)
	{
		chars += ft_fprintx_up(fd, (n / 16));
	}
	chars += ft_fprintc(fd, hex[n % 16]);
	return (chars);
}

int	ft_fprintx_lo(int fd, long n)
{
	char	*hex;
	int		chars;

	hex = "0123456789abcdef";
	chars = 0;
	if (n / 16 > 0)
	{
		chars += ft_fprintx_lo(fd, (n / 16));
	}
	chars += ft_fprintc(fd, hex[n % 16]);
	return (chars);
}
