#include "../include/minishell.h"

int	create_pipe(t_mini *mini)
{
	int		fd[2];
	int		status;

	//g_global.pipe = 1;
	status = pipe(fd);
	if (status < 0)
	{
		mini->pipe_read = -1;
		mini->pipe_write = -1;
		return (0);
	}
	mini->pipe_read = fd[0];
	mini->pipe_write = fd[1];
	return (1);
}