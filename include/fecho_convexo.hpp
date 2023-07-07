#ifndef FECHOCONVEXO_HPP
#define FECHOCONVEXO_HPP

// Estrutura que representa um ponto no plano cartesiano
struct Ponto {
    int x; // coordenada x do ponto
    int y; // coordenada y do ponto
};

// Estrutura que representa uma reta formada por dois pontos
struct Reta {
    Ponto ponto1; // primeiro ponto da reta
    Ponto ponto2; // segundo ponto da reta
};

// Estrutura que representa um fecho convexo, composto por um conjunto de pontos
struct FechoConvexo {
    Ponto* pontos; // array de pontos do fecho convexo
    int tamanho;   // quantidade de pontos no fecho convexo
};

#endif // FECHOCONVEXO_HPP
