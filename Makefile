paint: main.c graphics.h bitmap.h
	gcc main.c -o paint -lSDL2

clean:
	rm paint
