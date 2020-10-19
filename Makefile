test: dist/main
	./dist/main

dist/main: dist/main.o dist/Events.o dist/Task.o
	gcc -o $@ $^

dist/main.o: src/main.c
	gcc -c -o $@ $^

dist/Events.o: src/lib/Events.c
	gcc -c -o $@ $^

dist/Task.o: src/lib/Task.c
	gcc -c -o $@ $^

clean:
	rm -fv dist/main
	rm -fv dist/main.o
	rm -fv dist/Events.o
	rm -fv dist/Task.o
