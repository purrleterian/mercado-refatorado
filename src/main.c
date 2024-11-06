#include "main.h"

int main() {
    carrinhoMercado.quantidade = 0;
    sistemaMercado.quantidade = 0;

    // Loop infinito gerenciado pela variavel 'rodando', assim posso parar o
    // loop alterando-a
    while (menu() != 0);
    return 0;
}

void trocar(Produto *a, Produto *b) {
    Produto temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarSelecao(Produto *p, int size) {
    for (int i = 0; i < size; i++) {
        int menor = i;
        for (int j = i; j < size; j++) {
            if (p[j].id < p[menor].id) {
                menor = j;
            }
        }
        trocar(&p[i], &p[menor]);
    }
}

void banner(const char s[]) {
    // funcao simples pra evitar repetir esse loop sempre que quiser formatar
    // texto com caracteres envolta
    size_t sTamanho = strlen(s);
    for (int i = 0; i < sTamanho + 4; i++) {
        printf("=");
    }

    printf("\n= %s =\n", s);
    for (int i = 0; i < sTamanho + 4; i++) {
        printf("=");
    }
    printf("\n");
}

void linhaDiv(int n, char c) {
    // funcao de utilidade pra desenhar uma linha horizontal divisoria
    for (int i = 0; i < n; i++) {
        printf("%c", c);
    }
    printf("\n");
}

void infoProduto(Produto p, int incluirN) {
    banner(p.nome);

    // apenas mostrar a quantia de um produto se ela for maior de que 1.
    // A variavel 'incluirN' serve pra eu poder esconder essa informacao quando
    // mostrando o registro (visto que n faria muito sentido mostrar mais do que
    // um do mesmo produto no registro do sistema)
    if ((p.n > 1) && incluirN) printf("- x%d\n", p.n);
    printf("- ID: %d\n", p.id);

    // caso houver desconto...
    if (p.desconto > 0) {
        // ... adicione esse desconto para as informacoes do produto...
        printf("- Preco: %.2f (%.2f) // %0.f%% de desconto",
               p.preco - (p.preco * p.desconto), p.preco, p.desconto * 100);
        // ...e calcule o desconto multiplicando pelo preco e subtraindo do
        // total
    } else {
        // se n houver desconto, n precisa mostrar
        printf("- Preco: %.2f", p.preco);
    }
    printf("\n");
    linhaDiv(20, '*');
}

int temNoCarrinho(Carrinho c, int novoId) {
    // loop simples que passa pela array da struct Carrinho ate encontrar um id,
    // se n for encontrado, produto nao esta no carrinho
    int encontrado = 0;
    for (int i = 0; i < c.quantidade; i++) {
        if (c.produtos[i].id == novoId) {
            encontrado = 1;
        }
    }
    return encontrado;
}

int temNoSistema(Sistema s, int novoId) {
    // mesma funcao que acima, apenas que para analisar o sistema
    int encontrado = 0;
    for (int i = 0; i < s.quantidade; i++) {
        if (s.produtos[i].id == novoId) {
            encontrado = 1;
        }
    }

    return encontrado;
}

void comprarProduto(Sistema s, Carrinho *c, int novoId) {
    // caso o produto sendo comprado esteja presente no sistema...
    if (temNoSistema(s, novoId)) {
        // ... faca um loop pelos elementos do sistema
        for (int i = 0; i < s.quantidade; i++) {
            // se no sistema estiver um produto com o mesmo id do produto sendo
            // comprado...
            if (s.produtos[i].id == novoId) {
                // ...verifique se esse produto ja esta no carrinho.
                if (!temNoCarrinho(*c, novoId)) {
                    // se n estiver, adicione ele pro primeiro espaco vazio na
                    // array, indo pro final e depois aumente a quantidade de
                    // produtos total no carrinho
                    c->produtos[c->quantidade] = s.produtos[i];
                    c->quantidade++;

                } else {
                    // se o produto ja estiver no carrinho, faca um segundo
                    // loop. A diferenca e que esse loop e para passar pelo
                    // carrinho, nao pelo sistema como o acima
                    for (int j = 0; j < c->quantidade; j++) {
                        // ao encontrar a posicao do produto ja presente...
                        if (s.produtos[i].id == c->produtos[j].id) {
                            // adicionar 1 para seu n, definindo que ha
                            // multiplos dele presente obs: c->quantidade
                            // armazena apenas o numero de produtos unicos, logo
                            // aumentar o n do produto n quer dizer que
                            // c->quantidade tambem aumenta
                            c->produtos[j].n++;
                        }
                    }
                }
            }
        }
    } else {
        printf("Produto com ID %d nao registrado no sistema\n", novoId);
    }

    ordenarSelecao(c->produtos, c->quantidade);
}

void removerDoCarrinho(Carrinho *c, int idRemover) {
    int removerInd;
    int unico = 0;
    for (int i = 0; i < c->quantidade; i++) {
        if (c->produtos[i].id == idRemover) {
            if (c->produtos[i].n == 1) {
                unico = 1;
                removerInd = i;
            } else {
                c->produtos[i].n--;
            }
        }
    }

    // Pra remover um elemento da lista e um pouco complicado.
    // - Primeiro, encontrar indice do elemento a remover
    // - trocar esse elemento com o ultimo elemento da array
    // - diminuir o tamanho da array por 1 pra empurrar pra fora o elemento
    // - aplicar alg de ordenacao
    if (unico) {
        trocar(&c->produtos[removerInd], &c->produtos[c->quantidade - 1]);
        c->quantidade--;
        ordenarSelecao(c->produtos, c->quantidade);
    }
}

void listarProdutos(Sistema s) {
    printf("Registro de Produtos: \n");
    // loop simples que aplica a funcao infoProduto a todos os produtos do
    // sistema
    if (s.quantidade > 0) {
        for (int i = 0; i < s.quantidade; i++) {
            infoProduto(s.produtos[i], 0);
        }
    } else {
        printf("Registro Vazio\n");
    }
    linhaDiv(25, '-');
}

void visualizarCarrinho(Carrinho c) {
    printf("Carrinho: \n");

    // loop simples que aplica a funcao infoProduto a todos os produtos do
    // carrinho
    if (c.quantidade > 0) {
        for (int i = 0; i < c.quantidade; i++) {
            infoProduto(c.produtos[i], 1);
        }
    } else {
        printf("Carrinho Vazio\n");
    }

    linhaDiv(25, '-');
}

void cadastrarProduto(Sistema *s, Produto p) {
    if (temNoSistema(*s, p.id)) {
        printf("O Produto de ID %d ja foi registrado.\n", p.id);
    } else {
        // se o produto ja n estiver no sistema, adicionar ele pro
        // primeiro espaco vazio na array
        s->produtos[s->quantidade] = p;
        ++s->quantidade;
    }

    ordenarSelecao(s->produtos, s->quantidade);
}

void finalizarCompras(Carrinho *c) {
    // memset e uma funcao de string.h que permite resetar todas as posicoes de
    // uma array pra um certo valor, nesse caso, 0
    // Obs: c->quantidade * sizeof(Produto) e uma maneira de determinar o
    // tamanho da array, multiplicando o numero de elementos pelo tamanho da
    // struct criada
    memset(c->produtos, 0, c->quantidade * sizeof(Produto));
    // depois, resetar a quantidade para 0
    c->quantidade = 0;
}

float obterTotal(Carrinho *c) {
    // adquirir o total passando por todos os items no carrinhos, lembrando
    // de levar em consideracao os descontos
    float total = 0;
    for (int i = 0; i < c->quantidade; i++) {
        float preco = (c->produtos[i].preco -
                       (c->produtos[i].preco * c->produtos[i].desconto)) *
                      c->produtos[i].n;
        printf("* %s x %d - %.2f\n", c->produtos[i].nome, c->produtos[i].n,
               preco);

        total += preco;
    }
    return total;
}
