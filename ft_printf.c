/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:39:55 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 14:26:47 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	error_number:
**	-1 = Malloc or other general error
**	-2 = Undefined behavior (not comprehensive)
**	-3 = NULL format string
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
	get_modifiers(p);
	handle_initial_conversion(p);
	if ((p->flags & F_MINUS && p->flags & F_ZERO) ||
			(p->flags & F_PRECISION && p->flags & INTEGER_CONVERSION))
		p->flags &= ~F_ZERO;
	if (p->flags & F_PRECISION && (p->flags & INTEGER_CONVERSION || p->c == 's' || p->c == 'S'))
		handle_precision(p);
	if (!(p->flags & F_ZERO) && !p->error)
	{
		handle_sign(p);
		handle_hash(p);
	}
	handle_min_width(p);
	if (p->flags & F_ZERO && !p->error)
	{
		handle_sign(p);
		handle_hash(p);
	}
	if (p->conversion && !p->error)
	{
		if ((p->c == 'c' || p->c == 'C') && p->flags & NULL_TERMINATOR)
			add_to_buf(p, p->conversion, max(1, p->min_width));
		else
			add_to_buf(p, p->conversion, ft_strlen(p->conversion));
	}
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
	if ((p.format = (char *)format))
		process_format(&p);
	else
		p.error = -3;
	va_end(p.arg);
	if (!p.error)
	{
		write(1, p.buf, p.buf_index);
		free(p.buf);
		return (p.buf_index);
	}
	if (p.error == -1)
		write(1, "Malloc error\n", 13);
	else if (p.error == -2)
		write(1, "Undefined behavior\n", 19);
	else if (p.error == -3)
		write(1, "Format string is NULL\n", 22);
	return (p.error);
}
