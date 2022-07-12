/*****************************************************************/
/*       Biblioteca componentes | ESDA | LEEC | 2021/22          */
/*****************************************************************/

#include "componentes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int componente_compara_id(componente *c1, componente *c2){
    return strcmp(c1->ID,c2->ID);    
}
int componente_compara_preco(componente *c1, componente *c2){
    if(c1->preco > c2->preco) return -1;
    else if(c1->preco < c2->preco) return 1;
    else{
        return componente_compara_id(c1,c2);
    }
}

componente *componente_novo(const char *ID, char *nome, int quantidade, float preco, const char *categoria){

    // aloca memória para nova estrutura componente
    if (ID == NULL || nome == NULL || categoria == NULL )
    {
        return NULL;
    }
    componente *c = ( componente* ) malloc(sizeof(componente));
    if ( c == NULL )
    {
        return NULL;
    }

    // copia ID
    strcpy(c->ID, ID);

    // copia nome
	c->nome = (char*)malloc((strlen(nome) + 1) * sizeof(char));
    if(c == NULL)
    {
        return NULL;
    }
    strcpy(c->nome, nome);

    // copia quantidade
    c->quantidade = quantidade;

    // copia preco
    c->preco = preco;

    // copia categoria
    strcpy(c->categoria, categoria);
  
    return c;
}

armazem *armazem_novo(){
    armazem* a=(armazem *)malloc(sizeof(armazem));
    if(a==NULL) {return NULL;}
    a->tamanho=0;
    a->componentes=NULL;
    return a;  
}

int componente_insere(armazem *a,componente *c){     
    if( a == NULL || c == NULL)
    {
        return -1;
    }

    // caso específico de armazém vazio
    if(a->tamanho == 0){
        a->componentes = (componente **) malloc(sizeof(componente *));
        a->componentes[0] = c;
        a->tamanho++;
        return 0;
    }

    for(int i = 0; i< a->tamanho; i++) // procura por componente que já existe
    {      
        if(strcmp(a->componentes[i]->ID , c->ID) == 0){ // se a componente existir: atualizar valores
            a->componentes[i]->quantidade = c->quantidade + a->componentes[i]->quantidade;
            a->componentes[i]->preco = c->preco;
            return 1;
        }
    }

    // caso a componente não exista
    a->componentes = (componente**)realloc(a->componentes, (a->tamanho + 1) * sizeof(componente *));
    if(a->componentes == NULL){
        return -1;
    }
    a->componentes[a->tamanho] = c;
    a->tamanho++;
    return 0;
}

armazem *armazem_importa(const char *nome_ficheiro){
	
    if(nome_ficheiro==NULL) return NULL;
    FILE *fi;
    fi = fopen(nome_ficheiro, "r");
    if (fi == NULL) {
        printf("Erro a abrir %s.\n", nome_ficheiro);
        return NULL;
    }

    //iniciar variaveis para componente
    char linha[MAX_CHAR], categoria[MAX_CHAR], ID[10];
    char nome[MAX_CHAR];
    char *ptr;
    int quantidade=0;
    float preco=0;
    armazem *a = armazem_novo();
    componente *c;
    while(fgets(linha,MAX_CHAR,fi) != NULL){
        if(linha[strlen(linha)-1] == '\n') linha[strlen(linha)-1] = '\0'; 
        //get ID
        ptr=strtok(linha,",");
        if(ptr!=NULL){
            strcpy(ID,ptr);
        }
        else return NULL;
        //get nome
        ptr=strtok(NULL,",");
        if(ptr!=NULL){
            strcpy(nome,ptr);
        }
        else return NULL;

        //categoria
        ptr=strtok(NULL,",");
        if(ptr!=NULL){
            strcpy(categoria,ptr);
        }
        else return NULL;

        //get quantidade and cast it to INT
        ptr=strtok(NULL,",");
        if(ptr!=NULL){
            quantidade=atoi(ptr);
        }
        else return NULL;

        //get preco and cast it to FLOAT
        ptr=strtok(NULL,",");
        if(ptr!=NULL){
            preco=atof(ptr);
        }
        else return NULL;

        //chamar componente novo com os parametros que fomos buscar e inserir componente
        c = componente_novo(ID,nome,quantidade,preco,categoria);
        if(componente_insere(a, c) == 1)
            componente_apaga(c);
    
    }
    fclose(fi);

    //retorna armazem(a));
	return a;
    
}

