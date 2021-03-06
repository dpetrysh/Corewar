/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:29:53 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/06 19:29:54 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if ((!s1 || !s2) && !(!s1 && !s2))
		return (0);
	else if (!s1 && !s2)
		return (1);
	return ((ft_strncmp(s1, s2, n)) ? 0 : 1);
}
