/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:36:52 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/28 15:40:58 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flags(t_printf *p)
{
	char	*flag_order;
	char	*pos;
	
	flag_order = FLAG_ORDER;
	while ((pos = ft_strchr(flag_order, *p->format)) != NULL)
	{
		p->flags |= (1 << (pos - flag_order));
		p->format++;
	}
}

