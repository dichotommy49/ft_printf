/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:15:06 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/22 14:21:31 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

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
