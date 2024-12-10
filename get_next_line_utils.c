/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenisse <agenisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:41:22 by agenisse          #+#    #+#             */
/*   Updated: 2024/12/10 21:29:54 by agenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
    size_t	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
    char	*ptr;
    size_t	i;

    ptr = malloc(count * size);
    if (!ptr)
        return (NULL);
    i = 0;
    while (i < count * size)
        ptr[i++] = 0;
    return (ptr);
}

char	*ft_strchr(char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (*s == (char)c)
        return ((char *)s);
    return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
    char	*str;
    size_t	i;
    size_t	j;

    if (!s1)
        s1 = ft_calloc(1, sizeof(char));
    if (!s1 || !s2)
        return (NULL);
    str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
    if (!str)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
        str[i++] = s2[j++];
    free(s1);
    return (str);
}
