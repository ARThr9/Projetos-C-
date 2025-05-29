#include <iostream>
#include <string>
using namespace std;

int main()
{
    int opcaoCategoria, opcaoItem, quantidade;
    double totalPedido = 0.00;
    double desconto = 0.00;
    char adicionarMais = 's';
    string nome;

    cout << "Bem vindo à Lanchonete!\n";
    cout << "Informe seu nome: ";
    cin >> nome;

    while (adicionarMais == 'S' || adicionarMais == 's')
    {
        cout << "\nOla " << nome << "! Escolha uma categoria: \n";
        cout << "1 - Lanches\n";
        cout << "2 - Bebidas\n";
        cout << "3 - Sobremesas\n";
        cout << "4 - Finalizar Pedido\n";
        cout << "Escolha uma opcao: ";
        cin >> opcaoCategoria;

        switch (opcaoCategoria)
        {
        case 1: // Menu de Lanches
            cout << "1 - Hamburguer R$10\n";
            cout << "2 - Cheeseburguer R$12\n";
            cout << "3 - X-Bacon R$15\n";
            cout << "Escolha uma opcao: ";
            cin >> opcaoItem;

            switch (opcaoItem)
            {
            case 1:
                cout << "Digite a quantidade de Hamburguer: ";
                cin >> quantidade;
                totalPedido += 10.00 * quantidade;
                break;

            case 2:
                cout << "Digite a quantidade de Cheeseburguer: ";
                cin >> quantidade;
                totalPedido += 12.00 * quantidade;
                break;

            case 3:
                cout << "Digite a quantidade de X-Bacon: ";
                cin >> quantidade;
                totalPedido += 15.00 * quantidade;
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
            }
            break;

        case 2: // Menu de Bebidas
            cout << "1 - Refrigerante R$5\n";
            cout << "2 - Suco R$7\n";
            cout << "3 - Agua R$3\n";
            cout << "Escolha uma opcao: ";
            cin >> opcaoItem;

            switch (opcaoItem)
            {
            case 1:
                cout << "Digite a quantidade de refrigerante: ";
                cin >> quantidade;
                totalPedido += 5.00 * quantidade;
                break;

            case 2:
                cout << "Digite a quantidade de suco: ";
                cin >> quantidade;
                totalPedido += 7.00 * quantidade;
                break;

            case 3:
                cout << "Digite a quantidade de agua: ";
                cin >> quantidade;
                totalPedido += 3.00 * quantidade;
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
            }
            break;

        case 3: // Menu de Sobremesas
            cout << "1 - Sorvete R$8\n";
            cout << "2 - Bolo R$6\n";
            cout << "3 - Pudim R$5\n";
            cout << "Escolha uma opcao: ";
            cin >> opcaoItem;

            switch (opcaoItem)
            {
            case 1:
                cout << "Digite a quantidade de Sorvete: ";
                cin >> quantidade;
                totalPedido += 8.00 * quantidade;
                break;

            case 2:
                cout << "Digite a quantidade de Bolo: ";
                cin >> quantidade;
                totalPedido += 6.00 * quantidade;
                break;

            case 3:
                cout << "Digite a quantidade de Pudim: ";
                cin >> quantidade;
                totalPedido += 5.00 * quantidade;
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
            }
            break;

        case 4: // Finalizar Pedido
            cout << "\nFinalizar Pedido\n";

            if (totalPedido > 50.00)
            {
                desconto = 0.10 * totalPedido;
                totalPedido -= desconto;
                cout << "Desconto de 10% aplicado! (-R$" << desconto << ")\n";
            }

            cout << "O valor total do pedido foi de: R$" << totalPedido << endl;
            return 0; // Encerra o programa ao finalizar o pedido

        default:
            cout << "Opcao invalida!\n";
            break;
        }

        // Pergunta se o cliente quer adicionar mais itens
        cout << "\nDeseja adicionar mais itens ao pedido? (S/N): ";
        cin >> adicionarMais;
    }
    cout << "\nFinalizar Pedido\n";

    if (totalPedido > 50.00)
    {
        desconto = 0.10 * totalPedido;
        totalPedido -= desconto;
        cout << "Desconto de 10% aplicado! (-R$" << desconto << ")\n";
    }

    cout << "O valor total do pedido foi de: R$" << totalPedido << endl;
    return 0; // Encerra o programa ao finalizar o pedido

    return 0;
}
