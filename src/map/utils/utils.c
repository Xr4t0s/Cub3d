/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:31:11 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/27 02:03:41 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

char	*ft_strchr1(const char *s, int c)
{
	int	i;
	int	limit;

	i = 0;
	limit = ft_strlen(s) + 1;
	while (i < limit)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_rm_char(char *str, char *ch)
{
	int		i;
	int		x;
	char	*ret;
	int mark;
	
	mark = 1;
	i = 0;
	x = 0;
	if (!str || !ch)
		return (NULL);
	ret = calloc(8, ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	while (str[i] && ft_strchr1(ch, str[i]))
		i++;
	while (str[i])
	{
		if (!ft_strchr1(ch, str[i]))
			ret[x++] = str[i];
		else
		{
			if (mark == 1)
			{
				ret[x++] = ';';
				mark = 0;
			}
			while (str[i] && ft_strchr1(ch, str[i]))
				i++;
			continue ;
		}	
		i++;
	}
	ret[x] = 0;
	free(str);
	return (ret);
}
