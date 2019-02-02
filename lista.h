typedef struct Node{
	char linha[500];
	int localizacao;
	struct Node *prox;
}node;

node *nova(char *linha, int localizacao){
	node *p = malloc(sizeof(node)); /*aloca espaço na memoria*/
	somaMemoria(sizeof(node));
	if(p==NULL){
		printf("ERRO: Memoria insuficiente");
		exit(1);
	}
	strcpy(p->linha, linha); /*copia linha para p->linha*/
	p->localizacao = localizacao;
	p->prox=NULL;
	return p;
}

void insere(node *LISTA, char *linha, int localizador){
	node *novo = (node *) malloc(sizeof(node));
	somaMemoria(sizeof(node));
	memset(novo->linha, '\0', sizeof(novo->linha));

	strcpy(novo->linha, linha);
	novo->localizacao = localizador;
	novo->prox = NULL;

	if(LISTA->prox == NULL){
		LISTA->prox = novo;
	}else{
		node *tmp = LISTA->prox;
		while(tmp->prox !=NULL) {
			tmp = tmp->prox;
		}
		tmp->prox = novo;
	}
}
