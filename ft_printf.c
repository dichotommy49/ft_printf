/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:39:55 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/25 15:59:54 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_to_buf(t_printf *p, void *src, size_t size)
{
	while (p->buf && src && size > 0 && !p->error)
	{
		if (p->buf_index + 2 >= p->buf_size)
		{
			if (!(p->buf = ft_realloc(p->buf, p->buf_size, (p->buf_size *= 2))))
			{
				p->error = -1;
				return ;
			}
		}
		p->buf[p->buf_index++] = *(char *)src;
		if (size > 1)
			src++;
		size--;
	}
}

void	check_specifier(t_printf *p)
{
	p->c = *p->format;
	if (p->c == 'c')
	{
		unsigned int c = va_arg(p->arg, unsigned int);
		add_to_buf(p, &c, 1);
	}
	if (p->c == 's')
	{
		char *s = va_arg(p->arg, char *);
		add_to_buf(p, s, ft_strlen(s));
	}
	if (p->c == 'p')
	{
		char *pnt;
		if (!(pnt = ft_ultoa(va_arg(p->arg, unsigned long))))
		{
			p->error = -1;
			return ;
		}
		char *tmp;
		if (!(tmp = ft_convert_base(pnt, "0123456789", "0123456789abcdef")))
		{
			p->error = -1;
			return ;
		}
		free(pnt);
		if (!(pnt = ft_strjoin("0x", tmp)))
		{
			p->error = -1;
			return ;
		}
		free(tmp);
		add_to_buf(p, pnt, ft_strlen(pnt));
		free(pnt);
	}
	if (p->c == 'd' || p->c == 'i')
	{
		char *di;
		if (!(di = ft_itoa(va_arg(p->arg, int))))
		{
			p->error = -1;
			return ;
		}
		add_to_buf(p, di, ft_strlen(di));
		free(di);
	}
	if (p->c == 'u')
	{
		char *u;
		if (!(u = ft_uitoa(va_arg(p->arg, unsigned int))))
		{
			p->error = -1;
			return ;
		}
		add_to_buf(p, u, ft_strlen(u));
		free(u);
	
	}
	if (p->c == 'x' || p->c == 'X')
	{
		char *x = ft_uitoa(va_arg(p->arg, unsigned int));
		char *tmp;
		if (p->c == 'x')
		{
			if (!(tmp = ft_convert_base(x, "0123456789", "0123456789abcdef")))
			{
				p->error = -1;
				return ;
			}
		}
		else
		{
			if (!(tmp = ft_convert_base(x, "0123456789", "0123456789ABCDEF")))
			{
				p->error = -1;
				return ;
			}
		}
		free(x);
		add_to_buf(p, tmp, ft_strlen(tmp));
		free(tmp);
	}
//	if (p->c == 'n')
//	{
//	
//	}
//	if (p->c == 'f')
//	{
//	
//	}
//	if (p->c == 'g')
//	{
//	
//	}
//	if (p->c == 'e')
//	{
//	
//	}
}

void	parse_spec(t_printf *p)
{
	//check for '#' flag
	//check for '-' flag
	//check for '+' flag
	//check for ' ' flag
	//check for '0' flag
	//check for ''' flag
	//check for field width
	//check for precision
	check_specifier(p);
	//convert(format specifier) -> add_to_buf(p, "conversion", size)
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
			parse_spec(p);
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
	p.buf = malloc((p.buf_size = 16));
	p.format = (char *)format;

	process_format(&p);
	va_end(p.arg);
	if (!p.error)
	{
		write(1, p.buf, ft_strlen(p.buf));
		free(p.buf);
		return (p.buf_index);
	}
	return (p.error);
}
