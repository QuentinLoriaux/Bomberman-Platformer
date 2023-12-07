CC=g++
CFLAGS = -Wall  -I include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJ = main

all : Bomberman_Plat

Bomberman_Plat : $(addsuffix .o, $(addprefix obj/,$(OBJ)))
	$(CC) $^ -o $@ $(LDFLAGS)  

obj/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ 

run:
	./Bomberman_Plat