/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:39:55 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/01 14:21:09 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	error_number:
**	-1 = Malloc or other general error
**	-2 = Undefined behavior (not comprehensive)
*/

void	error_return(t_printf *p, int error_number)
{
	p->error = error_number;
	return ;
}

void	ready_for_next_conversion(t_printf *p)
{
	if (p->conversion)
	{
		free(p->conversion);
		p->conversion = NULL;
	}
	p->flags = 0;
	p->min_width = 0;
	p->precision = 0;
}

void	convert(t_printf *p)
{
	get_flags(p);
	get_min_width(p);
	get_precision(p);
	handle_initial_conversion(p);
	if (p->flags & F_PRECISION)
		handle_precision(p);
	handle_min_width(p);
	if (p->conversion && !p->error)
		add_to_buf(p, p->conversion, ft_strlen(p->conversion));
	ready_for_next_conversion(p);
}

void	process_format(t_printf *p)
{
	while (p->format && *p->format && !p->error)
	{
		if (*p->format == '%')
		{
			p->format++;
			if (!*p->format)
				break ;
			convert(p);
		}
		else
		{
			add_to_buf(p, p->format, 1);
		}
		p->format++;
	}
	if (!p->error)
		p->buf[p->buf_index] = '\0';
}

int		ft_printf(const char *format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	va_start(p.arg, format);
	p.buf_size = 16;
	p.buf = malloc(p.buf_size * sizeof(*p.buf));
	p.format = (char *)format;
	process_format(&p);
	va_end(p.arg);
	if (!p.error)
	{
		write(1, p.buf, ft_strlen(p.buf));
		free(p.buf);
		return (p.buf_index);
	}
	if (p.error == -1)
		write(1, "Ft_printf has encountered an error\n", 35);
	else if (p.error == -2)
		write(1, "Undefined behavior\n", 19);
	return (p.error);
}
