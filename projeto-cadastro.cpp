#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include<iostream>

struct modelo {  
	char modelo[10];
	char cor[10];
	char status;
	int id;
};

int tam(FILE*);
void cadastrar(FILE *);
void consultar(FILE *);
void arquivotxt(FILE *);
void excluir(FILE *);
void cabecalho ();

int main (void) {
	int op;
	FILE *arq;
	setlocale(LC_ALL, "Portuguese");
	
	if ((arq = fopen("trabalho-final", "rb+")) == NULL)
	{
		if ((arq = fopen("trabalho-final", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}
	
	do{  //usamos o do para que garanta que o codigo execute pelo menos 1 vez
		cabecalho ();
		printf("Menu de opção:\n");
		printf("1-Cadastrar:\n");
		printf("2- Consultar: \n");
		printf("3- Gerar txt:\n");
		printf("4- Excluir: \n");
		printf("5-Sair: \n");
		printf("Digite a opção desejada:\n");
		scanf("%d",&op);
		switch (op) //esse comando teste a variavel e verifica se ela corresponde ao case pré definido 
		{
		case 1:
			cadastrar(arq);
			break;
		case 2:
			consultar(arq);
			break;
		case 3:
			arquivotxt(arq);
			break;
		case 4:
			excluir(arq);
			break;
		case 5: fclose(arq);
		break;
		}
	}while(op!=5);		
	return 1;
}

void cadastrar (FILE*arq)
{
	int i;
	modelo celular;
	celular.status = 'D';
	char confirma;
	fflush(stdin);
		
	printf("---------------------------------------------------- \n");
	printf("Estoque de mercadoria\n");
	printf("------------------------------------------------\n");
	
	printf("Id do modelo: %i \n",tam(arq)+1); //gera o id automatico do 
	
	printf("Digite o modelo do aparelho: \n");
	fflush(stdin);
	gets(celular.modelo);
	
	printf("Digite a cor do aparelho:\n");
	fflush(stdin);
	gets(celular.cor);
		
	printf("\nDeseja cadastrar esse aparelho?(S/N):");
	fflush(stdin);
	scanf("%c", &confirma);
	
		
	
	if (toupper(confirma) == 'S')
	{
		printf("\Aparelho cadastrado!!\n\n");
		fseek(arq, 0, SEEK_END); //permite apontar o indicador para um registro qualquer dentro do arquivo.
		fwrite(&celular, sizeof(modelo), 1, arq); //escrever no arquivo
	}
	
	
}
void consultar (FILE*arq) {
	
	modelo celular;
	int num;
	
	printf("\nInforme o Id para consultar: ");
	scanf("%d", &num);

	
	if ((num <= tam(arq)) && (num>0))
	{
		fseek(arq, (num - 1) * sizeof(modelo), SEEK_SET);
		fread(&celular, sizeof(modelo), 1, arq); //função de leitura do arquivo
		if(celular.status == 'D') 
		{
			printf("\n modelo: %s", celular.modelo);
			printf("\n cor: %s", celular.cor);
			printf("\n status: %c\n\n",celular.status);
		}
		else
		{
			printf("Esse aparelho está indisponível no estoque.");
		}
		
	}
	else
	{
		printf("\nId invalido!\n");
	}
	system("pause");	
}

void arquivotxt(FILE *arq)
{
	char nome[20];
	int num;
	modelo celular;
	
	printf("Nome do arquivo texto:");
	scanf("%s", nome);
	strcat(nome, ".txt"); //função que concatena
	FILE *arqtxt = fopen(nome, "w"); //abre e cria um arquivo para escrita
	if (!arqtxt) //negação
	{
		printf("Nao foi possivel criar esse arquivo!\n");
		system("pause");
	}
	fprintf(arqtxt, "Modelo                Cor               Status             \n"); //permite escrita dos dados
	fprintf(arqtxt, "-------------------------------------------------------------\n");

	for (num = 0; num<tam(arq); num++) //analisando o arquivo 
	{
		fseek(arq, num* sizeof(modelo), SEEK_SET);
		fread(&celular, sizeof(modelo), 1, arq);
		fprintf(arqtxt, "%-20s%-22s%-25c-\n", celular.modelo, celular.cor, celular.status);
	}
	fprintf(arqtxt, "----------------------------------------------------------------\n");
	fclose(arqtxt);
}

void excluir(FILE *arq)
{
	modelo celular;
	char confirma;
	int num;

	printf("\nInforme o Id que deseja excluir:\n");
	fflush(stdin);
	scanf("%d", &num);
	
	if ((num <= tam(arq)) && (num>0))
	{
		fseek(arq, (num - 1) * sizeof(modelo), SEEK_SET);
		fread(&celular, sizeof(modelo), 1, arq);
		fflush(stdin);
		
		if (celular.status == 'D') //compara os status que estao disponivel
		{
			printf("\nModelo......:%s", celular.modelo);
			printf("\nCor..:%s", celular.cor);
			printf("\nStatus....:%c\n",celular.status);
			printf("\nDeseja excluir(S/N)\n");
			scanf(" %c", &confirma);

			if (toupper(confirma) == 'S') //converte minusculo para maisculo e vice versa
			{
				printf("\nExcluindo aparelho do estoque...\n\n");
				celular.status = 'I'; //vai receber I d eindisponivel
				fseek(arq, (num - 1) * sizeof(modelo), SEEK_SET);
				fwrite(&celular, sizeof(modelo), 1, arq);
			}
		}
		else
			printf("\nEsse celular está indisponível no estoque \n");
	}
	else
	{
		printf("\nNumero invalido!\n");
	}
	system("pause");

}
int tam(FILE *arq) 
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(modelo);
}

void cabecalho (){ //criou uma função para exibir no menu
	system("cls"); // limpa a tela
	printf("-------------------------------------------------------- \n");
	printf("CADASTRO DE APARELHOS ELETRÔNICOS \n");
	printf("-------------------------------------------------------- \n \n");
}
