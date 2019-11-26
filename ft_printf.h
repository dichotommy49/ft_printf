/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:52:35 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/26 13:21:56 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

/*
**	Flag masks definition
*/

# define F_HASH			(1 << 0)
# define F_MINUS		(1 << 1)
# define F_PLUS			(1 << 2)
# define F_SPACE		(1 << 3)
# define F_ZERO			(1 << 4)
# define F_APOSTROPHE	(1 << 5)
# define F_PRECISION	(1 << 6)

/*
**	Structure definition
*/

typedef	struct			s_printf
{
	int					len;
	short				flags;
	int					min_length;
	int					precision;
	int					padding;
	int					buf_index;
	char				*buf;
	int					buf_size;
	va_list				arg;
	char				*format;
	unsigned int		c;
	short				error;
}						t_printf;

int		ft_printf(const char *format, ...);

#endif
