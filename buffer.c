/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:10:00 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 21:39:32 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_to_buf(t_printf *p, void *src, size_t size)
{
	if ((p->c == 'c' || p->c == 'C') && p->flags & NULL_TERMINATOR)
		size = max(1, p->min_width);
	while (p->buf && src && size > 0 && !p->error)
	{
		if (p->buf_index + 2 >= p->buf_size)
		{
			if (!(p->buf = ft_realloc(p->buf, p->buf_size, (p->buf_size *= 2))))
			{
				return (error_return(p, -4));
			}
		}
		p->buf[p->buf_index++] = *(char *)src;
		if (size > 1)
			src++;
		size--;
	}
}
