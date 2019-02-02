void alerta(int codeAlerta, int numeroLinha)
{
    if(numeroLinha != 0)
    {
        printf("LINHA: %i\n", numeroLinha);
    }
    switch (codeAlerta) {
        case 0: 
            printf("0 - Alerta memoria utilizada no momento esta entre 90 e 99% do total disponivel.\n");
            break;        
        default:
            printf("");
    }
    system("pause");
}