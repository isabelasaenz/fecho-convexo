#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include "fecho_convexo.hpp"
#include <iomanip>
#include <iostream>

// Adiciona um ponto ao conjunto de pontos do fecho convexo
void adicionarPonto(Ponto*& pontos, int& tamanho, int x, int y);

// Determina a orientação de três pontos no plano cartesiano
int orientacao(Ponto p, Ponto m, Ponto n);

// Funções de ordenação
void merge(Ponto* arr, int esq, int centro, int dir);
void mergeSort(Ponto* arr, int esq, int dir);
void insertionSort(Ponto* arr, int n);
void countingSort(Ponto* arr, int n);
void sortPontos(Ponto* arr, int n);

// Encontra o ponto inicial para o algoritmo de Graham
int encontrarPontoInicial(Ponto* pontos, int tamanho);

// Algoritmo de Graham para encontrar o fecho convexo
FechoConvexo scanGraham(Ponto* pontos, int tamanho, int tipo_sort);

// Algoritmo de Jarvis para encontrar o fecho convexo
FechoConvexo marcharJarvis(Ponto* pontos, int tamanho);

#endif // ORDENACAO_HPP
