/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:39:55 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/29 16:34:06 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_test_info(t_printf *p)
{
	printf("ft_printf testing info is indented below:\n");
	printf("\tMin width is: %d\n", p->min_width);
	printf("\tPrecision is: %d\n", p->precision);
	printf("\tFlags are : %s\n", ft_convert_base(ft_itoa(p->flags), "0123456789", "01"));
}

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

void	ready_for_next_convert(t_printf *p)
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

void	handle_precision(t_printf *p)
{
	int		padding;
	char	*tmp;

	if (p->flags & F_PRECISION)
	{
		p->precision *= (p->precision < 0) ? -1 : 1;
		if (p->flags & INTEGER_CONVERSION)
		{
			if ((padding = p->precision - ft_strlen(p->conversion)) > 0)
			{
				if (!(tmp = malloc((p->precision + 1) * sizeof(*tmp))))
				{
					p->error = -1;
					return ;
				}
				ft_memset(tmp, '0', padding);
				ft_strlcpy(tmp + padding, p->conversion, ft_strlen(p->conversion) + 1);
				free(p->conversion);
				p->conversion = tmp;
			}
		}
		else if (p->c == 's' || p->c == 'S')
		{
			if (!(tmp = malloc((p->precision + 1) * sizeof(*tmp))))
			{
				p->error = -1;
				return ;
			}
			ft_strlcpy(tmp, p->conversion, p->precision + 1);
			free(p->conversion);
			p->conversion = tmp;
		}
	}
}

void	handle_min_width(t_printf *p)
{
	int		padding;
	char	pad;
	char	*tmp;

	pad = ' ';
	if ((padding = (p->min_width - ft_strlen(p->conversion))) > 0)
	{
		if (p->flags & F_ZERO)
			pad = '0';
		if (!(tmp = malloc((p->min_width + 1) * sizeof(*tmp))))
		{
			p->error = -1;
			return ;
		}
		if (p->flags & F_MINUS)
		{
			if (p->flags & F_ZERO)
				p->error = -2;
			ft_memcpy(tmp, p->conversion, ft_strlen(p->conversion));
			ft_memset(tmp + ft_strlen(p->conversion), pad, padding);
			tmp[padding + ft_strlen(p->conversion)] = '\0';
		}
		else
		{
			ft_memset(tmp, pad, padding);
			ft_strlcpy(tmp + padding, p->conversion, ft_strlen(p->conversion) + 1);
		}
		free(p->conversion);
		p->conversion = tmp;
	}
}

void	handle_hash(t_printf *p)
{
	char	*hash;
	char	*tmp;

	if (p->flags & F_HASH)
	{
		hash = (p->c == 'x') ? "0x" : "0X";
		tmp = ft_strjoin(hash, p->conversion);
		free(p->conversion);
		p->conversion = tmp;
	}
}

void	convert(t_printf *p)
{
	p->c = *p->format;
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
		convert_xX(p);
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
	else if (p->c == '%')
		convert_percent(p);
}

void	handle_conversion(t_printf *p)
{
	get_flags(p);
	get_min_width(p);
	get_precision(p);
	convert(p);
	handle_precision(p);
	handle_min_width(p);
	handle_hash(p);
//	print_test_info(p);
	if (p->conversion && !p->error)
		add_to_buf(p, p->conversion, ft_strlen(p->conversion));
	ready_for_next_convert(p);
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
			handle_conversion(p);
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
	if (p.error == -1)
		write(1, "Ft_printf has encountered an error", 34);
	else if (p.error == -2)
		write(1, "Undefined behavior", 18);
	return (p.error);
}
