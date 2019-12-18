/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:48:31 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/18 14:47:31 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_precision(t_printf *p)
{
	int		padding;
	char	*tmp;

	if (p->flags & INTEGER_CONVERSION && !p->error)
	{
		if (!(p->flags & F_HASH) && p->precision == 0 && *p->conversion == '0')
			p->conversion[0] = '\0';
		if ((padding = p->precision - ft_strlen(p->conversion)) > 0)
		{
			if (!(tmp = ft_calloc((padding + 1), sizeof(*tmp))))
				return (error_return(p, -1));
			ft_memset(tmp, '0', padding);
			prepend(p, tmp, 1);
		}
	}
	else if ((p->c == 's' || p->c == 'S') && !p->error)
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
	char	*padding;

	pad_size = get_pad_size(p);
	pad = (p->flags & F_ZERO) ? '0' : ' ';
	if (pad_size > 0 && !p->error)
	{
		if (!(padding = ft_calloc(pad_size + 1, sizeof(*padding))))
			return (error_return(p, -1));
		padding = ft_memset(padding, pad, pad_size);
		if (p->flags & NULL_TERMINATOR)
		{
			if (p->flags & F_MINUS)
				padding[0] = p->character;
			else
				padding[ft_strlen(padding) - 1] = p->character;
			free(p->conversion);
			p->conversion = padding;
		}
		else
			(p->flags & F_MINUS) ? append(p, padding, 1)
				: prepend(p, padding, 1);
	}
}

int		get_pad_size(t_printf *p)
{
	int		pad_size;

	if (p->flags & F_PRECISION && p->flags & INTEGER_CONVERSION)
		p->flags &= ~F_ZERO;
	pad_size = p->min_width - ft_strlen(p->conversion);
	if (p->flags & F_ZERO && (p->c == 'x' || p->c == 'X') && p->flags & F_HASH)
		pad_size -= 2;
	if (p->flags & SIGNED_CONVERSION && p->flags & F_ZERO &&
			(p->is_negative || p->flags & F_PLUS || p->flags & F_SPACE))
		pad_size -= 1;
	return (pad_size);
}
