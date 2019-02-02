char palavraReservada[12][10] = {"main", "function", "in", "out", "switch", "case", "break", "default", "foreach", "integer", "char", "float"};
/*main 0 - function 1 - in 2 - out 3 - switch 4 - case 5 - break 6
default 7 - foreach 8 - integer 9 - char 10 - float 11 */
char escopo[255];

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "memoria.h"
#include "lista.h"
#include "tabelaSimbolos.h"

void alterarValor(nodeTabelaSimbolo *simbolo, char *variavel, char *valor);
int verificaNome(nodeTabelaSimbolo *simbolo, char *variavel, char *palavra);

int main(void)
{
	char url[] = "lexico.txt", linha[500], *result, string, stringTmp;
	int localizacao = 1;
	int comparar, i, j, k, v, index, indexVariavel, indexFunction, indexValor, indexLimitadorChar, numeroLinha, asciiLetter;
	char palavra[255], variavel[255], valor[255], function[255],limitadorChar[20];
	int abreParentese = 40, fechaParentese = 41, espaco = 32, virgula = 44, pontoEvirgula = 59, igual = 61, abreChave = 123, fechaChave = 125, abreColchete = 91, fechaColchete = 93;
	int validaMain = 0, validaFunction = 0, variavelInserida = 0;

	FILE *arq;
	node *lista = (node *)malloc(sizeof(node));
	nodeTabelaSimbolo *listaSimbolo = (nodeTabelaSimbolo *)malloc(sizeof(nodeTabelaSimbolo));

	somaMemoria(sizeof(node));
	somaMemoria(sizeof(nodeTabelaSimbolo));

	listaSimbolo->prox = NULL;
	lista->prox = NULL;
	arq = fopen(url, "r");
	if (arq == NULL)
	{
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}
	else
	{
		while (!feof(arq))
		{
			result = fgets(linha, 500, arq);
			insere(lista, result, localizacao);
			localizacao++;
		}
	}
	fclose(arq);

	node *tmp = lista->prox;

	memset(linha, '\0', sizeof(linha));
	numeroLinha = 1;
	while (tmp != NULL)
	{
		i = 0;
		index = 0;
		strcpy(linha, tmp->linha);
		memset(palavra, '\0', sizeof(palavra));

		while ((int)linha[i] != 0)
		{
			asciiLetter = (int)linha[i];
			if ((asciiLetter != espaco) &&
				(asciiLetter != abreParentese) &&
				(asciiLetter != fechaParentese) &&
				(asciiLetter != virgula) &&
				(asciiLetter != pontoEvirgula) &&
				(asciiLetter != igual) &&
				(asciiLetter != abreChave) &&
				(asciiLetter != fechaChave) &&
				(asciiLetter != abreColchete) &&
				(asciiLetter != fechaColchete) &&
				(asciiLetter != 129))
			{
				palavra[index] = linha[i];
				index++;
			}
			else
			{

				if (palavra[0] == 'm' || palavra[0] == 'M')
				{
					if (strcmp(palavra, palavraReservada[0]) == 0) /*main*/
					{
						validaMain++;
						strcpy(escopo, palavraReservada[0]);
					}
					else
					{
						erro(0, numeroLinha);
					}
				}
				if (palavra[0] == 'f' || palavra[0] == 'F')
				{
					if (palavra[1] == 'u' || palavra[1] == 'U')
					{
						if (strcmp(palavra, palavraReservada[1]) == 0) /*function*/
						{
							validaFunction = 1;
							i = 9;
							indexFunction = 0;
							memset(function, '\0', sizeof(function));
							while ((int)linha[i] != 0)
							{
								asciiLetter = (int)linha[i];
								if ((asciiLetter != espaco) &&
									(asciiLetter != abreParentese) &&
									(asciiLetter != fechaParentese) &&
									(asciiLetter != pontoEvirgula))
								{
									function[indexFunction] = linha[i];
									indexFunction++;
								}
								else
								{
									if (function[0] == '!')
									{
										for (k = 1; (int)function[k] != 0; k++)
										{
											if (function[k] >= 'a' && function[k] <= 'z' || function[k] >= 'A' && function[k] <= 'Z' || function[k] >= '0' && function[k] <= '9')
											{
											}
											else
											{
												erro(4, numeroLinha);
											}
										}
									}
									else
									{
										erro(3, numeroLinha);
									}
									indexFunction = 0;
									strcpy(escopo, function);
									memset(function, '\0', sizeof(function));
									break;
								}
								i++;
							}
						}
						else
						{
							erro(5, numeroLinha);
						}
					}

					if (palavra[1] == 'o' || palavra[1] == 'O')
					{
						if (strcmp(palavra, palavraReservada[8]) == 0) /*foreach*/
						{
						}
						else
						{
							erro(1, numeroLinha);
						}
					}
					if (palavra[1] == 'l' || palavra[1] == 'L')
					{
						if (strcmp(palavra, palavraReservada[11]) == 0) /*float*/
						{
							indexVariavel = 0;
							memset(variavel, '\0', sizeof(variavel));
							while ((int)linha[i] != 0)
							{
								asciiLetter = (int)linha[i];
								if ((asciiLetter != espaco) &&
									(asciiLetter != pontoEvirgula) &&
									(asciiLetter != abreParentese) &&
									(asciiLetter != fechaParentese) &&
									(asciiLetter != igual))
								{
									variavel[indexVariavel] = linha[i];
									indexVariavel++;
								}
								else if (variavel[0] != 0 && variavelInserida == 0)
								{
									if (variavel[0] == '$')
									{
										if (variavel[1] >= 'a' && variavel[1] <= 'z')
										{
										}
										else
										{
											erro(8, numeroLinha);
										}

										for (k = 2; (int)variavel[k] != 0; k++)
										{
											if (variavel[k] >= 'a' && variavel[k] <= 'z' || variavel[k] >= 'A' && variavel[k] <= 'Z' || variavel[k] >= '0' && variavel[k] <= '9')
											{
											}
											else
											{
												erro(8, numeroLinha);
											}
										}
									}
									else
									{
										erro(7, numeroLinha);
									}
									if (palavra && variavel != NULL)
									{
										if(verificaNome(listaSimbolo, variavel, palavra) == 0)
										{
											insereTabelaSimbolo(listaSimbolo, palavra, variavel, escopo);
										}
										else
										{
											erro(12, numeroLinha);
										}
									}
									indexVariavel = 0;
									variavelInserida = 1;
								}
								else if (asciiLetter == igual)
								{
									indexValor = 0;
									memset(valor, '\0', sizeof(valor));
									i++;
									while ((int)linha[i] != 0)
									{
										asciiLetter = (int)linha[i];
										if ((asciiLetter != virgula) &&
											(asciiLetter != pontoEvirgula))
										{
											valor[indexValor] = linha[i];
											indexValor++;
										}
										else if (valor[0] != 0)
										{
											alterarValor(listaSimbolo, variavel, valor);
											break;
										}
										i++;
									}
								}
								i++;
							}
						}
						else
						{
							erro(10, numeroLinha);
						}
					}
					variavelInserida = 0;
					memset(variavel, '\0', sizeof(variavel));
				}
				if (palavra[0] == 'i' || palavra[0] == 'I')
				{
					if ((int)palavra[2] == 0)
					{
						if (strcmp(palavra, palavraReservada[2]) != 0) /*in*/
						{
							erro(1, numeroLinha);
						}
						else
						{
						}
					}
					else
					{
						if (strcmp(palavra, palavraReservada[9]) != 0) /*integer*/
						{
							erro(6, numeroLinha);
						}
						else
						{
							indexVariavel = 0;
							memset(variavel, '\0', sizeof(variavel));
							while ((int)linha[i] != 0)
							{
								asciiLetter = (int)linha[i];
								if ((asciiLetter != espaco) &&
									(asciiLetter != pontoEvirgula) &&
									(asciiLetter != abreParentese) &&
									(asciiLetter != fechaParentese) &&
									(asciiLetter != igual))
								{
									variavel[indexVariavel] = linha[i];
									indexVariavel++;
								}
								else if (variavel[0] != 0 && variavelInserida == 0)
								{
									if (variavel[0] == '$')
									{
										if (variavel[1] >= 'a' && variavel[1] <= 'z')
										{
										}
										else
										{
											erro(8, numeroLinha);
										}

										for (k = 2; (int)variavel[k] != 0; k++)
										{
											if (variavel[k] >= 'a' && variavel[k] <= 'z' || variavel[k] >= 'A' && variavel[k] <= 'Z' || variavel[k] >= '0' && variavel[k] <= '9')
											{
											}
											else
											{
												erro(8, numeroLinha);
											}
										}
									}
									else
									{
										erro(7, numeroLinha);
									}

									if (palavra && variavel != NULL)
									{
										if(verificaNome(listaSimbolo, variavel, palavra) == 0)
										{
											insereTabelaSimbolo(listaSimbolo, palavra, variavel, escopo);
										}
										else
										{
											erro(12, numeroLinha);
										}
									}
									indexVariavel = 0;
									variavelInserida = 1;
								}
								else if (asciiLetter == igual)
								{
									indexValor = 0;
									memset(valor, '\0', sizeof(valor));
									i++;
									while ((int)linha[i] != 0)
									{
										asciiLetter = (int)linha[i];
										if ((asciiLetter != virgula) &&
											(asciiLetter != espaco) &&
											(asciiLetter != pontoEvirgula))
										{
											valor[indexValor] = linha[i];
											indexValor++;
										}
										else if (valor[0] != 0)
										{
											for (k = 0; (int)valor[k] != 0; k++)
											{
												if (valor[k] >= '0' && valor[k] <= '9')
												{
												}
												else
												{
													erro(13, numeroLinha);
												}
											}
											if(verificaNome(listaSimbolo, variavel, palavra) == 1)
											{
												alterarValor(listaSimbolo, variavel, valor);
											}
											else
											{
												erro(12, numeroLinha);
											}

											break;
										}
										i++;
									}
								}
								i++;
							}
						}
					}

					variavelInserida = 0;
					memset(variavel, '\0', sizeof(variavel));
				}
				if (palavra[0] == 'o' || palavra[0] == 'O')
				{
					if (strcmp(palavra, palavraReservada[3]) == 0) /*out*/
					{
					}
					else
					{
						erro(1, numeroLinha);
					}
				}
				if (palavra[0] == 's' || palavra[0] == 'S')
				{
					if (strcmp(palavra, palavraReservada[4]) == 0) /*switch*/
					{
					}
					else
					{
						erro(1, numeroLinha);
					}
				}
				if (palavra[0] == 'c' || palavra[0] == 'C')
				{
					if (palavra[1] == 'a' || palavra[1] == 'A')
					{
						if (strcmp(palavra, palavraReservada[5]) == 0) /*case*/
						{
						}
						else
						{
							erro(1, numeroLinha);
						}
					}
					else
					{
						if (strcmp(palavra, palavraReservada[10]) == 0) /*char*/
						{
							indexVariavel = 0;
							memset(variavel, '\0', sizeof(variavel));
							while ((int)linha[i] != 0)
							{
								asciiLetter = (int)linha[i];
								if ((asciiLetter != espaco) &&
									(asciiLetter != pontoEvirgula) &&
									(asciiLetter != abreParentese) &&
									(asciiLetter != fechaParentese) &&
									(asciiLetter != igual))
								{
									variavel[indexVariavel] = linha[i];
									indexVariavel++;
								}
								else if (variavel[0] != 0 && variavelInserida == 0)
								{
									if (variavel[0] == '$')
									{
										if (variavel[1] >= 'a' && variavel[1] <= 'z')
										{
										}
										else
										{
											erro(8, numeroLinha);
										}
									}
									else
									{
										erro(7, numeroLinha);
									}
									if (palavra && variavel != NULL)
									{
										insereTabelaSimbolo(listaSimbolo, palavra, variavel, escopo);
									}
									indexVariavel = 0;
									variavelInserida = 1;
								}
								else if (asciiLetter == igual)
								{
									indexValor = 0;
									memset(valor, '\0', sizeof(valor));
									i++;
									while ((int)linha[i] != 0)
									{
										asciiLetter = (int)linha[i];
										if ((asciiLetter != virgula) &&
											(asciiLetter != pontoEvirgula))
										{
											valor[indexValor] = linha[i];
											indexValor++;
										}
										else if (valor[0] != 0)
										{
											alterarValor(listaSimbolo, variavel, valor);
											verificaNome(listaSimbolo, variavel, palavra);
											break;
										}
										i++;
									}
								}
								i++;
							}
						}
						else
						{
							erro(10, numeroLinha);
						}
					}
					variavelInserida = 0;
					memset(variavel, '\0', sizeof(variavel));
				}
				if (palavra[0] == 'b' || palavra[0] == 'B')
				{
					if (strcmp(palavra, palavraReservada[6]) == 0) /*break*/
					{
					}
					else
					{
						erro(1, numeroLinha);
					}
				}
				if (palavra[0] == 'd' || palavra[0] == 'D')
				{
					if (strcmp(palavra, palavraReservada[7]) == 0) /*default*/
					{
					}
					else
					{
						erro(1, numeroLinha);
					}
				}

				indexFunction = 0, indexVariavel = 0;
				index = 0;
				memset(palavra, '\0', sizeof(palavra));
			}
			i++;
		}
		numeroLinha++;
		tmp = tmp->prox;
	}

	if (validaMain == 0)
	{
		erro(2, 0);
	}
	if (validaMain > 1)
	{
		erro(11, 0);
	}

	nodeTabelaSimbolo *temp = listaSimbolo->prox;

	memoriaDisponivel(memoriaTotal);
	printf("Tamanho da Memoria: %i\n", memoria);
	printf("Memoria Disponivel: %i\n", memoriaDisp);
	printf("Memoria utilizada: %i\n\n", memoriaTotal);
	printf("|-------------------------------|\n|");
	printf("\tTABELA DE SIMBOLOS\t");
	printf("|\n|");
	printf("-------------------------------|");
	printf("\n");
	while (temp != NULL)
	{
		printf("\tNome: %s\n", temp->name);
		printf("\tTipo: %s\n", temp->type);
		printf("\tEscopo: %s\n", temp->scope);
		printf("\tValor: %s\n", temp->value);
		printf("\n");
		printf("---------------------------------");
		printf("\n");
		temp = temp->prox;
	}
	system("pause");
}

void alterarValor(nodeTabelaSimbolo *simbolo, char *variavel, char *valor)
{
	nodeTabelaSimbolo *temp = simbolo->prox;

	while (temp != NULL)
	{
		if (strcmp(variavel, temp->name) == 0)
		{
			memset(temp->value, '\0', sizeof(temp->value));
			strcpy(temp->value, valor);
			break;
		}
		temp = temp->prox;
	}
}

int verificaNome(nodeTabelaSimbolo *simbolo, char *variavel, char *palavra)
{
	nodeTabelaSimbolo *temp = simbolo->prox;
	int valor = 0;
	while (temp != NULL)
	{
		if (strcmp(variavel, temp->name) == 0)
		{
			valor = 1;
			break;
		}

		temp = temp->prox;
	}

	return valor;
}
