/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 14:39:35 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 20:01:33 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

int		main(void)
{
	int i = ft_printf("%5c\n", '\0');
	printf("%d\n", i);
	
//	wchar_t s[4];
//	
//	setlocale(LC_ALL, "");
//	int i = ft_printf("--.4u et %#O0%#012);
//	printf("\n%d\n", i);
	return (0);
}
