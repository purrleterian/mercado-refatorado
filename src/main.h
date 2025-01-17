#ifndef MYHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void trocarProdutos(Produto *a, Produto *b);
void ordenarSelecao(Produto *p, int size);

int menu(Sistema *sistemaMercado, Carrinho *carrinhoMercado);

void banner(const char s[]);
void linhaDiv(int n, char c);

void infoProduto(Produto p, int incluirN);
int temNoCarrinho(Carrinho c, int novoId);
int temNoSistema(Sistema s, int novoId);

void comprarProduto(Sistema s, Carrinho *c, int novoId);
void visualizarCarrinho(Carrinho c);
void removerDoCarrinho(Carrinho *c, int idRemover);

void listarProdutos(Sistema s);
void cadastrarProduto(Sistema *s, Produto p);

void finalizarCompras(Carrinho *c);
float obterTotal(Carrinho *c);

#endif