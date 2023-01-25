#include "../include/minishell.h"

void	token_free(t_token *tok)
{
	t_token	*temp;

	while (tok)
	{
		temp = tok;
		tok = tok->next;
		free(temp->str);
		free(temp);
		temp = tok;
	}
}

void	agrv_free(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i])
	{
		free(argv[i++]);
	}
	free(argv);
}