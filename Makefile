IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -std=c++11 -O0

ODIR=.

LIBS=-lncurses

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ1 = issue.o
_OBJ2 = jira.o
_OBJ3 = main.o
_OBJ4 = project.o
_OBJ5 = sprint.o
_OBJ6 = teamMember.o



$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: issue jira main project sprint teamMember
	
issue: $(_OBJ1)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

jira: $(_OBJ2)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

main: $(_OBJ3)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

project: $(_OBJ4)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

sprint: $(_OBJ5)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

teamMember: $(_OBJ6)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)





.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f issue
	rm -f jira
	rm -f main
	rm -f project
	rm -f sprint
	rm -f *.o

etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append         
