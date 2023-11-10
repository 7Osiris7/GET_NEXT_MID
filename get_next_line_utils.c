/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:22:22 by jruhlman          #+#    #+#             */
/*   Updated: 2023/11/10 12:08:32 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strlgjoin(char *s1, char *s2, int *r_l)
{
	char	*dest;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dest = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(dest, s1, len1);
	free(s1);
	ft_memcpy(dest + len1, s2, len2 + 1);
	if (len1 + len2 > 0 && *(dest + len1 + len2 - 1) == '\n')
		*r_l = 0;
	return (dest);
}

void	ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!dest || !src)
		return ;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (n--)
		*d++ = *s++;
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

void	ft_strlgcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while (src[i] && i < n - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
}
