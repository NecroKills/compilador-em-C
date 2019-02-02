typedef struct tabelaDeSimbolos{
	char name[100];
    char type[100];
    char scope[100];
	char value[100];
	struct tabelaDeSimbolos *prox;
}nodeTabelaSimbolo;

nodeTabelaSimbolo *novaTabelaSimbolo(char *name, char *type, char *scope){
	nodeTabelaSimbolo *p = malloc(sizeof(nodeTabelaSimbolo)); /*aloca espaço na memoria*/
	somaMemoria(sizeof(nodeTabelaSimbolo));
	if(p==NULL){
		printf("ERRO: Memoria insuficiente");
		exit(1);
	}
	strcpy(p->name, name);
	strcpy(p->type, type);
	strcpy(p->scope, scope);
	p->prox=NULL;
	return p;
}

void insereTabelaSimbolo(nodeTabelaSimbolo *LISTA, char *type, char *name, char *scope){
	nodeTabelaSimbolo *novo = (nodeTabelaSimbolo *) malloc(sizeof(nodeTabelaSimbolo));
	somaMemoria(sizeof(nodeTabelaSimbolo));
	memset(novo->name, '\0', sizeof(novo->name));
	memset(novo->type, '\0', sizeof(novo->type));
	memset(novo->scope, '\0', sizeof(novo->scope));

	strcpy(novo->name, name);
	strcpy(novo->type, type);
	strcpy(novo->scope, scope);
	novo->prox = NULL;

	if(LISTA->prox == NULL){
		LISTA->prox = novo;
	}else{
		nodeTabelaSimbolo *tmp = LISTA->prox;
		while(tmp->prox !=NULL) {
			tmp = tmp->prox;
		}
		tmp->prox = novo;
	}
}
