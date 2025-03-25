#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[])
{
    char **ev;
    for(ev = environ; *ev != NULL; ev++)
    {
        printf("\n%s",*ev);
    }

    putenv("MY_ENV_VAR=SitaRam");
    printf("\n The value at HOME variable is %s\n", getenv("HOME"));
    printf("\n The value at newly created env variable is %s\n", getenv("MY_ENV_VAR"));

    return 0;
}