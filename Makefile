CC= g++ -Wall -Wextra -Werror -std=c++11
OBJ= main.o mediamanager.o


tetravex: $(OBJ)
	$(CC) -o $@ $?


clean:
	rm -f tetravex *.o
