all_without_interface: user.o hachage.o liste.o main_sans_interface.o
	gcc hachage.o main_sans_interface.o user.o liste.o -o all_without_interface

all_w_interface: user.o hachage.o liste.o main_avec_interface.o
	gcc hachage.o main_avec_interface.o user.o liste.o -o all_w_interface `pkg-config --libs gtk+-3.0`

main_avec_interface.o: main_avec_interface.c hachage.h user.h liste.h
	gcc `pkg-config --cflags gtk+-3.0` -c main_avec_interface.c

main_sans_interface.o: main_sans_interface.c hachage.h user.h liste.h
	gcc -c main_sans_interface.c

liste.o: liste.c liste.h hachage.h user.h
	gcc -c liste.c

hachage.o: hachage.c hachage.h user.h liste.h
	gcc -c hachage.c

user.o: user.c user.h hachage.h liste.h
	gcc -c user.c

clean: 
	rm -rf *.o

mrproper: clean
	rm -rf main	
