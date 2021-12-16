othello: othello.o othello_func.o
	gcc -o $@ $^

othello.o: othello.c 
	gcc -c -o $@ $^

othello_func.o: othello_func.c 
	gcc -c -o $@ $^


clean:
	rm -rf othello 