compile:
	clear
	gcc -Wall -g3 -fsanitize=address archive.c -o archive
check:
	clear
	cppcheck --enable=all --inconclusive --std=posix archive.c
