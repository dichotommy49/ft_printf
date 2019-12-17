/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:41:23 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 20:27:26 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_info(t_printf *p)
{
	get_flags(p);
	get_min_width(p);
	get_precision(p);
	get_modifiers(p);
}

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
	if (p->flags & F_MINUS && p->flags & F_ZERO)
		p->flags &= ~F_ZERO;
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
		p->precision *= (p->precision < 0) ? -1 : 1;
	}
}

void	get_modifiers(t_printf *p)
{
	if (*p->format == 'l' || *p->format == 'h')
	{
		if (*(p->format + 1) == 'l' || *(p->format + 1) == 'h')
		{
			if (*p->format == 'l' && *(p->format + 1) == 'l')
				p->flags |= F_LL;
			else if (*p->format == 'h' && *(p->format + 1) == 'h')
				p->flags |= F_HH;
			p->format += 2;
		}
		else
		{
			if (*p->format == 'l')
				p->flags |= F_L;
			else
				p->flags |= F_H;
			p->format++;
		}
	}
}
