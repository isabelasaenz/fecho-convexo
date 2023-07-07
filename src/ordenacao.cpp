#include "ordenacao.hpp"

using namespace std;

void adicionarPonto(Ponto*& pontos, int& tamanho, int x, int y) {
    Ponto* novoPonto = new Ponto[tamanho + 1];
    for (int i = 0; i < tamanho; i++) {
        novoPonto[i] = pontos[i];
    }
    novoPonto[tamanho] = {x, y};

    delete[] pontos;
    pontos = novoPonto;
    tamanho++;
}

int orientacao(Ponto p, Ponto m, Ponto n) {
    int valor = (m.y - p.y) * (n.x - m.x) - (m.x - p.x) * (n.y - m.y);

    if (valor == 0)
        return 0;
    else if (valor > 0)
        return 1;
    else
        return -1;
}

void merge(Ponto* arr, int esq, int centro, int dir) {
    int i, j, k;
    int n1 = centro - esq + 1;
    int n2 = dir - centro;

    Ponto* E = new Ponto[n1];
    Ponto* D = new Ponto[n2];

    for (i = 0; i < n1; i++)
        E[i] = arr[esq + i];
    for (j = 0; j < n2; j++)
        D[j] = arr[centro + 1 + j];

    i = 0;
    j = 0;
    k = esq;
    while (i < n1 && j < n2) {
        if (E[i].x <= D[j].x) {
            arr[k] = E[i];
            i++;
        } else {
            arr[k] = D[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = E[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = D[j];
        j++;
        k++;
    }

    delete[] E;
    delete[] D;
}

void mergeSort(Ponto* arr, int esq, int dir) {
    if (esq < dir) {
        int centro = esq + (dir - esq) / 2;

        mergeSort(arr, esq, centro);
        mergeSort(arr, centro + 1, dir);

        merge(arr, esq, centro, dir);
    }
}

void insertionSort(Ponto* arr, int n) {
    for (int i = 1; i < n; i++) {
        Ponto chave = arr[i];
        int j = i - 1;
        while (j >= 0 && (arr[j].x > chave.x || (arr[j].x == chave.x && arr[j].y > chave.y))) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

void countingSort(Ponto* arr, int n) {
    Ponto* saida = new Ponto[n];
    int valor_max = arr[0].x;
    for (int i = 1; i < n; i++) {
        if (arr[i].x > valor_max) {
            valor_max = arr[i].x;
        }
    }

    int* count = new int[valor_max + 1];
    for (int i = 0; i <= valor_max; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[arr[i].x]++;
    }
    for (int i = 1; i <= valor_max; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        saida[count[arr[i].x] - 1] = arr[i];
        count[arr[i].x]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = saida[i];
    }

    delete[] saida;
    delete[] count;
}

int encontrarPontoInicial(Ponto* pontos, int tamanho) {
    int indice_inicial = 0;
    for (int i = 1; i < tamanho; i++) {
        if (pontos[i].x < pontos[indice_inicial].x || (pontos[i].x == pontos[indice_inicial].x && pontos[i].y < pontos[indice_inicial].y)) {
            indice_inicial = i;
        }
    }
    return indice_inicial;
}

void sortPontos(Ponto* arr, int n) {
    for (int i = 1; i < n; i++) {
        Ponto chave = arr[i];
        int j = i - 1;
        while (j >= 0 && (arr[j].x > chave.x || (arr[j].x == chave.x && arr[j].y > chave.y))) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

FechoConvexo scanGraham(Ponto* pontos, int tamanho, int tipo_sort) {
    FechoConvexo fecho;
    fecho.tamanho = 0;
    fecho.pontos = nullptr;

    if (tamanho < 3) {
        cerr << "ERRO: NÃO É POSSÍVEL CALCULAR O FECHO CONVEXO COM MENOS DE 3 PONTOS" << endl;
        return fecho;
    }

    sortPontos(pontos, tamanho);

    switch (tipo_sort) {
        case 1:
            mergeSort(pontos, 0, tamanho - 1);
            break;
        case 2:
            insertionSort(pontos, tamanho);
            break;
        case 3:
            countingSort(pontos, tamanho);
            break;
        default:
            cerr << "ERRO: TIPO DE ORDENAÇÃO INVÁLIDO" << endl;
            return fecho;
    }

    Ponto* pilha = new Ponto[tamanho];
    int topo = 2;
    pilha[0] = pontos[0];
    pilha[1] = pontos[1];
    pilha[2] = pontos[2];

    for (int i = 3; i < tamanho; i++) {
        while (topo > 0 && orientacao(pilha[topo - 1], pilha[topo], pontos[i]) != -1) {
            topo--;
        }
        topo++;
        pilha[topo] = pontos[i];
    }

    fecho.tamanho = topo + 1;
    fecho.pontos = pilha;
    return fecho;
}

FechoConvexo marcharJarvis(Ponto* pontos, int tamanho) {
    FechoConvexo fecho;
    fecho.tamanho = 0;
    fecho.pontos = nullptr;

    if (tamanho < 3) {
        cerr << "ERRO: QUANTIDADE DE PONTOS INVÁLIDA" << endl;
        return fecho;
    }

    int indice_inicial = encontrarPontoInicial(pontos, tamanho);

    Ponto* fechoConvexo = new Ponto[tamanho];
    int indice_atual = indice_inicial;
    int prox_indice;

    int i = 0;
    do {
        fechoConvexo[i++] = pontos[indice_atual];
        prox_indice = (indice_atual + 1) % tamanho;

        for (int j = 0; j < tamanho; j++) {
            if (orientacao(pontos[indice_atual], pontos[j], pontos[prox_indice]) == -1) {
                prox_indice = j;
            }
        }

        indice_atual = prox_indice;
    } while (indice_atual != indice_inicial);

    fecho.tamanho = i;
    fecho.pontos = fechoConvexo;
    return fecho;
}
