/*****************************************************************/
/*       Biblioteca componentes | ESDA | LEEC | 2021/22          */
/*****************************************************************/


#ifndef COMPONENTES_H
#define MAX_CHAR 200

/*
* Estrutura para armazenar elementos do vetor dinamico
* Esta estrutura contem duas strings (ID e categoria), 
um inteiro (quantidade), um float (preco) e um apontador para char (nome)
*/


typedef struct
{
    /** Identificacao unica do componente **/
    char ID[10];

    /** Nome do componente **/
    char *nome;

    /** Quantidade que existe deste componente no armazém **/
    int quantidade; 

    /** Preco **/
    float preco;

    /** Categoria do componente **/
    char categoria[MAX_CHAR]; 

} componente;


/*
* Estrutura para representacao do armazem
* Esta estrutura contem um apontador do tipo componente (componentes) e um long int (tamanho)
*/
typedef struct
{
  /** Apontador para o array de componentes armazenados (apontadores do tipo componente) **/
  componente **componentes;

  /** Tamanho do vetor de componentes **/
  long tamanho;

} armazem;



/*
* Estrutura para registo de parcelas de uma fatura
* Esta estrutura contém o um char (ID), um inteiro (quantidade), 
um float e um apontador do tipo parcela (proximo) 
*/

typedef struct _parcela
{
    /**ID do componente **/
    char ID[10];
    
    /** Quantidade de componentes comprados**/
    int quantidade;

    /** Preco unitário do componente no momento da compra **/
	  float preco; 
    
    /** Apontador para a proxima parcela **/
	  struct  _parcela *proximo;

}  parcela;


/*
* Estrutura que representa uma fatura
* Esta estrutura contém um apontador do tipo parcela (inicio), 
* um inteiro (tamanho) e um float (preco)
*/


typedef struct{
    /* Apontador para a primeira parcela */
    parcela *inicio; 
    
    /* Numero de parcelas da fatura*/
    int n_parcelas;

    /* Preco total da fatura */
    float preco_total;
} fatura;


/*
*  cria um novo componente com os valores dos parametros
*  parametro: ID - string de 10 carateres contendo o identificador unico do componente
*  parametro: nome- vetor de carateres contendo o nome do componente
*  parametro: n_exemplares- inteiro contendo o numero de exemplares do componente em armazem
* parametro - preco- float contendo o preço do componente
*parametro -  categoria - string de 200 carateres contendo a categoria do componente
*  retorno: retorna o apontador para o componente criado ou NULL se ocorrer algum erro ou se algum dos parametros nao estiver dentro da gama de valores valida
*/
componente *componente_novo(const char *ID, char *nome, int quantidade, float preco, const char *categoria);

/*
*  cria um novo armazem vazio
*  retorno: apontador para o armazem ou NULL se ocorreu algum erro
*/
armazem *armazem_novo();

/*
*  insere um componente no armazem, na posicao última posicao ( ou seja primeira posicao disponivel)
*  parametro: a - apontador para o armazem
*  parametro: c - componente a inserir
*  retorno: 0 se o componente nao existia e foi inserido com sucesso, 1 se o componente ja existia e apenas foi atualizado e -1 se ocorrer um erro
*  observacoes: caso o componente ja exista (tenha o mesmo ID) deve adicionar o numero de componentes ao que já existe e atualizar o preco
*/
int componente_insere(armazem *a,componente *c);



/*
*  cria um armazem, le o conteudo do ficheiro de texto de nome nome_ficheiro e importa-o para o armazem criado
*  parametro: nome_ficheiro - nome do ficheiro de texto contendo o armazem a importar
*  retorno: apontador para o armazem criado. Em caso de erro retorna NULL. 
*  observacoes: Cada linha do ficheiro corresponde a um componente e tem o seguinte formato: ID,nome,categoria,quantidade,preco
*/
armazem *armazem_importa(const char *nome_ficheiro);

/*
*  remove do armazem o componente com nome dado por nome e corrige o armazem no componente retirado
*  parametro: a - apontador para o armazem
*  parametro: nome - nome do componente a remover
*  retorno: apontador para o componente removido do armazem ou NULL se ocorrer um erro (ou o componente nao existir no armazem).
*  observacoes: remove apenas o primeiro componente que encontrar com o nome dado( tem que ser o nome completo) 
*/
componente *componente_remove(armazem *a,  char *nome);

/*
*  elimina um componente, libertando toda a memoria por ele ocupada
*  parametro: c - apontador para o componente
*  retorno: 0 se remocao ocorrer com sucesso e -1 em caso de erro
*
*/
int componente_apaga(componente *c);

/*
*  elimina um armazem e todos os seus componentes, libertando toda a memoria por eles ocupadas
*  parametro: a - apontador para o armazem
*  retorno: 0 se bem sucedida e -1 em caso de insucesso
*/
int armazem_apaga(armazem *a);

