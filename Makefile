build:
	gcc -Wall main.c -o main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lGL -lX11

run:
	./main

clean:
	rm main
