#include "../include/minishell.h"

/*

int ft_cmd(char *str, char *lineptr)
{
	char *cmd = str;
	char *argv[] = {lineptr, NULL};
	char *env[] = {NULL};

	int status;
	int pid = fork();
	if (!pid)
	{
	if (execve(cmd, argv, env) == -1)
		return (-1);
	}
	waitpid(pid, &status, 0);
	return (2);
}

int getenv_cmd(int argc, char **argv)
{
	char **split;
	int	i = 0;
	split = NULL;

	if (argc < 1)
		return (1);
	char *path = getenv("PATH");

	split = ft_split(path + 5, ':');
	while (split[i] != NULL)
	{
		split[i] = ft_strjoin(split[i], "/");
		split[i] = ft_strjoin(split[i], argv[0]);
		if (ft_cmd(split[i], *argv) != -1)
		{
			break;
		}
		i++;
	}
	return (0);
}

int call_cmd(char **argv)
{
	int argc;
	int builtin_cmd;
	builtin_cmd = 0;
	argc = count_argc(argv);
	
	builtin_cmd = getenv_cmd(argc, argv);
	return (builtin_cmd);	
}

*/

#include "../include/minishell.h"
#include <sys/stat.h>

int ft_cmd(char *str, char *lineptr)
{
	char *cmd = str;
	char *argv[] = {lineptr, NULL};
	char *env[] = {NULL};

	int status;
	int pid = fork();
	if (!pid)
	{
	if (execve(cmd, argv, env) == -1)
		return (-1);
	}
	waitpid(pid, &status, 0);
	return (2);
}

int getenv_cmd(int argc, char **argv)
{
	char **split;
	int	i = 0;
	split = NULL;

	if (argc < 1)
		return (1);
	char *path = getenv("PATH");

	split = ft_split(path + 5, ':');
	while (split[i] != NULL)
	{
		split[i] = ft_strjoin(split[i], "/");
		split[i] = ft_strjoin(split[i], argv[0]);
		if (ft_cmd(split[i], *argv) != -1)
		{
			break;
		}
		i++;
	}
	return (0);
}

/*
int call_cmd(char **argv)
{
	int argc;
	int builtin_cmd;
	builtin_cmd = 0;
	argc = count_argc(argv);
	
	builtin_cmd = getenv_cmd(argc, argv);
	return (builtin_cmd);	
}*/

int	it_works(char *cmd_path)
{
	struct stat	buffer;

	if (stat(cmd_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

char *ft_getpath(char **av)
{
	char **split;
	int i = 0;
	split = NULL;

	char *path = getenv("PATH");

	split = ft_split(path + 5, ':');
	while (split[i] != NULL)
	{
		split[i] = ft_strjoin(split[i], "/");
		split[i] = ft_strjoin(split[i], av[0]);
		if (it_works(split[i]))
		{
			break;
		}
		i++;
	}

	return (split[i]);
}

int ft_ex(char **argv, char **envp, int i)
{
	int	res;

	int pid = fork();
	if (!pid)
	{
		printf("inside executiuon\n");
		argv[i] = 0;
		execve(*argv, envp, NULL);
		return printf("error");
	}
	if (waitpid(pid, &res, 0) == -1)
		return printf("error");
	return WIFEXITED(res) && WEXITSTATUS(res);
}


int call_cmd(char **av)
{
	int i = 0;
	int j = 0;
	char *env[4028];

	*env = ft_getpath(av);

	while (av[i++])
	{
		printf("env in call cmd %s\n", *env);
		if ((j = ft_ex(env, av, i)) == 0)
			break;

	}
	return j;
}
