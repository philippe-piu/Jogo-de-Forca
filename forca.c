#include<stdio.h>
#include<string.h>

char palavrasecreta[20];
char chutestentativas[26];
int tentativas = 0;

//Funções
void apresentacao();
void chuta(char chutestentativas[26], int *tentativas);
int jachutou(char letra);
void desenhaforca();
void escolhasecreta();

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
		chuta(chutestentativas, &tentativas);
		
	}
	while(!acertou && !enforcou);
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
void chuta(char chutestentativas[26], int *tentativas)
{
	char chute;
	printf("\nInforme uma letra para forca: ");
	scanf(" %c", &chute);
	chutestentativas[(*tentativas)] =  chute;
	(*tentativas)++;
}

//Se você chutou
int jachutou(char letra)
{
	int j, achou = 0;

	for(j = 0; j < tentativas; j++)
	{
		if(chutestentativas[j] == letra)
		{
			achou = 1;
			break;
		}
	}
	
	return(achou);
}

//Desenho da forca
void desenhaforca()
{
	int i;
	printf("\n");
	
	printf("Voce deu %d chutes\n", tentativas);

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

//Palavra secreta
void escolhasecreta()
{
	sprintf(palavrasecreta, "MELANCIA");
}


