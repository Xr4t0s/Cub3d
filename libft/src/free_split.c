/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:20:57 by nitadros          #+#    #+#             */
/*   Updated: 2025/09/21 03:41:19 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split || !*split)
		return ;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
