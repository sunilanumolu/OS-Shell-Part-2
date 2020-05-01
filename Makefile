
output: my_Shell.o Ls.o Pinfo.o Signal_handlr.o Exec.o Pro_strng.o Builtin.o Redirect.o
	gcc my_Shell.o Ls.o Pinfo.o Signal_handlr.o Exec.o Pro_strng.o Builtin.o Redirect.o -lreadline -o output

my_Shell.o: my_Shell.c Main.h
	gcc -c my_Shell.c -lreadline

Ls.o: Ls.c Main.h
	gcc -c Ls.c

Pinfo.o: Pinfo.c Main.h
	gcc -c Pinfo.c

Signal_handlr.o: Signal_handlr.c Main.h
	gcc -c Signal_handlr.c

Exec.o: Exec.c Main.h
	gcc -c Exec.c

Pro_strng.o: Pro_strng.c Main.h
	gcc -c Pro_strng.c

Builtin.o: Builtin.c Main.h
	gcc -c Builtin.c

Redirect.o : Redirect.c Main.h
	gcc -c Redirect.c

clean: 
	rm *.o output