/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:31:05 by mjong             #+#    #+#             */
/*   Updated: 2024/12/20 18:32:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	ft_stringcounter(char const *s, char c)
{
	int	strings;
	int	sign;

	strings = 0;
	sign = 0;
	while (*s != '\0')
	{
		if (*s != c && sign == 0)
		{
			strings++;
			sign = 1;
		}
		if (*s == c)
		{
			sign = 0;
		}
		s++;
	}
	return (strings);
}

static int	ft_length(const char *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

void	ft_free(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		free(str[j]);
		j++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	str = malloc((ft_stringcounter(s, c) + 1) * sizeof(char *));
	i = 0;
	j = 0;
	if (!str || !s)
		return (NULL);
	while (i < ft_stringcounter(s, c))
	{
		while (s[j] == c)
			j++;
		str[i] = ft_substr(s, j, ft_length(s, c, j));
		if (str[i] == NULL)
		{
			ft_free(str);
			return (NULL);
		}
		j += ft_length(s, c, j);
		i++;
	}
	str[i] = NULL;
	return (str);
}
