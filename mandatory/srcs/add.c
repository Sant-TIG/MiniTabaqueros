#include "../incs/minishell.h"

/*
 * Añade un nuevo caracter a una cadena. Libera el contenido anterior
 */
char	*ft_join_chr(char *str, int c)
{
	//printf("\nJOIN CHR\n");
	char *new_str;
	int i;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!new_str)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		free(str);
	}
	new_str[i] = c;
	new_str[++i] = '\0';
	return (new_str);
}

/*
 * Mitico split del libft
 */
static char *ft_splitdup(const char *s, size_t start, size_t finish)
{
	char *dest;
	size_t i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (finish - start + 1));
	if (!dest)
		return (NULL);
	while (start < finish)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

static void ft_process_quote(const char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	(*i)++;
}

static char **ft_process_string(char **dest, const char *str, char c)
{
	printf("\nPROCESS STRING\n");
	int	i;
	int	j;
	int	start;

	i = 0;
	j = -1;
	start = 0;
	printf("str = %s\n", str);
	while (str[i])
	{
		if (str[i] == c)
		{
			printf("Encuentra espacio\n");
			while (str[i] && str[i] == c)
			{
				i++;
				start = i;
			}
		}
		else if (str[i])
		{
			//printf("cadena antes de revisar = %s\n", &str[i]);
			if (str[i] && (str[i] == 34 || str[i] == 39))
				ft_process_quote(str, &i, str[i]);
			if (str[i] && str[i] != c)
			{
				printf("Entra en caracter\n");
				while (str[i] && str[i] != c && str[i] != 34 && str[i] != 39)
					i++;
			}
			if (!str[i] || str[i] == c)
			{
				//printf("Entra a copiar con %s como inicio y %s como final\n", &str[start], &str[i]);
				dest[++j] = ft_splitdup(str, start, i);
				printf("Despues de cpiar = %s\n", dest[j]);
				start = i;
			}
		}
	}
	dest[++j] = NULL;
	return (dest);
}

static int	ft_process_quotes(const char *str, int *i, char c)
{
	if (str[*i] == 34 || str[*i] == 39)
	{
		ft_process_quote(str, i, str[*i]);
		while (str[*i] && str[*i] != c)
			(*i)++;
		return (1);
	}
	return (0);
}

static size_t	ft_line_counter(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			if (!ft_process_quotes(str, &i, c))
			{
				while (str[i] && str[i] != c)
				{
					ft_process_quotes(str, &i, c);
					i++;
				}
			}
			count++;
		}		
	}
	return (count);
}

char **ft_split(const char *str, char c)
{
	char **dest;

	if (!str)
		return (NULL);
	printf("cantidad de argumentos = %zu\n", ft_line_counter(str, c));
	dest = (char **)malloc(sizeof(char *) * (ft_line_counter(str, c) + 1));
	if (!dest)
		return (NULL);
	ft_process_string(dest, str, c);
	printf("Despues de haber copiado todo\n");
	ft_print2dstr(dest);
	printf("\n");
	return (dest);
}