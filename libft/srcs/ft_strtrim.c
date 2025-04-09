/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:44:16 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	ft_iterate(char strc, const char *set)
{
	while (*set != '\0')
	{
		if (strc == *set)
			return (1);
		else
			set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*str;

	start = 0;
	end = ft_strlen(s1);
	while (ft_iterate(s1[start], set) == 1)
	{
		start++;
	}
	while (ft_iterate(s1[end - 1], set) == 1)
	{
		end--;
	}
	len = end - start;
	str = ft_substr(s1, start, len);
	return (str);
}
