/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:13:54 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/18 15:43:14 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_n(t_printf *p)
{
	long long	*llnumber;
	long		*lnumber;
	short		*hnumber;
	signed char	*hhnumber;
	int			*number;

	if (p->flags & F_L && (lnumber = va_arg(p->arg, long *)))
		*lnumber = p->buf_index;
	else if (p->flags & F_LL && (llnumber = va_arg(p->arg, long long *)))
		*llnumber = p->buf_index;
	else if (p->flags & F_H && (hnumber = va_arg(p->arg, short *)))
		*hnumber = p->buf_index;
	else if (p->flags & F_HH && (hhnumber = va_arg(p->arg, signed char *)))
		*hhnumber = p->buf_index;
	else if ((number = va_arg(p->arg, int *)))
		*number = p->buf_index;
	if (!(p->conversion = ft_strdup("")))
		return (error_return(p, -1));
}

void		convert_percent(t_printf *p)
{
	if (!(p->conversion = ft_strdup("%")))
		return (error_return(p, -1));
}
