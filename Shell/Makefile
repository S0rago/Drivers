compile:
	clear
	gcc -Wall -g3 -fsanitize=address shell.c -o shell
check:
	clear
	cppcheck --enable=all --inconclusive --std=posix shell.c
