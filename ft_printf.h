/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:52:35 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/18 15:25:03 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <wchar.h>
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
# define F_L				(1 << 6)
# define F_LL				(1 << 7)
# define F_H				(1 << 8)
# define F_HH				(1 << 9)
# define F_PRECISION		(1 << 10)
# define INTEGER_CONVERSION	(1 << 11)
# define SIGNED_CONVERSION	(1 << 12)
# define NULL_TERMINATOR	(1 << 13)

# define FLAG_ORDER		"#-+ 0'"

/*
**	Structure definition
*/

typedef	struct			s_printf
{
	short				flags;
	int					min_width;
	int					precision;
	unsigned int		c;
	int					is_negative;
	int					buf_index;
	char				*buf;
	int					buf_size;
	va_list				arg;
	char				*format;
	short				error;
	char				*conversion;
	wint_t				character;
}						t_printf;

/*
**	Main functions
*/

int						ft_printf(const char *format, ...);
void					process_format(t_printf *p);
void					convert(t_printf *p);
void					handle_initial_conversion(t_printf *p);
void					ready_for_next_conversion(t_printf *p);

/*
**	Functions to parse and store flags + min_width + precision + modifiers
*/

void					get_info(t_printf *p);
void					get_flags(t_printf *p);
void					get_min_width(t_printf *p);
void					get_precision(t_printf *p);
void					get_modifiers(t_printf *p);

/*
**	Functions to perform specific conversions
*/

void					convert_c(t_printf *p);
void					convert_s(t_printf *p);
void					convert_p(t_printf *p);
void					convert_di(t_printf *p);
void					convert_u(t_printf *p);
void					convert_x(t_printf *p);
void					convert_n(t_printf *p);
void					convert_percent(t_printf *p);

/*
**	Functions to apply min width + precision to the converted string
*/

void					handle_min_width(t_printf *p);
int						get_pad_size(t_printf *p);
void					handle_precision(t_printf *p);

/*
**	Functions to apply certain flags to the converted string
*/

void					handle_hash(t_printf *p);
void					handle_sign(t_printf *p);
void					add_separators(t_printf *p);

/*
**	Buffer related functions
*/

void					add_to_buf(t_printf *p, void *src, size_t size);

/*
**	Other miscellaneous functions
*/

void					error_return(t_printf *p, int error_number);
void					prepend(t_printf *p, char *str, int dynamic);
void					append(t_printf *p, char *str, int dynamic);
int						max(int a, int b);
int						min(int a, int b);

/*
**	Functions used in wide conversions
*/

void					convert_ws(t_printf *p, wchar_t *ws);
int						check_ws(t_printf *p, wchar_t *ws);
char					*convert_wchar(unsigned int wc, int wlen,
		int nb_bytes, char *tmp);

#endif
