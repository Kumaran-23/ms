#include "../include/minishell.h"

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	mini->tokens = 0;
	mini->cmd = 1;
	mini->pipe_read = -1;
	mini->pipe_write = -1;
	mini->input = -1;
	mini->output = -1;
	mini->stdin = dup(STDIN_FILENO);
	mini->stdout = dup(STDOUT_FILENO);
	mini->execute_code = 0;
	mini->env = NULL;
	return (mini);
}

//just to get rid of unused parameter error when compiling
void	init_main(int argc, char **argv)
{
	if (argc > 1 || argv[1])
	{
		printf("one argc ./minishell ");
		exit(1);
	}
}

static void read_input(t_mini *mini, char *input)
{
	
	input = readline("@minishell> ");
	define_signal();
	parse(mini, input);
	add_history(input);
	dup2(mini->stdin, STDIN_FILENO);
	dup2(mini->stdout, STDOUT_FILENO);
	free(input);
}

int	main(int argc, char *argv[])
{
	t_mini	*mini;
	char	*buff;

	init_main(argc, argv);
	mini = init_mini();
	while (1)
	{
		buff = NULL;
		read_input(mini, buff);
	}
	return (mini->execute_code);
}