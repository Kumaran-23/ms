#include "../include/minishell.h"

//calls the builtin function for execution
int	call_builtin(char **argv, char *command, t_mini *ms)
{
	int	argc;
	int	builtin_cmd;

	argc = count_argc(argv);
	builtin_cmd = 0;
	if (!ft_strcmp(command, "echo"))
		builtin_cmd = echo(argc, argv);
	else if (!ft_strcmp(command, "pwd"))
		builtin_cmd = pwd();
	else if (!ft_strcmp(command, "exit"))
		builtin_cmd = mini_exit(ms, argv);
	return (builtin_cmd);
}

int execute_builtin(char **argv, char *command, t_mini *ms)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid != 0)
	{
		if (ms->pipe_read != -1)
		{
			close(ms->pipe_write);
			dup2(ms->pipe_read, STDIN_FILENO);
		}
		waitpid(pid, &exit_code, 0);
	}
	else
	{
		if (ms->pipe_write != -1)
		{
			close(ms->pipe_read);
			dup2(ms->pipe_write, STDOUT_FILENO);
		}
		exit_code = call_builtin(argv, command, ms);
		exit(exit_code);
	}
	return (exit_code);
}