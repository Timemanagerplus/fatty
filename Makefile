SHELL=cmd
fatty.exe:fatty.o fattylib.o
	gcc fatty.o fattylib.o -o fatty.exe
fatty.o:fatty.s
	gcc -c fatty.s -o fatty.o
fattylib.o:fattylib.s
	gcc -c fattylib.s -o fattylib.o
fatty.s:fatty.c
	gcc -S fatty.c -o fatty.s
fattylib.s:fattylib.c
	gcc -S fattylib.c -o fattylib.s
clear:
	rm .\fatty.s 