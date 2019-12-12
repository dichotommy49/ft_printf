/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:05:00 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/12 13:17:39 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_precision(t_printf *p)
{
	int		padding;
	char	*tmp;
	char	replace;
	char	replacement[2];

	if (p->flags & INTEGER_CONVERSION)
	{
		if ((replace = (p->conversion[0] == '-' || p->conversion[0] == '+' || p->conversion[0] == ' ') ? p->conversion[0] : 0))
		{
			if (!(tmp = ft_strdup(p->conversion + 1)))
				return (error_return(p, -1));
			free(p->conversion);
			p->conversion = tmp;
		}
		if (!(p->flags & F_HASH) && p->precision == 0 && p->conversion[0] == '0')
		{
			if (!(tmp = ft_strdup("")))
				return (error_return(p, -1));
			free(p->conversion);
			p->conversion = tmp;
		}
		if ((padding = p->precision - ft_strlen(p->conversion)) > 0)
		{
			if (!(tmp = malloc((p->precision + 1) * sizeof(*tmp))))
				return (error_return(p, -1));
			ft_memset(tmp, '0', padding);
			ft_strlcpy(tmp + padding, p->conversion,
					ft_strlen(p->conversion) + 1);
			free(p->conversion);
			p->conversion = tmp;
		}
		if (replace)
		{
			replacement[0] = replace;
			replacement[1] = '\0';
			prepend(p, replacement);
		}

	}
	else if (p->c == 's' || p->c == 'S')
	{
		if (!(tmp = malloc((p->precision + 1) * sizeof(*tmp))))
			return (error_return(p, -1));
		ft_strlcpy(tmp, p->conversion, p->precision + 1);
		free(p->conversion);
		p->conversion = tmp;
	}
}

void	handle_min_width(t_printf *p)
{
	int		pad_size;
	char	pad;
	char	*tmp;
	char	*padding;

	if ((p->flags & F_MINUS && p->flags & F_ZERO) ||
			(p->flags & F_PRECISION && p->flags & INTEGER_CONVERSION))
		p->flags &= ~F_ZERO;
	pad = (p->flags & F_ZERO) ? '0' : ' ';
	if ((pad_size = (p->min_width - ft_strlen(p->conversion))) > 0)
	{
		if (p->flags & F_ZERO && (p->c == 'x' || p->c == 'X') && p->flags & F_HASH)
			pad_size -= 2;
		if (p->flags & SIGNED_CONVERSION && p->flags & F_ZERO && (p->is_negative || p->flags & F_PLUS || p->flags & F_SPACE))
			pad_size -= 1;
		if (!(padding = malloc((pad_size + 1) * sizeof(*padding))))
			return (error_return(p, -1));
		ft_memset(padding, pad, pad_size);
		padding[pad_size] = '\0';
		if (!(tmp = (p->flags & F_MINUS) ? ft_strjoin(p->conversion, padding)
					: ft_strjoin(padding, p->conversion)))
			return (error_return(p, -1));
		free(p->conversion);
		free(padding);
		p->conversion = tmp;
	}
}

void	handle_hash(t_printf *p)
{
	char	*hash;

	if ((p->c == 'x' || p->c == 'X') && p->flags & F_HASH)
	{
		hash = (p->c == 'x') ? "0x" : "0X";
		prepend(p, hash);
	}
}

void	add_separators(t_printf *p)
{
	size_t	commas;
	char	*tmp;
	char	*pnt;
	size_t	i;
	size_t	j;

	commas = (ft_strlen(p->conversion) - 1) / 3;
	i = 0;
	j = ft_strlen(p->conversion) + commas + 1;
	pnt = &p->conversion[ft_strlen(p->conversion) - 1];
	if (!(tmp = malloc(j * sizeof(*tmp))))
		return (error_return(p, -1));
	tmp[--j] = '\0';
	while ((pnt - i) >= p->conversion)
	{
		if (i != 0 && i % 3 == 0)
		{
			tmp[--j] = ',';
			tmp[--j] = *(pnt - i++);
		}
		else
			tmp[--j] = *(pnt - i++);
	}
	free(p->conversion);
	p->conversion = tmp;
}

void	handle_initial_conversion(t_printf *p)
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
		convert_x(p);
	else if (p->c == '%')
		convert_percent(p);
}
