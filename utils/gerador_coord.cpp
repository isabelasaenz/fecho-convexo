// Cria um arquivo com coordenadas aleatórias para testes

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Coordenada {
    int x;
    int y;
};

void gera_coordenadas(int num_coordenadas, Coordenada* coordenadas) {
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < num_coordenadas; i++) {
        coordenadas[i].x = rand() % 501;
        coordenadas[i].y = rand() % 501;
    }
}

void save_coordenadas(const Coordenada* coordenadas, int num_coordenadas, const string& nome_arquivo) {
    ofstream arquivo(nome_arquivo);
    if (arquivo.is_open()) {
        for (int i = 0; i < num_coordenadas; i++) {
            arquivo << coordenadas[i].x << ' ' << coordenadas[i].y << '\n';
        }
        arquivo.close();
    } else {
        cout << "ERRO AO GERAR AS COORDENADAS\n";
    }
}

int main() {
    int num_coordenadas = 500;
    Coordenada coordenadas[num_coordenadas];

    gera_coordenadas(num_coordenadas, coordenadas);

    string nome_arquivo = "input/ENTRADA500.txt";
    save_coordenadas(coordenadas, num_coordenadas, nome_arquivo);

    cout << "COORDENADAS SALVAS EM " << nome_arquivo << ".\n";

    return 0;
}
