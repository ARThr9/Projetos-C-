/*
    Trabalho 2° Bimestre - Técnicas de Programação 2
    Nome: Alvaro Carvalho Tomazeli   RA: 2279900
    Nome: Arthur Bis Rordrigues      RA: 2295221
    Nome: Murilo Garibaldi Antonelli RA:2297370 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Usuario {
    int id;
    std::string nome;
    int idade;
    double saldo;
};

Usuario *adicionarUsuario(Usuario *usuarios, int& totalUsuarios, int& capacidade, const std::string& nome, int idade, double saldo, int& proximoId);
Usuario *removerUsuario(Usuario *usuarios, int& totalUsuarios, int id);
Usuario *redimensionarVetor(Usuario *usuarios, int& capacidade);
void buscarUsuario(const Usuario *usuarios, int totalUsuarios, int id);
bool transferirSaldo(Usuario *usuarios, int totalUsuarios, int idOrigem, int idDestino, double valor);
void salvarNoArquivo(const Usuario *usuarios, int totalUsuarios, const char* nomeArquivo);

void limparBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

Usuario *adicionarUsuario(Usuario *usuarios, int& totalUsuarios, int& capacidade, const std::string& nome, int idade, double saldo, int& proximoId) {
    if (totalUsuarios >= capacidade) {
        usuarios = redimensionarVetor(usuarios, capacidade);
    }
    if (usuarios == nullptr) {
        cout << "Erro ao redimensionar o vetor de usuarios.\n";
        return nullptr;
    }
    usuarios[totalUsuarios].id = proximoId++;
    usuarios[totalUsuarios].nome = nome;
    usuarios[totalUsuarios].idade = idade;
    usuarios[totalUsuarios].saldo = saldo;
    totalUsuarios++;
    cout << "Usuario inserido com id " << usuarios[totalUsuarios-1].id << ".\n";
    return usuarios;
}

Usuario *removerUsuario(Usuario *usuarios, int& totalUsuarios, int id) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == id) {
            for (int j = i; j < totalUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            totalUsuarios--;
            cout << "Usuario " << id << " removido com sucesso.\n";
            return usuarios;
        }
    }
    cout << "Erro: Usuario " << id << " nao encontrado.\n";
    return usuarios;
}

Usuario *redimensionarVetor(Usuario *usuarios, int& capacidade) {
    int novaCapacidade = capacidade * 2;
    Usuario *novoVetor = new Usuario[novaCapacidade];
    if (novoVetor == nullptr) return nullptr;
    for (int i = 0; i < capacidade; i++) {
        novoVetor[i] = usuarios[i];
    }
    delete[] usuarios;
    capacidade = novaCapacidade;
    return novoVetor;
}

void buscarUsuario(const Usuario *usuarios, int totalUsuarios, int id) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == id) {
            cout << "Usuario " << id << " tem saldo de R$" 
                 << fixed << setprecision(2) << usuarios[i].saldo << ".\n";
            return;
        }
    }
    cout << "Erro: Usuario " << id << " nao encontrado.\n";
}

bool transferirSaldo(Usuario *usuarios, int totalUsuarios, int idOrigem, int idDestino, double valor) {
    int indexOrigem = -1, indexDestino = -1;
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == idOrigem) indexOrigem = i;
        if (usuarios[i].id == idDestino) indexDestino = i;
    }
    if (indexOrigem == -1 || indexDestino == -1) {
        cout << "Erro: Usuario(s) nao encontrado(s).\n";
        return false;
    }
    if (usuarios[indexOrigem].saldo < valor || valor <= 0) {
        cout << "Erro: Saldo insuficiente ou valor invalido.\n";
        return false;
    }
    usuarios[indexOrigem].saldo -= valor;
    usuarios[indexDestino].saldo += valor;
    cout << "Transferencia realizada.\n";
    return true;
}

void salvarNoArquivo(const Usuario *usuarios, int totalUsuarios, const char* nomeArquivo) {
    ofstream arquivo(nomeArquivo);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }
    arquivo << totalUsuarios << endl;
    for (int i = 0; i < totalUsuarios; i++) {
        arquivo << usuarios[i].nome << ","
                << usuarios[i].idade << ","
                << fixed << setprecision(2) << usuarios[i].saldo << "\n";
    }
    arquivo.close();
    cout << "Arquivo salvo com sucesso." << endl;
}

int main() {
    const int capacidadeInicial = 10;
    int capacidade = capacidadeInicial;
    int totalUsuarios = 0;
    int proximoId = 1;
    Usuario *usuarios = new Usuario[capacidadeInicial];
    const char* nomeArquivo = "usuarios_BMbank.txt";
    int opcao;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Adicionar um usuario\n";
        cout << "2. Adicionar varios usuarios\n";
        cout << "3. Buscar usuario por ID\n";
        cout << "4. Transferir saldo entre usuarios\n";
        cout << "5. Remover usuario por ID\n";
        cout << "6. Carregar arquivo de usuarios para a memoria e sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        if (cin.fail()) {
            cout << "Entrada invalida. Tente novamente.\n";
            limparBuffer();
            continue;
        }

        limparBuffer();

        switch (opcao) {
            case 1: {
                string nome;
                int idade;
                double saldo;
                cout << "Nome: ";
                getline(cin, nome);
                if (nome.length() > 100) {
                    nome = nome.substr(0, 100);
                    cout << "Nome excede 100 caracteres.\n";
                }
                cout << "Idade: ";
                while (!(cin >> idade) || idade < 0) {
                    cout << "Idade invalida. Digite novamente: ";
                    limparBuffer();
                }
                cout << "Saldo: R$";
                while (!(cin >> saldo) || saldo < 0) {
                    cout << "Saldo invalido. Digite novamente: ";
                    limparBuffer();
                }
                limparBuffer();
                usuarios = adicionarUsuario(usuarios, totalUsuarios, capacidade, nome, idade, saldo, proximoId);
                break;
            }

            case 2: {
                int quantidade;
                cout << "Quantos usuarios deseja adicionar? ";
                cin >> quantidade;
                limparBuffer();
                for (int i = 0; i < quantidade; i++) {
                    string nome;
                    int idade;
                    double saldo;
                    cout << "Nome do usuario " << (i + 1) << ": ";
                    getline(cin, nome);
                    if (nome.length() > 100) {
                        nome = nome.substr(0, 100);
                        cout << "Nome excede 100 caracteres.\n";
                    }
                    cout << "Idade: ";
                    while (!(cin >> idade) || idade < 0) {
                        cout << "Idade invalida. Digite novamente: ";
                        limparBuffer();
                    }
                    cout << "Saldo: R$";
                    while (!(cin >> saldo) || saldo < 0) {
                        cout << "Saldo invalido. Digite novamente: ";
                        limparBuffer();
                    }
                    limparBuffer();
                    if (saldo < 0) {
                        cout << "Saldo nao pode ser negativo.\n";
                        continue;
                    }
                    usuarios = adicionarUsuario(usuarios, totalUsuarios, capacidade, nome, idade, saldo, proximoId);
                }
                break;
            }

            case 3: {
                int id;
                cout << "Digite o ID do usuario: ";
                cin >> id;
                limparBuffer();
                buscarUsuario(usuarios, totalUsuarios, id);
                break;
            }

            case 4: {
                int origem, destino;
                double valor;
                cout << "ID do remetente: ";
                cin >> origem;
                cout << "ID do destinatario: ";
                cin >> destino;
                cout << "Valor: R$";
                cin >> valor;
                limparBuffer();
                transferirSaldo(usuarios, totalUsuarios, origem, destino, valor);
                break;
            }

            case 5: {
                int id;
                cout << "Digite o ID do usuario que deseja remover: ";
                cin >> id;
                limparBuffer();
                usuarios = removerUsuario(usuarios, totalUsuarios, id);
                break;
            }

            case 6: {
                salvarNoArquivo(usuarios, totalUsuarios, nomeArquivo);
                delete[] usuarios;
                return 0;
            }

            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }

    } while (true);

}