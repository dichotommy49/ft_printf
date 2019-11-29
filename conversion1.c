/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:46:50 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/29 16:45:04 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_c(t_printf *p)
{
	if (!(p->conversion = malloc(2 * sizeof(*p->conversion))))
	{
		p->error = -1;
		return ;
	}
	p->conversion[0] = va_arg(p->arg, unsigned int);
	p->conversion[1] = '\0';
}

void		convert_s(t_printf *p)
{
	p->conversion = ft_strdup(va_arg(p->arg, char *));
}

void		convert_p(t_printf *p)
{
	char *tmp;
	
	if (!(p->conversion = ft_ultoa(va_arg(p->arg, unsigned long))))
	{
		p->error = -1;
		return ;
	}
	if (!(tmp = ft_convert_base(p->conversion, "0123456789", "0123456789abcdef")))
	{
		p->error = -1;
		return ;
	}
	free(p->conversion);
	if (!(p->conversion = ft_strjoin("0x", tmp)))
	{
		free(tmp);
		p->error = -1;
		return ;
	}
	free(tmp);
}
void		convert_di(t_printf *p)
{		
	char	*tmp;
	char	*prepend;

	if (!(p->conversion = ft_itoa(va_arg(p->arg, int))))
	{
		p->error = -1;
		return ;
	}
	if ((p->flags & F_PLUS || p->flags & F_SPACE) && p->conversion[0] != '-')
	{
		if (p->flags & F_PLUS)
			prepend = "+";
		else if (p->flags & F_SPACE)
			prepend = " ";	
		if (!(tmp = ft_strjoin(prepend, p->conversion)))
		{
			p->error = -1;
			return ;
		}
		free(p->conversion);
		p->conversion = tmp;
	}
	p->flags |= INTEGER_CONVERSION;
}
void		convert_u(t_printf *p)
{		
	if (!(p->conversion = ft_uitoa(va_arg(p->arg, unsigned int))))
	{
		p->error = -1;
		return ;
	}
	p->flags |= INTEGER_CONVERSION;
}
void		convert_xX(t_printf *p)
{
	char *tmp;
	char *base;

	if (!(p->conversion = ft_uitoa(va_arg(p->arg, unsigned int))))
	{
		p->error = -1;
		return ;
	}
	if (ft_strncmp(p->conversion, "0", 2) == 0)
		p->flags &= ~F_HASH;
	base = (p->c == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
	if (!(tmp = ft_convert_base(p->conversion, "0123456789", base)))
	{
		p->error = -1;
		return ;
	}
	free(p->conversion);
	p->conversion = tmp;
	p->flags |= INTEGER_CONVERSION;
}

void		convert_percent(t_printf *p)
{
	p->conversion = ft_strdup("%");
}
