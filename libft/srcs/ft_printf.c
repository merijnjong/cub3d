/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:52:07 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_printf2(char specifier, va_list args)
{
	int	chars;

	chars = 0;
	if (specifier == 'c')
		chars += ft_printc(va_arg(args, int));
	else if (specifier == 's')
		chars += ft_prints(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		chars += ft_printd(va_arg(args, int));
	else if (specifier == 'x')
		chars += ft_printx_lo(va_arg(args, unsigned int));
	else if (specifier == 'X')
		chars += ft_printx_up(va_arg(args, unsigned int));
	else if (specifier == 'u')
		chars += ft_printu(va_arg(args, unsigned int));
	else if (specifier == 'p')
		chars += ft_printp(va_arg(args, void *));
	else if (specifier == '%')
		chars += ft_printc('%');
	return (chars);
}

int	ft_printf(const char *s, ...)
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
			chars += ft_printf2(*s, args);
		}
		else
			chars += write(1, s, 1);
		s++;
	}
	va_end(args);
	return (chars);
}
