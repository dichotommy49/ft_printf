/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:43:41 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/01 13:53:09 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_c(t_printf *p)
{
	if (!(p->conversion = malloc(2 * sizeof(*p->conversion))))
		return (error_return(p, -1));
	p->conversion[0] = va_arg(p->arg, unsigned int);
	p->conversion[1] = '\0';
}

void		convert_s(t_printf *p)
{
	p->conversion = ft_strdup(va_arg(p->arg, char *));
}

void		convert_percent(t_printf *p)
{
	if (!(p->conversion = ft_strdup("%")))
		return (error_return(p, -1));
}
