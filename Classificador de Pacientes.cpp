#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int Max_Linhas = 11;
const int Max_Colunas = 7;
const int Min_Colunas = 3;

// Função para calcular a distância euclidiana entre dois pacientes (ignorando a classificação)
float distanciaEuclidiana(float pacienteA[], float pacienteB[], int numColunas) {
    float soma = 0.0;
    for (int i = 0; i < numColunas - 1; i++) {
        soma += pow(pacienteA[i] - pacienteB[i], 2);
    }
    return sqrt(soma);
} 

// Função para exibir a tabela formatada
void exibirTabela(float tabela[][Max_Colunas], int numLinhas, int numColunas) {
    cout << "\nTabela de Pacientes:\n";
    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {
            cout << setw(8) << fixed << setprecision(2) << tabela[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numColunas;
    
    // Solicita o número de colunas (3 a 7)
    do {
        cout << "Digite o numero de indicadores (3 a 7): ";
        cin >> numColunas;
    } while (numColunas < Min_Colunas || numColunas > Max_Colunas);

    float tabela[Max_Linhas][Max_Colunas];

    // Preenchimento da tabela de pacientes históricos
    cout << "\nInforme os valores dos indicadores para cada um dos 10 pacientes históricos:\n";
    for (int i = 0; i < Max_Linhas - 1; i++) { // Apenas os 10 primeiros pacientes
        cout << "Paciente " << i + 1 << ":\n";
        for (int j = 0; j < numColunas - 1; j++) { // Até a penúltima coluna
            cout << "  Indicador " << j + 1 << ": ";
            cin >> tabela[i][j];
        }
        
        
        do {
            cout << "  Classificacao (1.0 para saudavel, -1.0 para doente): ";
            cin >> tabela[i][numColunas - 1];
        } while (tabela[i][numColunas - 1] != 1.0 && tabela[i][numColunas - 1] != -1.0);
    }

    // Preenche do novo paciente
    cout << "\nInforme os indicadores do novo paciente:\n";
    for (int j = 0; j < numColunas - 1; j++) {
        cout << "  Indicador " << j + 1 << ": ";
        cin >> tabela[Max_Linhas - 1][j];
    }

    tabela[Max_Linhas - 1][numColunas - 1] = 0.0;
    
    
    // Classificação do novo paciente
    int indiceMaisProximo = 0;
    float menorDistancia = distanciaEuclidiana(tabela[Max_Linhas - 1], tabela[0], numColunas);

    for (int i = 1; i < Max_Linhas - 1; i++) {
        float distancia = distanciaEuclidiana(tabela[Max_Linhas - 1], tabela[i], numColunas);
        if (distancia < menorDistancia) {
            menorDistancia = distancia;
            indiceMaisProximo = i;
        }
    }

    // Determina a condição do novo paciente
    float classificacaoMaisProxima = tabela[indiceMaisProximo][numColunas - 1];
tabela[Max_Linhas - 1][numColunas - 1] = classificacaoMaisProxima;  

cout << "\nResultado da Classificacao:\n";
if (classificacaoMaisProxima == 1.0) {
    cout << "O paciente tem maior chance de estar saudavel.\n";
} else {
    cout << "O paciente tem maior chance de estar doente.\n";
}


    // Exibe a tabela completa
    exibirTabela(tabela, Max_Linhas, numColunas);

    return 0;
}
