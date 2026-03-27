NolistaDupla *dllCria(void){
    return NULL;
};
NolistaDupla*dllInsere(NolistaDupla *head, char *v){
    NolistaDupla *no = malloc(sizeof(NolistaDupla));
    no->info = strdup(v);
    no->ant = head;
    no->prox = NULL; 
    return no;
};
void dllImprime(NolistaDupla *head, int count){
    if(head != NULL){
        head->prox = no;
        printf("%d. %s\n", count, head->info);
        dllImprime(head->prox, ++count);
    }
    
};
int dllVazia(NolistaDupla *head);
NolistaDupla *dllBusca(NolistaDupla *head, char *v);
int dllComprimento(NolistaDupla *head);
NolistaDupla *dllUltimo(NolistaDupla *head);
NolistaDupla *dllRetira(NolistaDupla *head, char *v);
void dllLibera(NolistaDupla *head);
NolistaDupla *dllInsereFim(NolistaDupla *heaed, char *v);
