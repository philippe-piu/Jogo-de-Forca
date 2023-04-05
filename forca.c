#include<stdio.h>
#include<string.h>

//Jogo da Forca
int main()
{
	char palavrasecreta[20], chute, chutestentativas[26];
	//sprintf é uma String printf
	sprintf(palavrasecreta, "MELANCIA");

	int acertou, enforcou, i, j, tentativas, achou;
	acertou = 0;
	enforcou = 0;
	i = 0;
	j = 0;
	tentativas = 0;


	printf("*********************************\n");
	printf("*Bem Vindo a nosso Jogo da Forca*\n");
	printf("*********************************\n");
	printf("\n");
	do
	{
		//Loop para o tamanho da palavra secreta
		for(i = 0; i < strlen(palavrasecreta); i++)
		{
			achou = 0;
			for(j = 0; j < tentativas; j++)
			{
				if(chutestentativas[j] == palavrasecreta[i])
				{
					achou = 1;
					break;
				}
			}

			if(achou)
			{
				printf("%c ", palavrasecreta[i]);
			}
			else
			{
				printf("_ ");
			}
		}

		printf("\n");
		printf("\nInforme uma letra para forca: ");
		scanf(" %c", &chute);

		chutestentativas[tentativas] =  chute;
		tentativas++;

	}
	while(!acertou && !enforcou);
	//Quando tem isso !acertou ele assume como um booleano true e false
	return(0);
}


