/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:52:35 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/29 16:15:40 by tmelvin          ###   ########.fr       */
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

# define F_HASH				(1 << 0)
# define F_MINUS			(1 << 1)
# define F_PLUS				(1 << 2)
# define F_SPACE			(1 << 3)
# define F_ZERO				(1 << 4)
# define F_APOSTROPHE		(1 << 5)
# define F_PRECISION		(1 << 6)
# define INTEGER_CONVERSION	(1 << 7)

# define FLAG_ORDER		"#-+ 0'"

/*
**	Structure definition
*/

typedef	struct			s_printf
{
	short				flags;
	int					min_width;
	int					precision;
	int					buf_index;
	char				*buf;
	int					buf_size;
	va_list				arg;
	char				*format;
	unsigned int		c;
	short				error;
	char				*conversion;
}						t_printf;

/*
**	Main functions
*/

int						ft_printf(const char *format, ...);

/*
**	Functions to check flags + min_width + precision
*/

void					get_flags(t_printf *p);
void					get_min_width(t_printf *p);
void					get_precision(t_printf *p);

/*
**	Functions to perform conversions
*/

void					convert_c(t_printf *p);
void					convert_s(t_printf *p);
void					convert_p(t_printf *p);
void					convert_di(t_printf *p);
void					convert_u(t_printf *p);
void					convert_xX(t_printf *p);
void					convert_percent(t_printf *p);

/*
**	Functions to apply min width + precision + other flags to the converted string
*/

void					handle_min_width(t_printf *p);
void					handle_precision(t_printf *p);
void					handle_hash(t_printf *p);

/*
**	Buffer related functions
*/

void					add_to_buf(t_printf *p, void *src, size_t size);
#endif
