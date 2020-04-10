#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

void list(char *path, int archivedes);
int fsize(const char *path);
void writefile(const char *path, int archive);
void readfile(const char *path);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("too few args\n");
		printf("%lu", sizeof(-3));
		exit(-1);
	}
	printf("%s: %s\n", argv[1], argv[2]);
	if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0)
	{
		int archive = open(argv[3], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		writefile(argv[2], archive);
		list(argv[2], archive);
	}
	else if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--extract") == 0)
	{
		readfile(argv[2]);
	}
	printf("DONE");
	exit(0);
}

void list(char *basepath, int archivedes)
{
	char path[PATH_MAX + 1];
	struct dirent *dp;
	DIR *dir = opendir(basepath);

	if (!dir)
		return;

	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			strcpy(path, basepath);
			strcat(path, "/");
			strcat(path, dp->d_name);
			writefile(path, archivedes);
			list(path, archivedes);
		}
	}
	closedir(dir);
}

int fsize(const char *filename)
{
	struct stat st;
	if (stat(filename, &st) == 0)
	{
		if (S_ISREG(st.st_mode))
			return st.st_size;
		else
			return 0;
	}
	return -1;
}

void writefile(const char *path, int archive)
{
	printf("%s - %ld | ", path, strlen(path));

	int dir = 0;
	long len = strlen(path);
	int file = open(path, O_RDONLY);
	int flen = fsize(path);
	char buf;
	
	write(archive, &len, sizeof(len));
	write(archive, path, len);
	printf(" size: %d\n", flen, sizeof(flen));
	if (flen > 0)
	{
		write(archive, &flen, sizeof(flen));
		while (read(file, &buf, sizeof(buf)) == 1)
			write(archive, &buf, 1); 
	}
	else if (flen == 0) write(archive, &dir, sizeof(dir));
    
	close(file);
}

void readfile(const char *path)
{
	int archive = open(path, O_RDONLY);
	int byteread = 1;
	long pathsize = 0;
	int fsize = 0;
	int fdes = 0;
	char filepath[PATH_MAX + 1];
	char buf;
	while (byteread > 0)
	{
		printf("Extracting: ");
		byteread = read(archive, &pathsize, sizeof(pathsize));
		printf(" %d (%ld)", pathsize, sizeof(pathsize));
		
		read(archive, filepath, pathsize);
		
		read(archive, &fsize, sizeof(fsize));
		printf(" %d (%ld)\n", fsize, sizeof(fsize));
		
		if (fsize == 0)
		{
			printf(" %s\n", filepath);
		    mkdir(path, S_IRWXU | S_IRWXG);
		}
		else
		{
			fdes = open(filepath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			int fread = 0;
			while (read(archive, &buf, 1) && fread < fsize)
			{
				fread++;
				write(fdes, &buf, 1);
			}
			printf(" %s\n", filepath);
			close(fdes);
		}
	}
}
