#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(void)
{
	DIR *dirstream;
	struct dirent *direntry;

	dirstream = opendir ("./");
	if (! dirstream)
	{
		perror ("Não pude abrir esse diretorio\n");
		//exit(1);
	}
	while (direntry = readdir (dirstream))
		puts (direntry->d_name);
	(void)closedir (dirstream);
	//exit (0);
}