CC= g++ -Wall -Wextra -Werror -std=c++11
OBJ= mediamanager.o utils.o main.o solve.o test.o


tetravex: ${OBJ:.o=.cc} $(OBJ)
	$(CC) -o $@ $(OBJ)


clean:
	rm -f tetravex *.o
