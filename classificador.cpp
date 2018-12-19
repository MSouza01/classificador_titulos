#include <iostream>
#include <string>
#include <vector>

/* 	Definições para deixar o código mais legível
*	Na função "classifica_titulos", há uma variável de tipo char que contém a classificação de cada título
*	Esse char assume valor 'S' caso o título seja classificado como Smartphone ou 'N' caso contrário
*/
#define	SMARTPHONE	'S'
#define	N_SMARTPHONE	'N'

using namespace std;

/*
*	Função que lê um arquivo, caracter por caracter, até o fim de arquivo ou até o separador passado como parâmetro.
*	O texto lido é retornado como uma String.
*/
string le_linha(FILE *fp, char sep) {
	char c;
	string str;
	do {
		fread(&c, sizeof(char), 1, fp);
		if(!feof(fp) and c != sep)
			str.append(1, c);
	} while(!feof(fp) and c != sep);
	return str;
}

/*
*	Função que retorna a string passada como parâmetro com todos os caracteres maiúsculos.
*	Isto facilita as comparações na função "smartphone"
*/
string uppercase(string str) {
	int tam = str.length();
	string nova_str;
	
	for(int i = 0; i < tam; i++) {
		nova_str.append(1, toupper(str[i]));
	}
	return nova_str;
}

/*
*	Função que busca as substrings do vetor substr na string titulo.
*	É retornado o menor índice em que uma substring é encontrada.
*	Caso nenhuma substring seja encontrada, é retornado -1.
*/
int min_sub_string_pos(string titulo, vector<string> substr) {
	int i, min = 1000, pos;
	for(i = 0; i < substr.size(); i++) {
		pos = titulo.find(substr[i]);
		if(pos != -1 and pos < min)
			min = pos;
	}
	if(min == 1000)
		return -1;
	return min;
}

/*
*	Função que classifica o título como sendo de smartphone ou não.
*/
char smartphone(string titulo) {
	int pos1, pos2, pos3;
	
	// A pos1 se refere ao menor índice das substrings que classificam o título como sendo de smartphone
	pos1 = min_sub_string_pos(titulo, {"SMARTPHONE","CELULAR","MOTOROLA","MOTO G","MOTO X","MOTO C","MOTO E","MOTO Z","IPHONE",
			"LG L","LG G","LG T","LG K","LG Q","XPERIA","ZENFONE","GALAXY","XIAOMI","NOKIA"});
	// A pos2 se refere ao menor índice das substrings que classificam o título como não sendo smartphone se vierem antes da pos1
	pos2 = min_sub_string_pos(titulo, {"PELíCULA","PELICULA","CAPA","CABO","BUMPER","BRACADEIRA","BRAçADEIRA",
			"SUPORTE","PROTETOR","TABLET","PARA","KIT","LENTE","CARREGADOR", "REPETIDOR", "MIRROR CAST",
			"ADESIVO", "BUMBER"});
	// A pos3 se refere ao menor índice das substrings que classificam o título como não sendo smartphone
	pos3 = min_sub_string_pos(titulo, {"GALAXY TAB"});
	
	if(pos3 >= 0 or (pos2 >= 0 and pos2 < pos1))
		return N_SMARTPHONE;
	if(pos1 >= 0)
		return SMARTPHONE;
	return N_SMARTPHONE;
}

/*
*	Função que lê o arquivo .tsv com os títulos e os classifica um por um, imprimindo-os com suas respectivas classificações.
*/
void classifica_titulos() {
	string id, titulo, TITULO;
	FILE *fp;
	char classificacao;
	
	fp = fopen("data_estag_ds.tsv", "r");
	if(fp == NULL) {
		cout << "\nNão foi possível abrir o arquivo.\n";
		exit(-1);
	}
	
	titulo = le_linha(fp, '\n');
	cout << titulo << "\tSMARTPHONE\n";
	titulo.clear();
	
	while(!feof(fp)) {
		id = le_linha(fp, '\t');
		titulo = le_linha(fp, '\n');
		
		TITULO = uppercase(titulo);
		
		classificacao = smartphone(TITULO);
		
		cout << id << "\t" << titulo << "\t" << classificacao <<"\n";
		
		id.clear();
		titulo.clear();
		TITULO.clear();
	}
	
	fclose(fp);
}

int main(int argc, char **argv) {
	classifica_titulos();
	
	return 0;
}
