/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 15:33:53 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/10/29 15:33:56 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isupper(int c)
{
	return ((c >= 65 && c <= 90) ? 1 : 0);
}
