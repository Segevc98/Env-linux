#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_BUFFER_LENGTH 50
#define MAX_PATH_LENGTH 100
int main()
{
	int i = 0, valid = 0;
	FILE *file;
	pid_t pid;
	char buffer[MAX_BUFFER_LENGTH];
	char cmd_path[MAX_PATH_LENGTH];
	char *token, *args[10], temp[MAX_PATH_LENGTH];
	while(1)
	{
		printf("~$ ");
		fgets(buffer, MAX_BUFFER_LENGTH, stdin); //get command from user
		buffer[strlen(buffer)-1] = '\0'; // change backslash n at the end
		if(strcmp(buffer, "leave") == 0) {
			break;
			}
		else {
			token = strtok(buffer, " "); //find spaces:
			i = 0;
			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			}
			strcpy(cmd_path, getenv("PATH"));
			token = strtok(cmd_path, ":");
			i = 0;
			valid = 0; // reset the flag
			while(token != NULL)
			{
				if(valid == 0)
				{
					strcpy(temp, token);
					strcat(temp, "/");
					strcat(temp, args[0]);
					if(file = fopen(temp, "r"))
					{
						fclose(file);
						valid = 1;
					}
				}
				token = strtok(NULL, ":");
			}
			if (valid == 1)
			{
				pid = fork();
				if(pid == 0)
				{
					execv(temp, args);
					printf("execv failed\n");
					exit(1);
				}
				else if (pid == -1)
				{
					printf("Fork failed\n");
				}
				else
				{
					wait(NULL);
				}
				
			}
			else
			{
				printf("%s: Not a valid command\n", args[0]);
			}
	}
}