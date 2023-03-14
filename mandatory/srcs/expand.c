#include "../incs/minishell.h"

/* Recibe un argumento de next_line_split */

int	ft_search_env(char **env, char *var)
{
	int		i;
	size_t	len;
	size_t	var_len;
	int		j;

	i = -1;
	len = 0;
	j = 0;
	var_len = ft_strlen(var);
	//printf("var len = %zu\n", var_len);
	while (env[++i])
	{
		len = ft_get_chrlen(env[i], '=');
		//printf("Len hasta el igual = %zu\n", len);
		if (var_len == len)
		{
			//printf("Coincide longitud\n");
			//printf("env = %s y var = %s\n", env[i], var);
			if (ft_strnstr(env[i], var,  var_len))
				return (i);
		}
		
	}
	return (-1);
}

void	ft_expand(const char *str, char **env)
{
	int		i;
	int		start;
	char	*dst;
	int		indice_var;

	i = 0;
	start = 0;
	/*  */
	while (str[i] && str[i] != '$')
			i++;
	if (str[i] == '$')
	{
		i++;
		start = i;
		if (str[i] == 39 || str[i] == 32)
			return ;
	}
	while (str[i] && str[i + 1] != 34 && str[i] != 32)
		i++;
	dst = ft_substr(str, start, i);
	printf("Variable env = %s\n", dst);
	ft_search_env(env, dst);
	/*free(*str);
	*str = NULL;
	*str = dst;
	free(dst);*/
}

void	ft_process_expand(char **str, char **env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i][j] != 39)
			ft_expand((const char *)str[i], env);
	}
}