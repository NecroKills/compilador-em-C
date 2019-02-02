int memoria = 10485760; /*tamanho total */
int memoriaTotal = 0; /* memoria utilizada*/
int memoriaDisp = 0; /* memoria sobrando*/
int alerta = 0; /*90% = 9437184  */
void somaMemoria(int memoriaAloca)
{
    memoriaTotal = memoriaTotal + memoriaAloca;
    memoriaDisp = memoria - memoriaTotal;
}

void memoriaDisponivel(memoriaTotal)
{
    if(memoriaTotal >= memoria)
    {
        printf("Memoria Insuficiente\n\n");
        system("pause");
        exit(0);
    }
    alerta = memoria * 0.9;
    if(memoriaTotal >= alerta){
        printf("|--------------------------------------------------------------------------| \n");
        printf("|Alerta memoria utilizada no momento esta entre 90 e 99 porcento disponivel|\n");
        printf("|--------------------------------------------------------------------------| \n\n");
    }

}
