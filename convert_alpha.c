/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_alpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:43:41 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 20:53:25 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_c(t_printf *p)
{
	int	wcharlen;

	if (p->flags & F_L)
	{
		p->character = va_arg(p->arg, wint_t);
		if (p->character == 0)
			p->flags |= NULL_TERMINATOR;
		if (p->character > 0x10FFFF || p->character < 0 ||
				(p->character <= 0xDFFF && p->character >= 0xD800))
			return (error_return(p, -2));
		wcharlen = (int)ft_wcharlen((unsigned int)p->character);
		if (!(p->conversion = convert_wchar((unsigned int)p->character,
				wcharlen, wcharlen, p->conversion)))
			return (error_return(p, -1));
	}
	else
	{
		p->character = va_arg(p->arg, unsigned int);
		if (p->character == 0)
			p->flags |= NULL_TERMINATOR;
		if (!(p->conversion = ft_calloc(2, sizeof(*p->conversion))))
			return (error_return(p, -1));
		p->conversion[0] = p->character;
	}
}

void		convert_s(t_printf *p)
{
	char	*s;
	wchar_t *ws;

	if (p->flags & F_L)
	{
		if (!(ws = va_arg(p->arg, wchar_t *)))
		{
			if (!(p->conversion = ft_strdup("(null)")))
				return (error_return(p, -1));
		}
		else
			convert_ws(p, ws);
	}
	else
	{
		if (!(s = va_arg(p->arg, char *)))
		{
			if (!(p->conversion = ft_strdup("(null)")))
				return (error_return(p, -1));
		}
		else if (!(p->conversion = ft_strdup(s)))
			return (error_return(p, -1));
	}
}

void		convert_ws(t_printf *p, wchar_t *ws)
{
	int		wlen;
	size_t	wcharlen;
	char	*tmp;
	char	*tmp2;

	if (!(p->conversion = ft_strdup("")))
		return (error_return(p, -1));
	wlen = check_ws(p, ws);
	while (wlen > 0 && !p->error)
	{
		wcharlen = ft_wcharlen((unsigned int)*ws);
		if (!(tmp = convert_wchar(*ws++, wlen, wcharlen, tmp)))
			return (error_return(p, -1));
		if (!(tmp2 = ft_strjoin(p->conversion, tmp)))
		{
			free(tmp);
			return (error_return(p, -1));
		}
		free(p->conversion);
		p->conversion = tmp2;
		wlen -= wcharlen;
	}
}

int			check_ws(t_printf *p, wchar_t *ws)
{
	int	i;
	int	wlen;

	i = 0;
	while ((p->character = ws[i++]))
	{
		if (p->character > 0x10FFFF || p->character < 0 ||
				(p->character <= 0xDFFF && p->character >= 0xD800))
		{
			p->error = -2;
		}
	}
	wlen = (int)ft_wstrlen((unsigned int *)ws);
	if (p->flags & F_PRECISION)
		wlen = min(p->precision, wlen);
	return (wlen);
}

char		*convert_wchar(unsigned int wc, int wlen, int nb_bytes, char *tmp)
{
	if (!(tmp = calloc(nb_bytes + 1, sizeof(*tmp))))
		return (tmp);
	if (nb_bytes <= wlen && nb_bytes <= MB_CUR_MAX)
	{
		if (nb_bytes == 1)
			tmp[0] = wc;
		else
		{
			if (nb_bytes == 2)
				tmp[0] = ((wc & (0x1f << 6)) >> 6) | 0xC0;
			else
			{
				if (nb_bytes == 3)
					tmp[0] = ((wc >> 12) & 0xf) | 0xE0;
				else
				{
					tmp[0] = ((wc >> 18) & 7) | 0xF0;
					tmp[1] = ((wc >> 12) & 0x3f) | 0x80;
				}
				tmp[nb_bytes - 2] = ((wc >> 6) & 0x3f) | 0x80;
			}
			tmp[nb_bytes - 1] = (wc & 0x3f) | 0x80;
		}
	}
	return (tmp);
}
