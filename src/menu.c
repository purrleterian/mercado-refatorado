#include "main.h"

int menu() {
    // Buffer pra guardar o input do usuario que determina a acao
    char escolhaFluxo[MAX_BUFFER];

    printf("\nSistema interno de compras do Mercado %s\n", MERCADO_NOME);
    printf("Como gostaria de prosseguir?\n");
    linhaDiv(30, '-');
    printf("(1) Adicionar produto ao registro do sistema\n");
    printf("(2) Adicionar produto ao carrinho\n");
    printf("(3) Remover produto do carrinho\n");
    printf("(4) Listar os produtos no registro\n");
    printf("(5) Listar os produtos no carrinho\n");
    printf("(6) Concluir compras\n");
    printf("(7) Sair\n");

    printf(">> ");
    fgets(escolhaFluxo, MAX_BUFFER, stdin);

    // 'atoi' converte ascii para integer, assim o input de fget pode ser usado
    // pra comparar os numeros em switch
    switch (atoi(escolhaFluxo)) {
        case 1:;
            // definir variaveis que vao compor o novo produto
            char regiBuffer[MAX_BUFFER];
            char novoNome[MAX_NOME];
            int idNovoSistema;
            float novoPreco, novoDesc;

            int teveErro = 0;
            int resultadoProd;
            Produto novoProduto;

            printf("ID unico do produto (Numero inteiro):\n");
            printf(">> ");

            // fgets combinado com sscanf e um bom jeito de evitar deixar
            // linhas (\n) indesejadas no buffer, e ao mesmo tempo convertendo
            // input para outros tipos (nesse caso buffer armazenando no %d)
            fgets(regiBuffer, MAX_BUFFER, stdin);

            // Scanf sempre retorna o numero de inputs registrados com
            // sucesso...
            resultadoProd = sscanf(regiBuffer, "%d", &idNovoSistema);

            // ...ou seja se esse numero for '1' entao nao houveram erros
            if (resultadoProd == 1) {
                novoProduto.id = idNovoSistema;
            } else {
                // se tiveram erros, lembrar disso para impedir que info com
                // erro seja adicionada mais na frente
                teveErro = 1;
                printf("Erro ao registrar ID do produto\n");
            }

            // repetir o processo acima pros outros parametros
            printf("Nome do produto (Limite de %d caracteres) \n", MAX_NOME);
            printf(">> ");

            fgets(regiBuffer, MAX_BUFFER, stdin);
            resultadoProd = sscanf(regiBuffer, "%1000s", novoNome);

            if (resultadoProd == 1) {
                strcpy(novoProduto.nome, novoNome);
            } else {
                teveErro = 1;
                printf("Erro ao registrar nome do produto\n");
            }

            printf("Preco do produto (Numero decimal, separacao por ponto):\n");
            printf(">> ");

            fgets(regiBuffer, MAX_BUFFER, stdin);
            resultadoProd = sscanf(regiBuffer, "%f", &novoPreco);

            if (resultadoProd == 1) {
                novoProduto.preco = novoPreco;
            } else {
                teveErro = 1;
                printf("Erro ao registrar o preco do produto\n");
            }

            printf(
                "Desconto do produto (Numero decimal, separacao por ponto): "
                "\n");
            printf(">> ");

            fgets(regiBuffer, MAX_BUFFER, stdin);

            resultadoProd = sscanf(regiBuffer, "%f", &novoDesc);

            if (novoDesc < 0 || novoDesc > 1) {
                teveErro = 1;
                printf(
                    "\nPor favor insira um valor apropriado para o desconto\n");
            }

            if (resultadoProd == 1) {
                novoProduto.desconto = novoDesc;
            } else {
                teveErro = 1;
                printf("Erro ao registrar o desconto do produto\n");
            }

            // produtos sempre vao comecar com apenas 1, nao e possivel
            // registrar 2 do mesmo produto ao mesmo tempo
            novoProduto.n = 1;

            // se nenhum erro foi registrado no caminho, cadastrar o produto
            if (!teveErro) {
                cadastrarProduto(&sistemaMercado, novoProduto);
            }

            break;

        case 2:;
            char idBuffer[MAX_BUFFER];
            int idNovoCarrinho;

            printf("ID unico do produto (Numero inteiro): \n");
            printf(">> ");
            fgets(idBuffer, MAX_BUFFER, stdin);
            int resultadoCarr = sscanf(idBuffer, "%d", &idNovoCarrinho);
            if (resultadoCarr == 1) {
                comprarProduto(sistemaMercado, &carrinhoMercado,
                               idNovoCarrinho);
            } else {
                printf("\nErro ao receber input\n");
            }

            break;

        case 3:;
            char idRemoverBuffer[MAX_BUFFER];
            int idRemover;

            printf("ID unico do produto (Numero inteiro): \n");
            printf(">> ");
            fgets(idRemoverBuffer, MAX_BUFFER, stdin);
            int resultadoRemover = sscanf(idRemoverBuffer, "%d", &idRemover);
            if (resultadoRemover == 1) {
                removerDoCarrinho(&carrinhoMercado, idRemover);

            } else {
                printf("\nErro ao receber input\n");
            }

            break;

        case 4:
            listarProdutos(sistemaMercado);
            break;

        case 5:
            visualizarCarrinho(carrinhoMercado);
            break;

        case 6:
            // Ao concluir as compras:
            // - somar os precos no carrinho
            // - retornar o total
            // - esvaziar o carrinho

            printf("\n\n");
            banner("Recibo");

            linhaDiv(35, '*');
            printf("Total: %.2f\n", obterTotal(&carrinhoMercado));

            linhaDiv(35, '*');
            printf("\n");
            finalizarCompras(&carrinhoMercado);
            break;

        case 7:
            return 0;
            break;
    }

    return 1;
}