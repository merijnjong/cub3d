/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:42:18 by dkros             #+#    #+#             */
/*   Updated: 2024/12/24 13:42:19 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_fprintd(int fd, int n)
{
	int	chars;

	chars = 0;
	if (n == -2147483648)
	{
		chars += ft_fprints(fd, "-2147483648");
		return (chars);
	}
	if (n < 0)
	{
		chars += ft_fprintc(fd, '-');
		n = -n;
	}
	if (n >= 10)
	{
		chars += ft_fprintd(fd, (n / 10));
	}
	chars += ft_fprintc(fd, '0' + n % 10);
	return (chars);
}

int	ft_fprints(int fd, char *s)
{
	int	chars;

	chars = 0;
	if (!s)
	{
		return (write(fd, "(null)", 6));
	}
	while (*s != '\0')
	{
		chars += ft_fprintc(fd, *s);
		s++;
	}
	return (chars);
}

int	ft_fprintc(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_fprintf2(int fd, char specifier, va_list args)
{
	int	chars;

	chars = 0;
	if (specifier == 'c')
		chars += ft_fprintc(fd, va_arg(args, int));
	else if (specifier == 's')
		chars += ft_fprints(fd, va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		chars += ft_fprintd(fd, va_arg(args, int));
	else if (specifier == 'x')
		chars += ft_fprintx_lo(fd, va_arg(args, unsigned int));
	else if (specifier == 'X')
		chars += ft_fprintx_up(fd, va_arg(args, unsigned int));
	else if (specifier == 'u')
		chars += ft_fprintu(fd, va_arg(args, unsigned int));
	else if (specifier == 'p')
		chars += ft_fprintp(fd, va_arg(args, void *));
	else if (specifier == '%')
		chars += ft_fprintc(fd, '%');
	return (chars);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	int		chars;
	va_list	args;

	chars = 0;
	if (!s)
		return (-1);
	va_start(args, s);
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			chars += ft_fprintf2(fd, *s, args);
		}
		else
			chars += write(fd, s, 1);
		s++;
	}
	va_end(args);
	return (chars);
}