/*
*  pesquisa todos os componentes que tenham uma determinada categoria (categoria exata)
*  parametro: a - apontador para o armazem
*  parametro: categoria - categoria a procurar
*  parametro: tam - apontador para o tamanho do vetor retornado/numero total de plantas encontradas
*  retorno: vetor de indices/posicoes dos componentes  encontrados. O tamanho deste vetor e retornado por referencia no parametro tam.
*  observacoes: 
*/
int *armazem_pesquisa_categoria(armazem *a, const char *categoria, int *tam);


/*
*  pesquisa todos os componentes que contenham a determinado nome(na sua totalidade ou parcelarmente)
*  parametro: a - apontador para o armazem
*  parametro: nome- nome a procurar
*  parametro: tam - apontador para o tamanho do vetor retornado/numero total de componentes encontradas
*  retorno: vetor de indices/posicoes dos componentes  encontrados. O tamanho deste vetor e retornado por referencia no parametro tam.
*/
int *armazem_pesquisa_nome(armazem *a, char *nome, int *tam);


/*
* ordena um vetor de posições do mais barato para o mais caro
* parametro a - apontador para o armazem 
* parametro vetor_pos_c - vetor com as posicoes dos componentes no armazem 
* parametro tam - apontador para o tamanho do vetor fornecido
* retorno: 0 se bem sucedida e -1 em caso de insucesso
* observacoes: em caso de preços iguais deve primeiro ficar o que tiver um ID mais baixo. 
*/
int  vetor_ordena(armazem *a, int *vetor_pos_c, int tam );

/*
*  cria uma nova fatura vazia
*  retorno: apontador para a fatura ou NULL se ocorreu algum erro
*/
fatura *fatura_nova();

/*
*  cria uma nova parcela com os valores dos parametros
*  parametro: ID - ID do componente 
*  parametro: quantidade - inteiro contendo a quantidade de cada componente em armazem
*  parametro - preco- float contendo o preço do componente
*  retorno: retorna o apontador para a nova  parcela criado ou NULL se ocorrer algum erro ou se algum dos parametros nao estiver dentro da gama de valores valida
*/
parcela *parcela_nova (const char *ID, int quantidade,   float preco );

/* insere uma parcela na fatura, no fim da lista
*  parametro: f - fatura 
*  parametro: p - parcela
*  retorno: Retorna zero se a parcela ainda não existia e foi inserido com sucesso, 1 se a parcela ja existia e apenas foi atualizado e -1 em caso de erro
*  observacoes: Caso a parcela já exista (tenha o mesmo ID) deve adicionar a quantidade ao já existente. 
* observacoes: Obs: Sempre que adicionar uma parcela à fatura deve atualizar o armazém, ou seja, deve descontar as quantidades vendidas no stock do armazém.
*/
int insere_parcela_fatura(fatura *f, parcela  *p);


/* apaga  uma parcela, libertando toda a memoria por ela ocupada
* parametro: p - parcela
* retorno: 0 se apagar com sucesso e -1 em caso de erro
*/
int parcela_apaga(parcela *p);


/*
* cria uma fatura a partir de uma lista de compras ( ficheiro txt ) e retorna um fatura do tipo fatura
*  parametro: a - apontador para o armazem 
*  parametro: f - ficheiro com a lista de compras de componentes 
*  retorno: fatura se bem sucedido , NULL se não conseguir criar a fatura
*  observacao: Cada linha do ficheiro corresponde a uma parcela da compra e tem o seguinte formato: tipo_de_parcela,descrição,quantidade
*  observacao: O tipo de parcela pode ser de 3 tipos:
*  ‘C’ – Em que a descrição é referente a uma categoria, dessa categoria escolhe-se o mais barato, que tenha a quantidade necessária; se não houver nenhum componente que tenha a quantidade necessária, deve-se ir ao mais barato usar toda a quantidade, depois sucessivamente ir aos seguintes mais barato, usar a quantidade necessária para fazer o pretendido. Se não se conseguir chegar a essa quantidade pretendida, só se fatura o que se consegue.
*  ‘I’- Em que a descrição é referente ao ID do componente . Insere-se a quantidade desejada, se não houve o suficiente usa-se o o stock disponível.
*  ‘N’ – Em que a descrição é referente ao nome completo ou parcial do componente. Escolhe-se o mais barato, que tenha a quantidade pretendida. Se não houve nenhum escolhe-se o que tiver a maior quantidade( usa-se essa quantidade), em caso de empate escolhe-se o mais barato.
*/


fatura *cria_fatura(armazem *a, const char *f);


/* apaga a fatura e as suas parcelas, libertando toda a memoria por elas ocupadas
*  parametro - f - fatura
*  retorno: 0 se bem sucessido retorno 1 se a fatura nao existe ou nao conseguiu apagar
*  obsv: deve tambem apagar as parcelas associada a fatura
*/
int fatura_apaga(fatura *f);



#define COMPONENTES_H
#endif

