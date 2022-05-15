all: clean inicializador productor espia finalizador

inicializador:
	gcc inicializador.c -o inicializador
	
productor:
	gcc productor.c -o productor
	
espia:
	gcc espia.c -o espia
	
finalizador:
	gcc finalizador.c -o finalizador
	
clean:
	- rm inicializador
	- rm productor
	- rm espia
	- rm finalizador

