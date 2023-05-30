/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:27:31 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 14:36:07 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (!(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')
			|| ('0' <= c && c <= '9')))
		return (0);
	return (1);
}