componente *componente_remove(armazem *a,  char *nome){
    if( a == NULL || nome == NULL)
    {
        return NULL;
    }
    componente *c = NULL;
	int i, componente_existe = 0;
    for(i=0; i<a->tamanho; i++)
	{	
        if (strcmp(a->componentes[i]->nome, nome) == 0)
		{
			componente_existe++;
			break;
		}

	}
	if(componente_existe != 0)
	{
		c = a->componentes[i];
		if (i != (a->tamanho - 1))
			memmove(&a->componentes[i], &a->componentes[i+1], sizeof(componente *) * (a->tamanho - 1 - i));

		a->componentes = (componente **) realloc(a->componentes, (a->tamanho - 1) * sizeof(componente *));
		a->tamanho--;
        return c;
	} else return NULL;  
}

int componente_apaga(componente *c){    
    //verificar erros
    if(c == NULL) return -1;    
    //liberta a memoria
    free(c->nome);
    free(c);
	return 0;
}

int armazem_apaga(armazem *a){
    int i;
	if(a == NULL)
	{
		return -1;
	}
	for(i=0; i<a->tamanho; i++)
	{
		componente_apaga(a->componentes[i]);
	}
	free(a->componentes);	
	free(a);
	return 0;	
}

int *armazem_pesquisa_categoria(armazem *a, const char *categoria, int *tam){
	
    //testa parametros
    if(a==NULL || categoria==NULL) return NULL;
    int aux[a->tamanho];
    int *vetor;
    int pos=0,hasFound=0;
    for(int i = 0;i<a->tamanho;i++){
        //se encontrou na categoria,  hasFound=1
        if(strcmp(a->componentes[i]->categoria,categoria)==0){
            hasFound=1;
        }
        //agora, se hasFound=1
        if(hasFound){
            aux[pos]=i;
            pos++;
        }
        hasFound=0; //repor hasFound para a próxima iteração
    }
    
	//se nao tiver encontrado nenhum, return NULL
    if(pos==0) return NULL;

    *tam=pos;
    vetor = (int*)malloc((pos)*sizeof(int));
    //copia vetor
    for(int i = 0; i<pos;i++){
        vetor[i]=aux[i];
    }
    return vetor;
   
}

int *armazem_pesquisa_nome(armazem *a, char *nome, int *tam){

    int i;
	int *componentes_encontrados = NULL;
	if(a == NULL || nome == NULL)
	{
		return NULL;
	}
	*tam = 0;
	componentes_encontrados = ( int* ) malloc(sizeof(int *));
	if(componentes_encontrados == NULL)
	{
		return NULL;
	}    
	for(i=0; i<a->tamanho; i++)
	{
		// testa se existe "nome" em alguma parte do nome de um componente
		if(strstr(a->componentes[i]->nome, nome) != NULL)
		{ 
			componentes_encontrados = (int *) realloc(componentes_encontrados, (*tam + 1) * sizeof(int *));
			componentes_encontrados[*tam] = i;
			(*tam)++;
		}
	
	}
	if(*tam == 0) // se não achar o nome: libera o espaço alocado
	{
		free(componentes_encontrados);
		return NULL;
	}
	else // se achar: devolve o vetor com as posições
	{
		return componentes_encontrados;
	} 
}

int  vetor_ordena(armazem *a, int *vetor_pos_c, int tam){
    //verifica parametros
    if(a == NULL || tam <= 0 || vetor_pos_c == NULL) return -1;
    int aux;
    //se tamanho da colecao for menor que dois, não é preciso reordenar
    if(tam<2){
        return 0;
    }
    else{
        for (int h=0; h<tam ; h++){
            for(int k=h+1; k<tam; k++){
                //se Preco\ID for "menor"
                if ((componente_compara_preco(a->componentes[vetor_pos_c[h]], a->componentes[vetor_pos_c[k]])) < 0){
                    //troca um com o outro
                    /* >> Queremos ordenar o vetor de posições vetor_pos_c. Assim, o que vamos trocar são os elementos de vetor_pos_c e não do armazém. */
                    aux = vetor_pos_c[h];
                    vetor_pos_c[h] = vetor_pos_c[k];
                    vetor_pos_c[k] = aux;
                }
            }
        }
    }
    return 0;
}


