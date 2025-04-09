/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:06:47 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_strlen2(const char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != '\0')
		{
			i++;
		}
	}
	return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = ft_strlen2(s1);
	j = ft_strlen2(s2);
	str = (char *)malloc(i + j + 1);
	if (!str)
		return (ft_free2(&s1));
	str[i + j] = '\0';
	while (j--)
	{
		str[i + j] = s2[j];
	}
	while (i--)
	{
		str[i] = s1[i];
	}
	ft_free2(&s1);
	return (str);
}

char	*ft_strchr2(char *s, int c)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_free2(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}
