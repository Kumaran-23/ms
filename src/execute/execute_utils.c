#include "../include/minishell.h"
#include "../libft/libft.h"

int	count_argc(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

void	call_pipe_redirect(t_mini *mini, t_token *command, t_token *tok)
{
	if (!command)
		return ;
	if (tok && tok->type == PIPE)
	{
		create_pipe(mini);
		tok = tok->next;
	}
	else if (tok && (tok->type == TRUNC || tok ->type == APPEND))
	{
		tok = tok->next;
		tok->type = ARG;
		redirect_output(mini, tok, tok->prev->type);
	}
	else if (tok && (tok->type == INPUT))
	{
		tok = tok->next;
		tok->type = ARG;
		redirect_input(mini, tok);
	}
}

//converts arguments into an array of strings
char	**convert_argv(t_token	*tokens)
{
	int		i;
	t_token	*tok;
	char	**res;

	i = 0;
	tok = tokens;
	while (tok && (tok->type == ARG || tok->type == BUILTIN
			|| tok->type == CMD))
	{
		i++;
		tok = tok->next;
	}
	if (!i)
		return (0);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tok = tokens;
	while (tok && (tok->type == ARG || tok->type == BUILTIN
			|| tok->type == CMD))
	{
		res[i++] = ft_strdup(tok->str);
		tok = tok->next;
	}
	res[i] = 0;
	return (res);
}