/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:36:20 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 20:52:15 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		handle_hash(t_printf *p)
{
	char	*hash;

	if (!p->error)
	{
		if ((p->c == 'x' || p->c == 'X') && p->flags & F_HASH)
		{
			hash = (p->c == 'x') ? "0x" : "0X";
			prepend(p, hash);
		}
	}
}

void		add_separators(t_printf *p)
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

void		handle_sign(t_printf *p)
{
	if (!p->error)
	{
		if (p->flags & F_SPACE && p->flags & F_PLUS)
			p->flags &= ~F_SPACE;
		if (p->c == 'd' || p->c == 'D' || p->c == 'i' || p->c == 'I')
		{
			if (p->is_negative)
				prepend(p, "-");
			else
			{
				if (p->flags & F_SPACE)
					prepend(p, " ");
				else if (p->flags & F_PLUS)
					prepend(p, "+");
			}
		}
	}
}
