/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:43:41 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/11 14:10:27 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_c(t_printf *p)
{
	if (!(p->conversion = malloc(2 * sizeof(*p->conversion))))
		return (error_return(p, -1));
	p->conversion[0] = va_arg(p->arg, unsigned int);
	p->conversion[1] = '\0';
	if (p->conversion[0] == '\0')
		add_to_buf(p, p->conversion, 1);
}

void		convert_s(t_printf *p)
{
	char *s = va_arg(p->arg, char *);

	if (!s)
		p->conversion = ft_strdup("(null)");
	else
		p->conversion = ft_strdup(s);
}

void		convert_percent(t_printf *p)
{
	if (!(p->conversion = ft_strdup("%")))
		return (error_return(p, -1));
}
