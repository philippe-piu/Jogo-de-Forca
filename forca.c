#include<stdio.h>
#include<string.h>
#include "forca.h"

//Variaveis Globais
char palavrasecreta[20];
char chutestentativas[26];
int chutesdados = 0;

//Jogo da Forca
int main()
{
	int acertou, enforcou;
	acertou = 0;
	enforcou = 0;

	apresentacao();
	escolhasecreta();

	do
	{
		desenhaforca();
		chuta(chutestentativas, &chutesdados);

	}
	while(!acertouusuario() && !enforcouusuario());
	//Quando tem isso !acertou ele assume como um booleano true e false
	return(0);
}

//Função de apresentação Inicial
void apresentacao()
{
	printf("*********************************\n");
	printf("*Bem Vindo a nosso Jogo da Forca*\n");
	printf("*********************************\n");
	printf("\n");
}


//Chute do Usuario
void chuta(char chutestentativas[26], int *chutesdados)
{
	char chute;
	printf("\nInforme uma letra para forca: ");
	scanf(" %c", &chute);
	chutestentativas[(*chutesdados)] =  chute;
	(*chutesdados)++;
}

//Se você chutou
int jachutou(char letra)
{
	int j, achou = 0;

	for(j = 0; j < chutesdados; j++)
	{
		if(chutestentativas[j] == letra)
		{
			achou = 1;
			break;
		}
	}

	return(achou);
}

//Função do Desenho da forca
void desenhaforca()
{
	int i;
	printf("\n");

	printf("Voce deu %d chutes\n", chutesdados);

	for(i = 0; i < strlen(palavrasecreta); i++)
	{
		if(jachutou(palavrasecreta[i]))
		{
			printf("%c ", palavrasecreta[i]);
		}
		else
		{
			printf("_ ");
		}
	}
	printf("\n");

}

//Função da Palavra secreta
void escolhasecreta()
{
	int i;
	FILE *f;
	//Pegando arquivo com as palavras secretas
	f = fopen("palavrasecreta.txt","r");
	
	if(f == 0){
		printf("Banco de Dados não disponivel no momento tente mais tarde\n");
		exit(1);
	}
	
	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);
	
	srand(time(0));
	//não tem nada ver com numeros é so um nome de variavel
	int numerorandomico = rand() % qtddepalavras;
	
	for(i =0; i < numerorandomico; i++){
		fscanf(f, "%s", palavrasecreta);
	}
	
	//Fechando arquivo com as palavras secretas
	fclose(f);
}

//Função de finalização de jogo se usuario perdeu
int enforcouusuario()
{
	int i, j, existe, erros;
	erros = 0;

	//Loop em todos os chutes do usuario
	for(i = 0; i < chutesdados; i++)
	{
		existe = 0;
		
		//Aqui estou verificando quantas letras existem na palavra secreta e se ela é igual a o chute do usuario
		for(j = 0; j < strlen(palavrasecreta); j++)
		{
			//Se a palavra foi encontrada quebro o loop
			if(chutestentativas[i] == palavrasecreta[j])
			{
				existe = 1;
				break;
			}
		}
		//Aqui verifico as palavras que não existem na palavra secreta
		if(!existe) erros++;
	}
		
	//Se o erros for maior ou igual a 5 Jogador perdeu
	return erros >= 5;
}

//Função finaliza o jogo caso usuario ganhou
int acertouusuario(){
	int i;
	for(i = 0; i < strlen(palavrasecreta); i++){
		//Se o usuario não chutou a palavra secreta retorna 0
		if(!jachutou(palavrasecreta[i])){
			return 0;
		}
	}
	
	//Se usuario já acertou todas as palavras retorno 1 para acabar o jogo
	
	return 1;
}