#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


FILE* abrir_arquivo (char *fname)
{
	FILE *arquivo;

	arquivo = fopen(fname, "rb+");

	if (arquivo == NULL) {
		arquivo = fopen(fname, "wb");

		if (arquivo == NULL) {
			printf("impossivel criar arquivo %s\n", fname);
			exit(1);
		}

		fclose(arquivo);

		arquivo = fopen(fname, "rb+");

		if (arquivo == NULL) {
			printf("impossivel abrir arquivo %s\n", fname);
			exit(1);
		}
	}

	return arquivo;
}

struct Cliente {
	int codigo;
	char nome [100];
	int anoNasimento;
	char email [100];

};

struct Produto {
	int codigo;
	char descricao[100];
	double valor;
};

struct Venda {
	int codigo;
	int produto_codigo;
	int cliente_codigo;
};



void inserirProduto() {
	FILE *arquivo;
	int n;

	Produto produto;
	arquivo = abrir_arquivo("produto.dat");

	cout << " Informe o codigo do Produto " << endl;
	cin >> produto.codigo;

	cout << "Informe a descrição" << endl;
	cin >> produto.descricao;

	cout << "Informe o valor " << endl;
	cin >> produto.valor;

	fseek(arquivo, 0, SEEK_END);
	fwrite(&produto, sizeof(Produto),1,arquivo);
	fclose(arquivo);

}


void inserirCliente ()
{
	FILE *arquivo;
	int n;

	Cliente cliente;

	arquivo = abrir_arquivo("cliente.dat");

	cout <<"informe o id"<<endl;
	cin>> cliente.codigo;

	cout <<"informe nome do cliente "<<endl;
	cin>> cliente.nome;

	cout <<"digite ano de nasimento"<<endl;
	cin>> cliente.anoNasimento;

	cout <<"informe seu email"<<endl;
	cin>>cliente.email;


	fseek(arquivo, 0, SEEK_END);
	fwrite(&cliente, sizeof(Cliente), 1, arquivo);
	fclose(arquivo);
}

void listar_produto()
{
	FILE *arquivo;
	Produto buffer[100];
	int n;

	arquivo = abrir_arquivo("produto.dat");
	fseek(arquivo, 0, SEEK_SET);
	n = fread(buffer, sizeof(Produto), 100, arquivo);

	cout << "------Lista de Produtos---------- " << endl;

	for (int i = 0; i < n; i++)
	{
		cout << buffer[i].codigo << " - " << buffer[i].descricao << endl;

	}

	fclose(arquivo);

}

void listar_cliente()
{

	FILE *arquivo;
	Cliente buffer[100];
	int n;

	arquivo = abrir_arquivo("cliente.dat");
	fseek(arquivo, 0, SEEK_SET);
	n = fread(buffer, sizeof(Cliente), 100, arquivo);

	cout << "--------------------- Lista de clientes      ---------------------" << endl;
	for(int i = 0; i < n; i++){
		cout << buffer[i].codigo << " - " << buffer[i].nome << endl;
	}

	fclose(arquivo);

}

void alterar_cliente()
{
	FILE *arquivo;
	Cliente cliente;
	int codigo;


	cout << "Digite o id do cliente para alterar" << endl;
	cin >> codigo;

	arquivo = abrir_arquivo("cliente.dat");
	while(fread(&cliente, sizeof(Cliente), 1, arquivo)){
		if(cliente.codigo == codigo){
			fseek(arquivo, sizeof(Cliente) * -1 , SEEK_CUR);

			cout << "Digite o novo nome" << endl;
			cin >> cliente.nome;


			fwrite(&cliente, sizeof(Cliente), 1, arquivo);
		}
	}
	fclose(arquivo);

}

int main ()
{
	listar_cliente();
	inserirCliente();
	inserirCliente();
	inserirCliente();
	inserirCliente();
	listar_cliente();
	alterar_cliente();
	listar_cliente();


	return 0;
}
