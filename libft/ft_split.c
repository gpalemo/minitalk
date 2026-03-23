/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:32:37 by cmauley           #+#    #+#             */
/*   Updated: 2025/10/17 04:57:09 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			word_count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (word_count);
}

static void	*free_all(char **tab, int i)
{
	while (i >= 0)
	{
		free (tab[i]);
		i--;
	}
	free (tab);
	return (NULL);
}

static int	fill_words(char const *s, char c, char **str)
{
	size_t	i;
	size_t	w;
	size_t	start;

	i = 0;
	w = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		str[w] = ft_substr(s, start, i - start);
		if (!str[w])
		{
			free_all(str, w);
			return (0);
		}
		w++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str[word_count(s, c)] = NULL;
	if (!fill_words(s, c, str))
		return (NULL);
	return (str);
}
/*int	main()
{
	char	**tab;
	int		i;

	tab = ft_split("caca pipi caca  ", ' ');
	i = 0;
	while (tab[i])
	{
		printf("str = %d : %s\n", i, tab[i]);
		i++;
	}
	return (0);
}*/
