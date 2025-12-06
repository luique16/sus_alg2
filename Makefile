all:
	mkdir -p build
	gcc -o build/sus_alg src/* main.c

debug:
	mkdir -p build
	gcc -fsanitize=address -o build/sus_alg src/* main.c

run:
	./build/sus_alg

clean:
	rm -rf build

data:
	echo "[]" > list.json
	echo "[]" > queue.json
