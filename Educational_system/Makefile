all:main.o admin.o teacher.o student.o tools.o
	gcc -o edu.bin main.o admin.o teacher.o student.o tools.o

main.o:main.c student.h teacher.h admin.h tools.h
	gcc -c main.c

admin.o:student.h teacher.h admin.c admin.h tools.h
	gcc -c admin.c

student.o:student.c student.h teacher.h admin.h tools.h
	gcc -c student.c

teacher.o:student.h teacher.c teacher.h admin.h tools.h
	gcc -c teacher.c

clean:
	rm -rf main.o admin.o teacher.o student.o tools.o edu.bin

