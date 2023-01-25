#include "../include/minishell.h"
#include "../libft/libft.h"

void	parse(t_mini *mini, char *buff)
{
	char	**split;
	int		i;
	t_token	*head;

	split = ft_split(buff, ' ');
	head = new_token(mini, *split);
	mini->tokens = head;
	i = 0;
	while (split[++i])
		token_addend(split[i], mini);
	//print_tokens(mini->tokens);
	execute(mini);
	mini->cmd = 1;
	token_free(mini->tokens);
	agrv_free(split);
}