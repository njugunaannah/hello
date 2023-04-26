#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * read_command - Reads a command from the user input
 *
 * @cmd: Pointer to the buffer that will store the command string
 * @par: Pointer to the array that will store the command parameters
 *
 * This function reads a command from the user input and
 * stores it in the buffer
 * pointed by @cmd. The function also parses the
 * command into individual parameters
 * and stores them in the array pointed by @par.
 *
 * Return: void
 */

void read_command(char cmd[], char *par[])
{
char line[1024];
int count = 0, i = 0, j = 0;
char *array[100], *pch;

for (;;)
{
int c = fgetc(stdin);
line[count++] = (char) c;
if (c == '\n' || count > 1023)
{
break;
}
}
line[count] = '\0';

pch = strtok(line, " \n");

while (pch != NULL && i < 19)
{
array[i++] = strdup(pch);
pch = strtok(NULL, " \n");
}

strcpy(cmd, array[0]);

for (j = 0; j < i; j++)
{
par[j] = array[j];
}
par[j] = NULL;
}

/**
 * type_prompt - Displays the command prompt to the user
 *
 * This function displays the command prompt to the user. The prompt usually
 * contains information about the current directory, user information, or any
 * other relevant information that helps the user interact with the system.
 *
 * Return: void
 */

void type_prompt(void)
{
static int first_time = 1;
if (first_time)
{
/*const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";*/
	const char *CLEAR_SCREEN_ANSI = "\033[1;1H\033[2J";
write(STDERR_FILENO, CLEAR_SCREEN_ANSI, 12);
first_time = 0;
}
printf("$ ");
}

/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(void)
{

/* char cmd[100];*/

char command[100];
char *parameters[20];

/*char *envp[] = { (char *) "PATH=C:\\Windows\\System32", NULL };*/

while (1)
{
type_prompt();
read_command(command, parameters);
if (strcmp(command, "exit") == 0)
{
break;
}
if (fork() != 0)
{
wait(NULL);
}
else
{
execvp(command, parameters);
printf("Unknown command: %s\n", command);
exit(1);
}
}
return (0);
}
