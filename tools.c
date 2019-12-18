/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:03:00 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/18 13:03:23 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	error_number:
**	-1 = Malloc or other general error
**	-2 = Undefined behavior (not comprehensive)
**	-3 = NULL format string
**	-4 = failed Malloc on buffer (buffer should not be freed)
*/

void	error_return(t_printf *p, int error_number)
{
	p->error = error_number;
	return ;
}

/*
**	Prepend or append a string to dynamically allocated
**	p->conversion (formatted result of conversion)
*/

void	prepend(t_printf *p, char *str, int dynamic)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(str, p->conversion)))
	{
		if (dynamic)
			free(str);
		return (error_return(p, -1));
	}
	if (dynamic)
		free(str);
	free(p->conversion);
	p->conversion = tmp;
}

void	append(t_printf *p, char *str, int dynamic)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(p->conversion, str)))
	{
		if (dynamic)
			free(str);
		return (error_return(p, -1));
	}
	if (dynamic)
		free(str);
	free(p->conversion);
	p->conversion = tmp;
}

/*
**	Simple min and max functions
*/

int		max(int a, int b)
{
	return ((a > b) ? a : b);
}

int		min(int a, int b)
{
	return ((a < b) ? a : b);
}
