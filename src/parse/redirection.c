#include "../include/minishell.h"

int	redirect_input(t_mini *ms, t_token *token)
{
	if (ms->input != -1)
		close(ms->input);
	ms->input = open(token->str, O_RDONLY, S_IRWXU);
	if (ms->input == -1)
	{
		printf("minishell: %s : No such file or directory\n", token->str);
		return (1);
	}
	dup2(ms->input, STDIN_FILENO);
	return (0);
}

int	redirect_output(t_mini *ms, t_token *token, int type)
{
	if (ms->output != -1)
		close(ms->output);
	if (type == TRUNC)
		ms->output = open(token->str, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRWXU);
	else if (type == APPEND)
		ms->output = open(token->str, O_CREAT | O_WRONLY
				| O_APPEND, S_IRWXU);
	if (ms->output == -1)
	{
		printf("minishell: %s : No such file or directory\n", token->str);
		return (1);
	}
	dup2(ms->output, STDOUT_FILENO);
	return (0);
}