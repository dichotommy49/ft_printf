/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:39:17 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/29 15:53:52 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_min_width(t_printf *p)
{
	if (*p->format == '-')
	{
		p->flags |= F_MINUS;
		p->format++;
	}
	if (ft_isdigit(*p->format))
	{
		if (*p->format == '0')
			p->flags |= F_ZERO;
		p->min_width = ft_atoi(p->format);
		while (ft_isdigit(*p->format))
			p->format++;
	}
	else if (*p->format == '*')
	{
		p->min_width = va_arg(p->arg, int);
		p->format++;
		if (p->min_width < 0)
			p->flags |= F_MINUS;
		p->min_width *= (p->min_width < 0) ? -1 : 1;
	}
}

void	get_precision(t_printf *p)
{
	if (*p->format == '.')
	{
		p->flags |= F_PRECISION;
		p->format++;
		if (*p->format == '*')
		{
			p->precision = va_arg(p->arg, int);
			p->format++;
			if (p->precision < 0)
				p->flags &= ~F_PRECISION;
		}
		else
			p->precision = ft_atoi(p->format);
		while (ft_isdigit(*p->format))
			p->format++;
	}
}
