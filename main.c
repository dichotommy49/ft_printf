/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:09:34 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/01 14:50:39 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int		main(void)
{
//	char	s[] = "Just your average everyday string";
//	char	c = 'A';
	int		d = 42;
//	unsigned int u = 4147438648;
//	int x = 255;
//	int X = 0;
//	int	*p = &x;
//
//	ft_printf("This is a string test: %s\nAnd this is a char test: %c\nNow we have an int test: %i\nThis is an unsigned int: %u\nHere is a lowercase hexadecimal conversion: %#x\nAnd an uppercase hex conversion: %#X\nFinally, a pointer conversion: %p\n", s, c, d, u, x, X, p);
//	printf("This is the real function's pointer conversion: %p\n", p);

	ft_printf("This is a test of min width: |%5d|\n", d);
	return (0);
}
