all: clean inicializador productor espia finalizador

inicializador:
	gcc inicializador.c -o inicializador -pthread
	
productor:
	gcc productor.c -o productor -pthread
	
espia:
	gcc espia.c -o espia -pthread
	
finalizador:
	gcc finalizador.c -o finalizador -pthread
	
clean:
	- rm inicializador
	- rm productor
	- rm espia
	- rm finalizador

