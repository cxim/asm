//
// Created by И Б on 17.05.20.
//

#include "asm.h"

char 	*add_spaces(char **str)
{
	char 	*tmp;
	int		i;
	int 	j;

	tmp = (char*)ft_memalloc(sizeof(char) * 2 * (ft_strlen(*str) + 1));
	i = 0;
	j = 0;
	while (str[0][i])
	{
		if (str[0][i] == '%' || (i > 0 && str[0][i - 1] == ',') || (i > 1 && str[0][i - 1] == ':' && ft_strchr(LABEL_CHARS, str[0][i - 2])))
		{
			tmp[j] = ' ';
			j++;
		}
		tmp[j] = str[0][i];
		j++;
		i++;
	}
	return (tmp);
}

int		ft_countwords(char const *s, int c)
{
	int		word_count;
	int		i;

	word_count = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] > c && (s[i + 1] <= c || s[i + 1] == 127))
			word_count++;
		i++;
	}
	return (word_count);
}

void	ft_cpychars(char const *s, char *word, int start, int stop)
{
	int i;

	i = 0;
	while (start < stop)
	{
		word[i] = s[start];
		start++;
		i++;
	}
}

char	**ft_cpwrds(char **words, char const *s, int c)
{
	int i;
	int j;
	int start;
	int stop;

	i = -1;
	j = 0;
	start = 0;
	stop = 0;
	while (s[++i] != '\0')
	{
		if (s[i] <= c || s[i] == '\0')
			start = i + 1;
		if (s[i] > c && (s[i + 1] == 127 ||
						 s[i + 1] <= c))
		{
			stop = i + 1;
			words[j] = (char*)ft_memalloc(sizeof(char) * (stop - start + 1));
			ft_cpychars(s, words[j], start, stop);
			j++;
		}
	}
	words[j] = 0;
	return (words);
}

char		**ft_strsplit_whitespace(char const *s)
{
	char	**words;
	int		w_count;

	if (s)
	{
		w_count = ft_countwords(s, 32);
		words = (char**)ft_memalloc(sizeof(char*) * (w_count + 1));
		if (words)
			return (ft_cpwrds(words, s, 32));
	}
	return (0);
}

int		on_line(char *str)
{
	int 	i;
	int 	counter;

	i = (int)ft_strlen(str);
	counter = 0;
	while (i > 0 && counter < 2)
	{
		i--;
		if (str[i] == '"')
			counter++;
	}
	if (counter > 1)
		return (1);
	else if (counter > 0)
		return (0);
	else
		return (-1);
}

void	add_line(char **str)
{
	char 	*tmp;

	tmp = ft_strjoin(*str, "\n");
	free_str(str, NULL, 1);
	*str = tmp;
}