#include<stdio.h>
#include<string.h>
#include "forca.h"

//Variaveis Globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutestentativas[TAMANHO_CHUTE_TENTATIVAS];
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

	msgfinal();
	adicionarpalavra();

	return(0);
}

//Fun��o de apresenta��o Inicial
void apresentacao()
{
	printf("*********************************\n");
	printf("*Bem Vindo a nosso Jogo da Forca*\n");
	printf("*********************************\n");
	printf("\n");
}

//Fun��o de Finaliza��o do jogo
void msgfinal()
{
	if(acertouusuario())
	{
		printf("\nParabens voce ganhou o jogo\n");

		printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");
	}
	else
	{
		printf("\nGame Over\n");
		printf("A palavra era **%s**\n\n", palavrasecreta);
		
		printf("    _______________         \n");
		printf("   /               \\       \n");
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\_______/           \n");
	}
}

//Chute do Usuario
void chuta(char chutestentativas[TAMANHO_CHUTE_TENTATIVAS], int *chutesdados)
{
	char chute;
	printf("\nInforme uma letra para forca: ");
	scanf(" %c", &chute);
	chutestentativas[(*chutesdados)] =  chute;
	(*chutesdados)++;
}

//Se voc� chutou
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

//Fun��o do Desenho da forca
void desenhaforca()
{
	int i, erros = chuteserrados();
	printf("\n");

	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '),
		   (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
	printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '),
		   (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
	printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
	printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '),
		   (erros >= 4 ? '\\' : ' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

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

//Fun��o para usuario se caso quiser adicionar uma paravra secreta no arquivo palavrasecreta.txt
void adicionarpalavra()
{
	char resposta;

	printf("Gostaria de adicionar uma nova palavra secreta no jogo da forca ?\n");
	printf("S para sim e N para nao\n");
	scanf(" %c", &resposta);

	if(resposta == 'S')
	{
		char novapalavra[TAMANHO_PALAVRA];
		printf("Qual a nova palavra secreta ?\n");
		scanf("%s", &novapalavra);

		FILE *f;

		//r+ � leitura e escrita
		//Abrindo o arquivo de texto
		f = fopen("palavrasecreta.txt", "r+");

		if(f == 0)
		{
			printf("Banco de Dados n�o disponivel no momento tente mais tarde\n");
			//Fechando o programa
			exit(1);
		}

		//Ler quantidade do arquivo
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);

		fclose(f);
	}

}

//Fun��o da Palavra secreta
void escolhasecreta()
{
	int i;
	FILE *f;
	//Pegando arquivo com as palavras secretas
	f = fopen("palavrasecreta.txt", "r");

	if(f == 0)
	{
		printf("Banco de Dados n�o disponivel no momento tente mais tarde\n");
		//Fechando o programa
		exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);

	srand(time(0));
	//n�o tem nada ver com numeros � so um nome de variavel
	int numerorandomico = rand() % qtddepalavras;

	for(i = 0; i < numerorandomico; i++)
	{
		fscanf(f, "%s", palavrasecreta);
	}

	//Fechando arquivo com as palavras secretas
	fclose(f);
}

//Fun��o de chutes errados
int chuteserrados()
{
	int i, j, existe, erros;
	erros = 0;

	//Loop em todos os chutes do usuario
	for(i = 0; i < chutesdados; i++)
	{
		existe = 0;

		//Aqui estou verificando quantas letras existem na palavra secreta e se ela � igual a o chute do usuario
		for(j = 0; j < strlen(palavrasecreta); j++)
		{
			//Se a palavra foi encontrada quebro o loop
			if(chutestentativas[i] == palavrasecreta[j])
			{
				existe = 1;
				break;
			}
		}
		//Aqui verifico as palavras que n�o existem na palavra secreta
		if(!existe) erros++;
	}

	return erros;
}

//Fun��o de finaliza��o de jogo se usuario perdeu
int enforcouusuario()
{

	//Se o erros for maior ou igual a 5 Jogador perdeu
	return chuteserrados() >= 5;
}

//Fun��o finaliza o jogo caso usuario ganhou
int acertouusuario()
{
	int i;
	for(i = 0; i < strlen(palavrasecreta); i++)
	{
		//Se o usuario n�o chutou a palavra secreta retorna 0
		if(!jachutou(palavrasecreta[i]))
		{
			return 0;
		}
	}

	//Se usuario j� acertou todas as palavras retorno 1 para acabar o jogo

	return 1;
}

