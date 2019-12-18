/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:39:55 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/18 15:25:41 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	p->character = 0;
}

void	handle_initial_conversion(t_printf *p)
{
	p->c = *p->format;
	if (p->c == 'C' || p->c == 'S' || p->c == 'D' || p->c == 'U')
		p->flags |= F_L;
	if (p->c == 'c' || p->c == 'C')
		convert_c(p);
	else if (p->c == 's' || p->c == 'S')
		convert_s(p);
	else if (p->c == 'p' || p->c == 'P')
		convert_p(p);
	else if (p->c == 'd' || p->c == 'i' || p->c == 'D' || p->c == 'I')
		convert_di(p);
	else if (p->c == 'u' || p->c == 'U')
		convert_u(p);
	else if (p->c == 'x' || p->c == 'X')
		convert_x(p);
	else if (p->c == '%')
		convert_percent(p);
	else if (p->c == 'n')
		convert_n(p);
	else
		p->error = -2;
}

void	convert(t_printf *p)
{
	get_info(p);
	handle_initial_conversion(p);
	if ((p->flags & F_MINUS && p->flags & F_ZERO) ||
			(p->flags & F_PRECISION && p->flags & INTEGER_CONVERSION))
		p->flags &= ~F_ZERO;
	if (p->flags & F_PRECISION && (p->flags & INTEGER_CONVERSION || p->c == 's'
				|| p->c == 'S'))
		handle_precision(p);
	if (!(p->flags & F_ZERO))
	{
		handle_sign(p);
		handle_hash(p);
	}
	handle_min_width(p);
	if (p->flags & F_ZERO)
	{
		handle_sign(p);
		handle_hash(p);
	}
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
	if (!(p.buf = malloc(p.buf_size * sizeof(*p.buf))))
		p.error = -4;
	if ((p.format = (char *)format))
		process_format(&p);
	else
		p.error = -3;
	va_end(p.arg);
	if (!p.error)
		write(1, p.buf, p.buf_index);
	if (p.error != -4)
		free(p.buf);
	if (p.error == -1 || p.error == -4)
		write(1, "Malloc error\n", 13);
	else if (p.error == -2)
		write(1, "Undefined behavior\n", 19);
	else if (p.error == -3)
		write(1, "Format string is NULL\n", 22);
	else
		return (p.buf_index);
	return (p.error);
}
