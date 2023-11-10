# include "../../includes/minishell.h"

/*Restores the original attributes of the terminal before any modification.*/
void	restore_attributes(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &use_data()->old_attributes);
}

/*Before disabling the Ctrl+C echo from the terminal's attributes, we first
get the original attributes and make a copy of them so we can restore it 
before exiting the program.
Then we disable the ECHOCTL and set our new attributes with this new rule.*/
void	disable_ctrlc(void)
{
	tcgetattr(STDIN_FILENO, &use_data()->old_attributes);
	use_data()->new_attributes = use_data()->old_attributes;
	use_data()->new_attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &use_data()->new_attributes);
}
