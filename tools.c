/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:03:00 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/12 12:16:30 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Prepend a string to your dynamically allocated p->conversion (formatted result of conversion).
*/

void	prepend(t_printf *p, char *str)
{
	char	*tmp;
	
	if (!(tmp = ft_strjoin(str, p->conversion)))
		return (error_return(p, -1));
	free(p->conversion);
	p->conversion = tmp;
}
