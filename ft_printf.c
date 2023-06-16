/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcreus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:16:38 by mcreus            #+#    #+#             */
/*   Updated: 2023/06/16 13:20:10 by mcreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int putstr(char *str)
{
    if(!str)
    {
        write(1, "(null)", 6);
        return(6);
    }
    int i = 0;
    while(str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return(i);
}

int ft_putchar(char c)
{
    write(1, &c, 1);
    return(1);
}

int putnbr(long int nb)
{
    int len = 0;
    if(nb < 0)
    {
        nb *= -1;
        len++;
        write(1, "-", 1);
    }
    if(nb > 9)
    {
        len += putnbr(nb / 10);
        len += putnbr(nb % 10);
    }
    else
        len += ft_putchar('0' + nb);
    return(len);
}

int puthex(unsigned long int hex)
{
    int len  = 0;
    char *str = "0123456789abcdef";
    if(hex > 15)
    {
        len += puthex(hex / 16);
        len += puthex(hex % 16);
    }
    else
        len += ft_putchar(str[hex]);
    return(len);
}

int ft_printf(char *format, ... )
{
    int len = 0;
    int i = 0;
    va_list str;
    va_start(str, format);
    while(format[i])
    {
        if(format[i] != '%')
            len += ft_putchar(format[i]);
        else if(format[i] == '%' && format[i + 1])
        {
            i++;
            if(format[i] == 's')
                len += putstr(va_arg(str, char *));
            if(format[i] == 'd')
                len += putnbr((long int)va_arg(str, int));
            if(format[i] == 'x')
                len += puthex((unsigned long int)va_arg(str, unsigned int));
        }
        i++;
    }
    va_end(str);
    return(len);
}
