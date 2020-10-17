all: CaesarCypher.c 
	gcc -o cypher CaesarCypher.c

clean:
	rm cypher
