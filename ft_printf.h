/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:52:35 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/25 14:52:48 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

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