fatura *fatura_nova(){
	fatura *nova = (fatura *) malloc(sizeof(fatura));
	if(nova == NULL)
	{
		return NULL;
	}
	nova->inicio = NULL;
	nova->n_parcelas = 0;
	nova->preco_total = 0;

    return nova;
}

parcela *parcela_nova (const char *ID, int quantidade,   float preco ){  
    if(ID == NULL || quantidade<0 || preco<0) return NULL;
    parcela* p=(parcela *)malloc(sizeof(parcela));
    if (p==NULL){
        return NULL;
    }
    p->quantidade=quantidade;
    p->preco=preco;
    strcpy(p->ID,ID);
    p->proximo=NULL;
    return p;
}

int insere_parcela_fatura(fatura *f, parcela  *p){
	if(f == NULL || p == NULL)
	{
		return -1;
	}
	// caso fatura vazia:
    if(f->n_parcelas == 0)
	{
		f->inicio = p;
		f->n_parcelas = 1;
		f->preco_total = (p->preco * p->quantidade);
		return 0;
	}
	// caso de fatura não vazia:
    parcela *p_itera = f->inicio;
	for(int i=0; i < f->n_parcelas; i++)
	{        
        if(strcmp(p_itera->ID, p->ID) == 0)  // parcela já existente
		{            
            p_itera->quantidade = p_itera->quantidade + p->quantidade;
            f->preco_total = f->preco_total + (p->quantidade * p->preco);
            return 1;
		}
        p_itera = p_itera->proximo;
	}
    p_itera = f->inicio;

    // parcela não existe:
    for (int i = 0; i < f->n_parcelas; i++)
    {
        if(p_itera->proximo == NULL)
        {            
            p_itera->proximo = p;
            f->n_parcelas++;
            f->preco_total = f->preco_total + (p->quantidade * p->preco);       
            return 0;
        }
        p_itera = p_itera->proximo;
    }
    return -1;   
}

int parcela_apaga(parcela *p){
    if(p == NULL)
    {
        return -1;
    }
    free(p);
    return 0;
}

