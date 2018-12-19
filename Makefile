make:
	g++ -o classificador classificador.cpp
	
run:
	./classificador
	
write_file:
	./classificador > titulos_classificados.tsv
