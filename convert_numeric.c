/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_numeric.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:46:32 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/12 13:08:25 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_p(t_printf *p)
{
	char *tmp;

	if (!(p->conversion = ft_ultoa(va_arg(p->arg, unsigned long))))
		return (error_return(p, -1));
	if (!(tmp = ft_convert_base(p->conversion, "0123456789",
					"0123456789abcdef")))
		return (error_return(p, -1));
	free(p->conversion);
	p->conversion = tmp;
	prepend(p, "0x");
}

void		convert_di(t_printf *p)
{
	char	*tmp;

	if (!(p->conversion = ft_itoa(va_arg(p->arg, int))))
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
	p->flags |= SIGNED_CONVERSION;
	p->flags |= INTEGER_CONVERSION;
}

void		convert_u(t_printf *p)
{
	if (!(p->conversion = ft_uitoa(va_arg(p->arg, unsigned int))))
		return (error_return(p, -1));
	if (p->flags & F_APOSTROPHE)
		add_separators(p);
	p->flags |= INTEGER_CONVERSION;
}

void		convert_x(t_printf *p)
{
	char *tmp;
	char *base;

	if (!(p->conversion = ft_uitoa(va_arg(p->arg, unsigned int))))
		return (error_return(p, -1));
	if (ft_strncmp(p->conversion, "0", 2) == 0)
		p->flags &= ~F_HASH;
	base = (p->c == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
	if (!(tmp = ft_convert_base(p->conversion, "0123456789", base)))
		return (error_return(p, -1));
	free(p->conversion);
	p->conversion = tmp;
	p->flags |= INTEGER_CONVERSION;
}

void		handle_sign(t_printf *p)
{
	if (p->flags & F_SPACE && p->flags & F_PLUS)
		p->flags &= ~F_SPACE;
	
	if (p->c == 'd' || p->c == 'D' || p->c == 'i' || p->c == 'I')
	{
		if (p->is_negative)
			prepend(p, "-");
		else
		{
			if (p->flags & F_SPACE)
				prepend(p, " ");
			else if (p->flags & F_PLUS)
				prepend(p, "+");
		}
	}
}
