#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "ordenacao.hpp"

using namespace std;

const int PRECISAO = 3;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "ARGUMENTOS INVÁLIDOS" << endl;
        return 1;
    }

    ifstream arquivo_entrada(argv[1]);
    if (!arquivo_entrada.is_open()) {
        cerr << "ERRO AO ABRIR O ARQUIVO DE ENTRADA: " << argv[1] << endl;
        return 1;
    }

    Ponto* pontos = nullptr;
    int tamanho = 0;
    int x, y;
    while (arquivo_entrada >> x >> y) {
        adicionarPonto(pontos, tamanho, x, y);
    }

    FechoConvexo fechoConvexo;

    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();

    // GRAHAM+MERGE
    start = chrono::high_resolution_clock::now();
    fechoConvexo = scanGraham(pontos, tamanho, 1);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo_merge = end - start;

    // GRAHAM+INSERTION
    start = chrono::high_resolution_clock::now();
    fechoConvexo = scanGraham(pontos, tamanho, 2);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo_insertion = end - start;

    // GRAHAM+LINEAR
    start = chrono::high_resolution_clock::now();
    fechoConvexo = scanGraham(pontos, tamanho, 3);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo_linear = end - start;

    // JARVIS
    start = chrono::high_resolution_clock::now();
    fechoConvexo = marcharJarvis(pontos, tamanho);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo_jarvis = end - start;

    cout << "FECHO CONVEXO:" << endl;
    for (int i = 0; i < fechoConvexo.tamanho; i++) {
        cout << fechoConvexo.pontos[i].x << " " << fechoConvexo.pontos[i].y << endl;
    }
    
    cout << endl;
    cout << "GRAHAM+MERGESORT: " << fixed << setprecision(PRECISAO) << tempo_merge.count() << "s" << endl;
    cout << "GRAHAM+INSERTIONSORT: " << fixed << setprecision(PRECISAO) << tempo_insertion.count() << "s" << endl;
    cout << "GRAHAM+COUNTINGSORT: " << fixed << setprecision(PRECISAO) << tempo_linear.count() << "s" << endl;
    cout << "JARVIS: " << fixed << setprecision(PRECISAO) << tempo_jarvis.count() << "s" << endl;

    ofstream arquivo_saida("output.dat");
    if (!arquivo_saida.is_open()) {
        cerr << "ERRO AO ABRIR O ARQUIVO DE SAIDA" << endl;
        return 1;
    }

    for (int i = 0; i < fechoConvexo.tamanho; i++) {
        arquivo_saida << fechoConvexo.pontos[i].x << " " << fechoConvexo.pontos[i].y << endl;
    }
    arquivo_saida << fechoConvexo.pontos[0].x << " " << fechoConvexo.pontos[0].y << endl;

    arquivo_saida.close();
    delete[] pontos;
    delete[] fechoConvexo.pontos;

    return 0;
}
