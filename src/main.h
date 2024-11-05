#ifndef MYHEADER_H
#define MYHEADER_H

#define MAX_NOME 1000
#define MAX_CARR 50
#define MAX_SIST 50

#define MAX_BUFFER 1000

#define MERCADO_NOME "Weldesmart"

typedef struct {
    int id;
    char nome[MAX_NOME];
    float preco;
    float desconto;
    int n;

} Produto;

typedef struct {
    Produto produtos[MAX_CARR];
    int quantidade;

} Carrinho;

typedef struct {
    Produto produtos[MAX_SIST];
    int quantidade;

} Sistema;

void trocar(Produto *a, Produto *b);
void selectionSort(Produto *p, int size);

void menu();

void banner(char s[]);
void linhaDiv(int n, char c);

void infoProduto(Produto p, int incluirN);
int temNoCarrinho(Carrinho c, int novoId);
int temNoSistema(Sistema s, int novoId);

Produto pegarProdutoPorCodigo(Sistema s, int id);

void comprarProduto(Sistema s, Carrinho *c, int novoId);
void visualizarCarrinho(Carrinho c);
void removerDoCarrinho(Carrinho *c, int idRemover);

void listarProdutos(Sistema s);
void cadastrarProduto(Sistema *s, Produto p);

void finalizarCompras(Carrinho *c);
float obterTotal(Carrinho *c);

#endif