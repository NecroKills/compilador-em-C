void erro(int codeErro, int numeroLinha)
{
    if(numeroLinha != 0)
    {
        printf("LINHA: %i\n", numeroLinha);
    }
    switch (codeErro) {
        case 0: 
            printf("0 - Declaracao do Main incorreto.\n");
            break;
        case 1: 
            printf("1 - Declaracao incorreta.\n");
            break;
        case 2:
            printf("2 - Modulo Principal Inexistente.\n");
            break;
        case 3:
            printf("3 - Nome da Function nao comecou com marcador '!'\n");
            break;
        case 4:
            printf("4 - Nome da Function contem simbolo invalido\n");
            break;
         case 5:
            printf("5 - Declaracao da Function incorreto.\n");
            break;
        case 6:
            printf("6 - Declaracao do Integer incorreto\n");
            break;
        case 7:
            printf("7 - Nome da Variavel nao comecou com marcador '$'\n");
            break;
        case 8:
            printf("8 - Nome da Variavel contem simbolo invalido\n");
            break;
        case 9:
            printf("9 - Declaracao do Char incorreto\n");
            break;
        case 10:
            printf("10 - Declaracao do Float incorreto\n");
            break;
        case 11:
            printf("11 - Declaracao de Main esta duplicado\n");
            break;
        case 12:
            printf("12 - Declaracao de variavel duplicada\n");
            break;
        case 13:
            printf("13 - valor da Variavel contem simbolo invalido\n");
            break;  
        case 14:
            printf("14 - limitador de tamanho contem simbolo invalido\n");
            break;
        case 15:
            printf("15 - \n");
            break;             
        default:
            printf("");
    }
    system("pause");
    exit(0);
}