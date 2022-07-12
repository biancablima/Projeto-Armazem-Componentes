#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "componentes.h"

/* VERIFICACOES IMPLEMENTADAS */
int verifica_componente_novo(componente **c, const char *ID,  char *nome, const char *categoria, int quantidade, float preco)
{
    int er = 0;

    *c = componente_novo(ID, nome, quantidade,preco,categoria);
    if (!(*c))
    {
        printf("...verifica_componente_novo: componente novo e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_componente_novo: componente novo nao e' NULL (ok)\n");

    if (strcmp((*c)->ID, ID) != 0)
    {
        printf("...verifica_componente_novo: ID do novo componente (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*c)->ID, ID);
        er++;
    }
    else
        printf("...verifica_componente_novo: ID coincide com o esperado (= %s) (ok)\n", ID);

    if (strcmp((*c)->nome, nome) != 0)
    {
        printf("...verifica_componente_novo: Nome do novo componente (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*c)->nome, nome);
        er++;
    }
    else
        printf("...verifica_componente_novo: Nome do novo componente coincide com o esperado (= %s) (ok)\n", nome);

     if (strcmp((*c)->categoria, categoria) != 0)
    {
        printf("...verifica_componente_novo: Categoria do novo componente (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*c)->categoria, categoria);
        er++;
    }
    else
        printf("...verifica_componente_novo: Categoria do novo componente coincide com o esperado (= %s) (ok)\n", categoria);    

    if ((*c)->quantidade != quantidade)
    {
        printf("...verifica_componente_novo: Quantidade do novo componente (= %d) e' diferente do esperado (= %d) (ERRO)\n", (*c)->quantidade, quantidade);
        er++;
    }
    else
        printf("...verifica_componente_novo: Quantidade do novo componente coincide com o esperado (= %d) (ok)\n", quantidade);

    if ((*c)->preco != preco)
    {
        printf("...verifica_componente_novo: Preco do novo componente (= %.2f) e' diferente do esperado (= %.2f) (ERRO)\n", (*c)->preco, preco);
        er++;
    }
    else
        printf("...verifica_componente_novo: Preco do novo componente coincide com o esperado (= %.2f) (ok)\n", preco);

    return er;
}


int verifica_armazem_novo(armazem **a)
{
    int er = 0;

    *a = armazem_novo();
    if (!(*a))
    {
        printf("...verifica_armazem_novo: armazem novo e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_armazem_novo: armazem novo nao e' NULL (ok)\n");

    if ((*a)->tamanho != 0)
    {
        printf("...verifica_armazem_novo: Tamanho do armazem novo (= %ld) 'e diferente do esperado (= 0) (ERRO)\n", (*a)->tamanho);
        er++;
    }
    else
        printf("...verifica_armazem_novo: Tamanho do armazem novo coincide com o esperado (= 0) (ok)\n");

    return er;
}

int verifica_componente_insere(armazem **a)
{
    int er = 0, erro;
    float preco1=3.14;
  
    componente *c1 = componente_novo("con007290", "800UF/250V GIGA 85 50X100MM MALLORY", 5, 1.34, "condensador eletrolitico");
    componente *c2 = componente_novo("con007350", "1000UF/400V GIGA 105 65X70MM NICHICON", 10, 3.12,"condensador eletrolitico" );
    componente *c3 = componente_novo("tra012720", "MJ900 MOTOROLA", 0, 1.20,"transistor");
    componente *c4 = componente_novo("con007350", "1000UF/400V GIGA 105 65X70MM NICHICON", 20, preco1,"condensador eletrolitico" );

    erro = componente_insere(*a, c1);

    if (erro == -1)
    {
        printf("...verifica_componente_insere: nao conseguiu inserir (ERRO)\n");
        componente_apaga(c1);
        return 1;
    }
    else if (erro == 1)
        componente_apaga(c1);

    erro = componente_insere(*a, c2);
    if (erro != 0)
        componente_apaga(c2);

    erro = componente_insere(*a, c3);
    if (erro != 0)
        componente_apaga(c3);

    erro = componente_insere(*a, c4);
    
        componente_apaga(c4);

    if (strcmp((*a)->componentes[0]->ID, "con007290") != 0 || strcmp((*a)->componentes[2]->ID, "tra012720") != 0)
    {
        printf("...verifica_componente_insere: nao inseriu correctamente o 1º e 3º componentes, nao estao na posicao correta (ERRO)\n");
        er++;
        return er;
    }
    else
        printf("...verifica_componente_insere: inseriu a 1º e 3º componentes nas posicoes corretas (ok)\n");

    if ((*a)->componentes[1]->quantidade != 30)
    {
        printf("...verifica_componente_insere: quantidade do 2º componente (= %d) 'e diferente do esperado (= 30) (ERRO)\n", (*a)->componentes[1]->quantidade);
        er++;
    }
    else
        printf("...verifica_componente_insere: quantidade do 2º componente coincide com o esperado (= 30) (ok)\n");

    if ((*a)->componentes[1]->preco != preco1)
    {
        printf("...verifica_componente_insere: preco do 2º componente (= %.2f) 'e diferente do esperado (= 3.14) (ERRO)\n", (*a)->componentes[1]->preco);
        er++;
    }
    else
        printf("...verifica_componente_insere: preco do 2º componente coincide com o esperado (= 3.14) (ok)\n");

    return er;
}
int verifica_armazem_importa(armazem **a, const char *ficheiro)
{
    int er = 0;
    printf("Importando armazem...\n");

    *a = armazem_importa(ficheiro);

    if (*a == NULL)
    {
        printf("...verifica_armazem_importa: falhou importacao do armazem (ERRO)\n");
        return 1;
    }
    else
    {
        int tam =(*a)->tamanho;
        if (tam != 565)
        {
            printf("...verifica_armazem_importa: tamanho do armazem (= %d) e' diferente do esperado (= 565) (ERRO)\n", tam);
            er++;
        }
        else
            printf("...verifica_armazem_importa: tamanho do armazem coincide com o esperado (= 565) (ok)\n");
    }
    if (strcmp((*a)->componentes[0]->ID, "cir000030") != 0 || strcmp((*a)->componentes[(*a)->tamanho - 1]->ID, "Cap016950") != 0)
    {
        printf("...verifica_armazem_importa: IDs da 1ª (= %s) e 'ultima (= %s) posicoes do armazem diferem do esperado (cir000030 e Cap016950) (ERRO)\n", (*a)->componentes[0]->ID, (*a)->componentes[(*a)->tamanho - 1]->ID);
        er++;
    }
    else
        printf("...verifica_armazem_importa: IDs da 1ª e 'ultima posicoes do armazem coincidem com o esperado (cir000030 e Cap016950) (ok)\n");

    return er;
}

int verifica_componente_remove(armazem *a)
{
    int er = 0;

    componente *c;
    c = componente_remove(a, "inexistente");
    if (c)
    {
        printf("...verifica_componente_remove (teste de componente inexistente): removeu um componente inexistente (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_componente_remove (teste de componente inexistente): nao removeu nenhum componente (ok)\n");
    componente_apaga(c);

    c = componente_remove(a, "800UF/250V GIGA 85 50X100MM MALLORY");
    if (!c)
    {
        printf("...verifica_componente_remove (teste de componente valida): nao removeu (ERRO)\n");
        er++;
    }
    else if (strcmp(c->ID, "con007290") != 0)
    {
        printf("...verifica_componente_remove (teste de componente valida): removeu um componente errado (%s) (ERRO)\n",c->ID);
        er++;
    }
    else
    {
        printf("...verifica_componente_remove (teste de componente valida): removeu com sucesso (ok)\n");
    }
    componente_apaga(c);
    return er;
}

int verifica_componente_apaga(componente **c)
{
    int erro;

    erro = componente_apaga(*c);
    if (erro == -1)
    {
        printf("...verifica_componente_apaga: deu erro ao apagar o componente (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_componente_apaga: apagou com sucesso (ok)\n");
    return 0;
}

int verifica_armazem_pesquisa_categoria(armazem *a)
{
    int er = 0;
    int *idxs, tam;
    idxs = armazem_pesquisa_categoria(a, "Rosae", &tam);

    if (idxs)
    {
        printf("...verifica_armazem_pesquisa_categoria (teste de uma categoria que nao existe): vetor nao 'e NULL (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_armazem_pesquisa_categoria (teste de uma categoria que nao existe): retornou NULL (ok)\n");

    idxs = armazem_pesquisa_categoria(a, "resistencia smd", &tam);
    if (idxs == NULL)
    {
        printf("...verifica_armazem_pesquisa_categoria (teste de uma categoria que existe): categoria nao foi encontrada (ERRO)\n");
        er++;
    }
    else if (tam != 18)
    {
        printf("...verifica_armazem_pesquisa_categoria (teste de uma categoria que existe): numero de indices encontrados (= %d) nao coincide com o esperado (= 18) (ERRO)\n", tam);
        er++;
    }
    else
        printf("...verifica_armazem_pesquisa_categoria (teste de uma categoria que existe): numero de indices encontrados coincide com o esperado (= 18) (ok)\n");

    if (idxs != NULL)
    {
        free(idxs);
    }
    return er;
}


int verifica_armazem_pesquisa_nome(armazem *a)
{
    int er = 0;
    int *idxs, tam;
    idxs = armazem_pesquisa_nome(a, "Rosae", &tam);

    if (idxs)
    {
        printf("...verifica_armazem_pesquisa_nome (teste de um nome que nao existe): vetor nao 'e NULL (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_armazem_pesquisa_nome (teste de um nome que nao existe): retornou NULL (ok)\n");

    idxs = armazem_pesquisa_nome(a, "AXIAL", &tam);
    if (idxs == NULL)
    {
        printf("...verifica_armazem_pesquisa_nome (teste de um nome que existe): nome nao foi encontrado (ERRO)\n");
        er++;
    }
    else if (tam != 26)
    {
        printf("...verifica_armazem_pesquisa_nome (teste de um nome que existe): numero de indices encontrados (= %d) nao coincide com o esperado (= 26) (ERRO)\n", tam);
        er++;
    }
    else
        printf("...verifica_armazem_pesquisa_nome (teste de um nome que existe): numero de indices encontrados coincide com o esperado (= 26) (ok)\n");

    if (idxs != NULL)
    {
        free(idxs);
    }
    return er;
}

int verifica_vetor_ordena(armazem **a)
{
    int erro;
    int vet[]={5,10,15,20};
    int tam=4;
    erro = vetor_ordena(*a, vet,tam);
    if (erro == -1)
    {
        printf("...verifica_vetor_ordena: deu erro ao reordenar o vetor (ERRO)\n");
        return 1;
    }
    if (strcmp((*a)->componentes[vet[0]]->ID, "cir000480") != 0 || strcmp((*a)->componentes[vet[tam-1]]->ID, "cir000330") != 0)
    {
        printf("...verifica_vetor_ordena: 1ª (= %s) e 'ultimo (= %s) componentes do vetor sao diferentes do esperado (= cir000480 e cir000330) (ERRO)\n", (*a)->componentes[vet[0]]->ID,(*a)->componentes[vet[tam-1]]->ID);
        return 1;
    }
    else
    {
        printf("...verifica_vetor_ordena: 1ª e 'ultimo componentes do vetor coincidem com o esperado (= cir000480 e cir000330) (ok)\n");
    }
    return 0;
}


int verifica_fatura_nova(fatura **f)
{
    int er = 0;

    *f = fatura_nova();
    if (!(*f))
    {
        printf("...verifica_fatura_nova: fatura nova e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_fatura_nova: fatura novo nao e' NULL (ok)\n");

    if ((*f)->n_parcelas != 0)
    {
        printf("...verifica_fatura_nova: Numero de parcelas da fatura nova (= %d) 'e diferente do esperado (= 0) (ERRO)\n", (*f)->n_parcelas);
        er++;
    }
    else
        printf("...verifica_fatura_nova:  Numero de parcelas da fatura nova coincide com o esperado (= 0) (ok)\n");
float pre=0.0;
    if ((*f)->preco_total != pre)
    {
        printf("...verifica_fatura_nova: Preco total da fatura nova (= %f) 'e diferente do esperado (= 0.0) (ERRO)\n", (*f)->preco_total);
        er++;
    }
    else
        printf("...verifica_fatura_nova: Preco total  da fatura nova coincide com o esperado (= 0.0) (ok)\n");

    return er;
}

int verifica_parcela_nova(parcela **f, const char *ID, int quantidade, float preco)
{
    int er = 0;

    *f = parcela_nova(ID, quantidade,preco);
    if (!(*f))
    {
        printf("...verifica_parcela_nova: parcela nova e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_parcela_nova: parcela nova nao e' NULL (ok)\n");

    if (strcmp((*f)->ID, ID) != 0)
    {
        printf("...verifica_parcela_nova: ID na parcela nova (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*f)->ID, ID);
        er++;
    }
    else
        printf("...verifica_parcela_nova: ID coincide com o esperado (= %s) (ok)\n", ID);

    if ((*f)->quantidade != quantidade)
    {
        printf("...verifica_parcela_nova: Quantidade na parcela nova (= %d) e' diferente do esperado (= %d) (ERRO)\n", (*f)->quantidade, quantidade);
        er++;
    }
    else
        printf("...verifica_parcela_nova: Quantidade na parcela nova coincide com o esperado (= %d) (ok)\n", quantidade);

    if ((*f)->preco != preco)
    {
        printf("...verifica_componente_novo: Preco na parcela nova (= %.2f) e' diferente do esperado (= %.2f) (ERRO)\n", (*f)->preco, preco);
        er++;
    }
    else
        printf("...verifica_componente_novo: Preco na parcela nova coincide com o esperado (= %.2f) (ok)\n", preco);

    parcela_apaga(*f);
    return er;
}

int verifica_insere_parcela_fatura(fatura **f)
{
    int er = 0, erro;
    float preco2=124.30;

  
    parcela *p1 = parcela_nova("con007290", 5, 1.34);
    parcela *p2 = parcela_nova("con007350", 10, 3.12);
    parcela *p3 = parcela_nova("tra012720", 20, 1.20);
    parcela *p4 = parcela_nova("con007350", 20, 3.12);

    erro = insere_parcela_fatura(*f, p1);

    if (erro == -1)
    {
        printf("...verifica_insere_parcela_fatura: nao conseguiu inserir (ERRO)\n");
        parcela_apaga(p1);
        return 1;
    }
    else if (erro == 1)
        parcela_apaga(p1);

    erro = insere_parcela_fatura(*f, p2);
    if (erro != 0)
        parcela_apaga(p2);

    erro = insere_parcela_fatura(*f, p3);
    if (erro != 0)
        parcela_apaga(p3);

    erro = insere_parcela_fatura(*f, p4);
   
        parcela_apaga(p4);
    if ((*f)->n_parcelas != 3)
    {
        printf("...verifica_insere_parcela_fatura: numero de parcelas (= %d)  'e diferente do esperado (= 3) (ERRO)\n", (*f)->n_parcelas);
        er++;
    }
    else
        printf("...verifica_insere_parcela_fatura: numero de parcelas coincide com o esperado (= 3) (ok)\n");


    if (strcmp((*f)->inicio->ID, "con007290") != 0 || strcmp((*f)->inicio->proximo->proximo->ID, "tra012720") != 0)
    {
        printf("...verifica_insere_parcela_fatura: nao inseriu correctamente a 1ª e 3ª parcelas, nao estao na posicao correta (ERRO)\n");
        er++;
        return er;
    }
    else
        printf("...verifica_insere_parcela_fatura: inseriu a 1ª e 3ª parcelas nas posicoes corretas (ok)\n");

    if ((*f)->inicio->proximo->quantidade != 30)
    {
        printf("...verifica_insere_parcela_fatura: quantidade da 2ª parcela (= %d) 'e diferente do esperado (= 30) (ERRO)\n", (*f)->inicio->proximo->quantidade);
        er++;
    }
    else
        printf("...verifica_insere_parcela_fatura: quantidade do 2º parcela coincide com o esperado (= 30) (ok)\n");

    if (fabs((*f)->preco_total - preco2) > 0.00001)
    {
        printf("...verifica_insere_parcela_fatura: preco total da fatura (= %.2f) 'e diferente do esperado (= %.2f) (ERRO)\n", (*f)->preco_total,preco2);
        er++;
    }
    else
        printf("...verifica_insere_parcela_fatura: preco total da fatura coincide com o esperado (= 124.30) (ok)\n");

    return er;
}



int verifica_cria_fatura(armazem **a, const char *ficheiro)
{
    int er = 0;
   

    fatura *f = cria_fatura(*a,ficheiro);

    if (f == NULL)
    {
        printf("...verifica_cria_fatura: falhou criacao da fatura (ERRO)\n");
        return 1;
    }
    else
    {
        int tam =f->n_parcelas;
        if (tam != 7)
        {
            printf("...verifica_cria_fatura: numero de parcelas da fatura (= %d) e' diferente do esperado (= 7) (ERRO)\n", tam);
            er++;
        }
        else {
            printf("...verifica_cria_fatura: numero de parcelas da fatura coincide com o esperado (= 7) (ok)\n");
    
             if (strcmp(f->inicio->ID, "dio009630") != 0 || strcmp(f->inicio->proximo->proximo->proximo->proximo->proximo->proximo->ID, "con009210") != 0)
            {
                printf("...verifica_cria_fatura: IDs da 1ª (= %s) e 'ultima (= %s) parcelas da fatura diferem do esperado (dio009630 e con009210) (ERRO)\n", f->inicio->ID, f->inicio->proximo->proximo->proximo->proximo->proximo->proximo->ID);
                er++;
            }
            else
                 printf("...verifica_cria_fatura: IDs da 1ª e 'ultima parcelas da fatura coincidem com o esperado (dio009630 e con009210) (ok)\n");
        }
    float prec=22270.89;
     if ((f->preco_total -prec) > 0.000001)
     
        {
            printf("...verifica_cria_fatura: preço total da fatura (= %.2f) e' diferente do esperado (= 22270.89) (ERRO)\n", f->preco_total);
            er++;
        }
        else
            printf("...verifica_cria_fatura: preço total da fatura coincide com o esperado (= 22270.89) (ok)\n");
    
     if ((*a)->componentes[299]->quantidade != 2195)
        {
            printf("...verifica_cria_fatura: quantidade do componente 'cri009000' no armazem (= %d) e' diferente do esperado (= 2295) (ERRO)\n", (*a)->componentes[299]->quantidade);
            er++;
        }
        else
            printf("...verifica_cria_fatura: quantidade do componente 'cri009000' no armazem coincide com o esperado (= 2295) (ok)\n");
    

    }
   
    fatura_apaga(f);
    return er;
}

int main()
{
    int errorCount = 0, error;

     char nome[] = "100UF/100V RD. 85 10X20MM SANSUNG";
    const char categoria[] = "condensador eletrolitico";
  
    int quantidade = 60;
    float preco=1.34;
    char ID[10] = "con000101";
    char ficheiro[] = "db_small.txt";
    componente *c;
    armazem *a, *a1;

    printf("INICIO DOS TESTES\n\n");

    error = verifica_componente_novo(&c, ID, nome, categoria, quantidade, preco);

    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_componente_novo\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_componente_novo passou\n\n");
    }

    error = verifica_armazem_novo(&a);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_armazem_nov0\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_armazem_novo passou\n\n");
    }

    error = verifica_componente_insere(&a);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_componente_insere\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_componente_insere passou\n\n");
    }

    error = verifica_armazem_importa(&a1, ficheiro);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_armazem_importa\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_armazem_importa passou\n\n");
    }

    error = verifica_componente_remove(a);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_componente_remove\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_componente_remove passou\n\n");
    }

    error = verifica_componente_apaga(&c);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_componente_apaga\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_componente_apaga passou\n\n");
    }

    error = verifica_armazem_pesquisa_categoria(a1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_armazem_pesquisa_categoria\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_armazem_pesquisa_categoria passou\n\n");
    }

        error = verifica_armazem_pesquisa_nome(a1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_armazem_pesquisa_nome\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_armazem_pesquisa_nome passou\n\n");
    }

    error = verifica_vetor_ordena(&a1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_vetor_ordena\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_vetor_ordena passou\n\n");
    }

    printf("\n****** Testes 'a fatura ******\n\n");
    fatura *f;
    parcela *p;
    
    error = verifica_fatura_nova(&f);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_fatura_nova\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_fatura_nova passou\n\n");
    }

     error = verifica_parcela_nova(&p, ID, quantidade, preco);

    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_parcela_nova\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_parcela_nova passou\n\n");
    }

    error = verifica_insere_parcela_fatura(&f);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_insere_parcela_fatura\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_insere_parcela_fatura passou\n\n");
    }
      error = verifica_cria_fatura(&a1,"lista_de_compras.txt");
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_cria_fatura\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_cria_fatura passou\n\n");
    }

    armazem_apaga(a);
    armazem_apaga(a1);
    fatura_apaga(f);

    if (errorCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errorCount);

    return 0;
}
