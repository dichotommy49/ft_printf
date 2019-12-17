/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_numeric.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:46:32 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 20:51:47 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_p(t_printf *p)
{
	char *tmp;

	if (p->flags & F_PRECISION || p->flags & F_ZERO)
		return (error_return(p, -2));
	if (!(p->conversion = ft_ulltoa(va_arg(p->arg, unsigned long))))
		return (error_return(p, -1));
	if (!(tmp = ft_convert_base_unsigned(p->conversion, "0123456789",
					"0123456789abcdef")))
		return (error_return(p, -1));
	free(p->conversion);
	p->conversion = tmp;
	prepend(p, "0x");
}

void		convert_di(t_printf *p)
{
	char		*tmp;
	long long	number;

	if (p->flags & F_L)
		number = (long)va_arg(p->arg, long);
	else if (p->flags & F_LL)
		number = va_arg(p->arg, long long);
	else if (p->flags & F_H)
		number = (short)va_arg(p->arg, int);
	else if (p->flags & F_HH)
		number = (signed char)va_arg(p->arg, int);
	else
		number = va_arg(p->arg, int);
	if (!(p->conversion = ft_lltoa(number)))
		return (error_return(p, -1));
	if ((p->is_negative = (p->conversion[0] == '-') ? 1 : 0))
	{
		if (!(tmp = ft_strdup(p->conversion + 1)))
			return (error_return(p, -1));
		free(p->conversion);
		p->conversion = tmp;
	}
	if (p->flags & F_APOSTROPHE)
		add_separators(p);
	p->flags |= (SIGNED_CONVERSION | INTEGER_CONVERSION);
}

void		convert_u(t_printf *p)
{
	unsigned long long number;

	if (p->flags & F_L)
		number = (unsigned long)va_arg(p->arg, unsigned long);
	else if (p->flags & F_LL)
		number = va_arg(p->arg, unsigned long long);
	else if (p->flags & F_H)
		number = (unsigned short)va_arg(p->arg, int);
	else if (p->flags & F_HH)
		number = (unsigned char)va_arg(p->arg, int);
	else
		number = va_arg(p->arg, unsigned int);
	if (!(p->conversion = ft_ulltoa(number)))
		return (error_return(p, -1));
	if (p->flags & F_APOSTROPHE)
		add_separators(p);
	p->flags |= INTEGER_CONVERSION;
}

void		convert_x(t_printf *p)
{
	char				*tmp;
	char				*base;
	unsigned long long	number;

	if (p->flags & F_L)
		number = (unsigned long)va_arg(p->arg, unsigned long);
	else if (p->flags & F_LL)
		number = va_arg(p->arg, unsigned long long);
	else if (p->flags & F_H)
		number = (unsigned short)va_arg(p->arg, unsigned int);
	else if (p->flags & F_HH)
		number = (unsigned char)va_arg(p->arg, unsigned int);
	else
		number = va_arg(p->arg, unsigned int);
	if (number == 0)
		p->flags &= ~F_HASH;
	if (!(p->conversion = ft_ulltoa(number)))
		return (error_return(p, -1));
	base = (p->c == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
	if (!(tmp = ft_convert_base_unsigned(p->conversion, "0123456789", base)))
		return (error_return(p, -1));
	free(p->conversion);
	p->conversion = tmp;
	p->flags |= INTEGER_CONVERSION;
}

void		convert_percent(t_printf *p)
{
	if (!(p->conversion = ft_strdup("%")))
		return (error_return(p, -1));
}
