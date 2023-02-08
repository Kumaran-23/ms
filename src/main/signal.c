#include "../include/minishell.h"

//ctrl c = sigint (intrrup process) ---> new prompt  || done!
//ctrl \ = sigquit (quit process) ---->nothing   |||done!
//ctrl z = sigstp ()
//ctrl d = eof --> exit || done!

void sig_handler(int signum)
{
	printf("%d done", signum);
}

void disable_veof(void)
{
	struct termios ori_settings;

    tcgetattr(STDIN_FILENO, &ori_settings);
    struct termios new_settings = ori_settings;
    new_settings.c_cc[VEOF] = 3;
	new_settings.c_cc[VINTR] = 4;
	
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void define_signal(void)
{

	signal(SIGQUIT, SIG_IGN);
	disable_veof();
}