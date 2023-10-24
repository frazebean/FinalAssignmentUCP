CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
OBJ = main.o game_initialisation.o game_display.o terminal.o game_movement.o
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c game_initialisation.h map_struct.h game_display.h constants.h terminal.h
	$(CC) $(CFLAGS) -c main.c

game_initialisation.o : game_initialisation.c game_initialisation.h map_struct.h
	$(CC) $(CFLAGS) -c game_initialisation.c

game_display.o : game_display.c game_display.h map_struct.h
	$(CC) $(CFLAGS) -c game_display.c

terminal.o : terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

game_movement.o : game_movement.c game_movement.h map_struct.h
	$(CC) $(CFLAGS) -c game_movement.c

clean:
	rm -f $(EXEC) $(OBJ)