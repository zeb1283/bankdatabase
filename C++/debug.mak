project_debug: user-interface.o llist.o
	g++ -o project_debug user-interface.o llist.o

user-interface.o: user-interface.cpp record.h llist.h 
	g++ -ansi -pedantic-errors -Wall -DDEBUG -c user-interface.cpp

llist.o: llist.cpp llist.h record.h
	g++ -ansi -pedantic-errors -Wall -DDEBUG -c llist.cpp
