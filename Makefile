run: main.out
	./main.out 

main.out: main.c
	gcc main.c -o main.out -lgmp

clean:
	rm main.out