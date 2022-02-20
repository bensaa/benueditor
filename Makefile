
OBJECTS= obj/characters.o obj/commands.o obj/globals.o obj/input.o obj/main.o obj/renderer.o obj/split.o obj/windowclass.o obj/keybindings.o



CFLAGS=`pkg-config gtkmm-3.0 --cflags --libs gio-unix-2.0`

output: $(OBJECTS)
	g++ $(OBJECTS) -O2 -o benu $(CFLAGS)

obj/characters.o: characters.cpp characters.h
	g++ -c characters.cpp -o obj/characters.o

obj/commands.o: commands.cpp split.h globals.h commands.h renderer.h input.h
	g++ -c commands.cpp -o obj/commands.o $(CFLAGS)

obj/globals.o: globals.cpp globals.h split.h windowclass.h
	g++ -c  globals.cpp -o obj/globals.o $(CFLAGS)

obj/input.o: input.cpp globals.h renderer.h input.h commands.h keybindings.h
	g++ -c  input.cpp -o obj/input.o $(CFLAGS)

obj/main.o: main.cpp globals.h windowclass.h input.h commands.h
	g++ -c   main.cpp -o obj/main.o $(CFLAGS)

obj/renderer.o: renderer.cpp renderer.h split.h characters.h
	g++ -c  renderer.cpp -o obj/renderer.o $(CFLAGS)

obj/split.o: split.cpp globals.h renderer.h input.h commands.h
	g++ -c   split.cpp -o obj/split.o $(CFLAGS)

obj/windowclass.o: windowclass.cpp windowclass.h globals.h renderer.h
	g++ -c   windowclass.cpp -o obj/windowclass.o $(CFLAGS)

obj/keybindings.o: keybindings.cpp keybindings.h globals.h commands.h input.h
	g++ -c   keybindings.cpp -o obj/keybindings.o $(CFLAGS)

run: output
	./benu

clean:
	rm benu
	rm obj/*