fatura *cria_fatura(armazem *a, const char *f){
      if(f==NULL) return NULL;
    FILE *fi;
    fi = fopen(f, "r");
    if (fi == NULL) {
        printf("Erro a abrir %s.\n", f);
        return NULL;
    }

    //iniciar variaveis para componente
    char linha[MAX_CHAR], categoria[MAX_CHAR], ID[10];
    char tipo_de_parcela[MAX_CHAR];
    char nome[MAX_CHAR];
    char *ptr;
    int quantidade=0, y, dq=0;
    //float preco=0;

    fatura *fat = fatura_nova();
    while(fgets(linha,MAX_CHAR,fi) != NULL){
        if(linha[strlen(linha)-1] == '\n') linha[strlen(linha)-1] = '\0';

        //get tipo de parcela
        ptr=strtok(linha,",");
        if(ptr!=NULL){
            strcpy(tipo_de_parcela,ptr);
        }
        else return NULL;

        //qual e o tipo de parcela
        //se for do tipo C
        if (strcmp(tipo_de_parcela, "C")==0){
            //get descricao do tipo categoria
            ptr=strtok(NULL,",");
            if(ptr!=NULL){
                strcpy(categoria,ptr);
            }
            else return NULL;
        }
           //se for do tipo I  
        else if(strcmp(tipo_de_parcela, "I")==0){
   
            //get descricao do tipo ID
            ptr=strtok(NULL,",");
            if(ptr!=NULL){
                strcpy(ID,ptr);
            }
            else return NULL;
        }
        //se for do tipo N
        else if(strcmp(tipo_de_parcela, "N")==0){
            //get descricao do tipo nome
            ptr=strtok(NULL,",");
            if(ptr!=NULL){
                strcpy(nome,ptr);
            }
            else return NULL;
        }
        else return NULL;

        //get quantidade and cast it to INT
        ptr=strtok(NULL,",");
        if(ptr!=NULL){
            quantidade=atoi(ptr);
        } 
        else return NULL;

        /* --------------estao recolhidas as informacoes dos componentes pedidos--------------*/

        //Caso seja do tipo C:
        if (strcmp(tipo_de_parcela, "C")==0){
            int tam, c=0, i;
            int *cat=armazem_pesquisa_categoria(a,categoria, &tam);
            if(cat == NULL) return NULL;
            y = vetor_ordena(a, cat, tam);
            if(y == -1) return NULL;

            // procura por categoria com a quantidade pretendida
            for(i=0; i<tam; i++)
            {
                if(a->componentes[cat[i]]->quantidade >= quantidade){
                    c++;
                    break;
                }
            }
            if(c!=0)
            {
                insere_parcela_fatura(fat,parcela_nova(a->componentes[cat[i]]->ID, quantidade, a->componentes[cat[i]]->preco));
                //ATUALIZAR ARMAZEM
                a->componentes[cat[i]]->quantidade = a->componentes[cat[i]]->quantidade - quantidade;
            } else{            
                for(int j=0; j < tam; j++){
                    //testo se o mais barato tem quantidade suficiente
                    if(a->componentes[cat[j]]->quantidade >= quantidade){
                        insere_parcela_fatura(fat,parcela_nova(a->componentes[cat[j]]->ID, quantidade, a->componentes[cat[j]]->preco));
                        //ATUALIZAR ARMAZEM
                        a->componentes[cat[j]]->quantidade = a->componentes[cat[j]]->quantidade - quantidade;
                        break;
                    }
                    else if(a->componentes[cat[j]]->quantidade < quantidade){
                        //calcula quanto falta
                        dq = quantidade - a->componentes[cat[j]]->quantidade;
                        insere_parcela_fatura(fat,parcela_nova(a->componentes[cat[j]]->ID, a->componentes[cat[j]]->quantidade, a->componentes[cat[j]]->preco));
                        //ATUALIZAR ARMAZEM
                        a->componentes[cat[j]]->quantidade=0;
                    }
                    //atribui a quantidade, a quantidade que falta preencher
                    quantidade=dq;
                    //repoe dq
                    dq=0;
                } 
            } free(cat);
        }

        // Caso seja do tipo I:
        if(strcmp(tipo_de_parcela, "I") == 0)
        {   
            for(int i=0; i < a->tamanho; i++){
                if(strcmp(a->componentes[i]->ID, ID) == 0){
                    int dif = a->componentes[i]->quantidade - quantidade; // se dif >= 0, há a quantidade inteira em stock
                    if(dif >= 0)
                    {
                        insere_parcela_fatura(fat, parcela_nova(ID, quantidade, a->componentes[i]->preco));
                        a->componentes[i]->quantidade = dif;
                        break;
                    }
                    else{
                        insere_parcela_fatura(fat, parcela_nova(ID, a->componentes[i]->quantidade, a->componentes[i]->preco));
                        a->componentes[i]->quantidade = 0;
                        break;
                    }
                }
            }
        }

        // Caso seja do tipo N:
        if(strcmp(tipo_de_parcela, "N") == 0)
        {   
            int tam;
            int *vetor_nomes = armazem_pesquisa_nome(a, nome, &tam);

            if(vetor_nomes == NULL)
            {
                return NULL;
            }
            if(vetor_ordena(a, vetor_nomes, tam) == -1)
            {
                return NULL;
            }
            int c=0, fim=0;
            componente *aux;
            for(int i=0; i <= tam; i++){      
                if(a->componentes[vetor_nomes[i]]->quantidade >= quantidade)       // procura o que tem a quantidade necessária dentre os mais baratos
                {   
                    insere_parcela_fatura(fat, parcela_nova(a->componentes[vetor_nomes[i]]->ID, quantidade, a->componentes[vetor_nomes[i]]->preco));
                    a->componentes[vetor_nomes[i]]->quantidade = a->componentes[vetor_nomes[i]]->quantidade - quantidade;
                    fim=0;
                    break;

                }
                else if(a->componentes[vetor_nomes[i]]->quantidade > c){
                    c=a->componentes[vetor_nomes[i]]->quantidade;
                    aux = a->componentes[vetor_nomes[i]];
                    fim=vetor_nomes[i];
                }
            }
            if(fim!=0)
            {
                insere_parcela_fatura(fat, parcela_nova(aux->ID, aux->quantidade, aux->preco));
                a->componentes[fim]->quantidade = 0;
            } free(vetor_nomes);
            
        }

    } fclose(fi); 
    
    
    return fat;
}

int fatura_apaga(fatura *f){
 
   if(f==NULL) return -1;

   parcela * aux;

   for(int i=0; i<f->n_parcelas; i++)
   {    
       aux = f->inicio->proximo;
       free(f->inicio);
       f->inicio = aux;
   }
   free(f);
   return 0;

}
