test: dist/test
	./dist/test

dist/test: dist/test.o dist/Events.o dist/Task.o dist/Promise.o
	gcc -o $@ $^ -pthread -lrt

dist/test.o: src/test.c
	gcc -c -o $@ $^

dist/Promise.o: src/lib/Promise.c
	gcc -c -o $@ $^

dist/Events.o: src/lib/Events.c
	gcc -c -o $@ $^

dist/Task.o: src/lib/Task.c
	gcc -c -o $@ $^

dist/Promise.o: src/lib/Promise.c
	gcc -c -o $@ $^

clean:
	rm -fv dist/*
