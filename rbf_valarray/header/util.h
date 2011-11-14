#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <valarray>

int randomize (int lower, int upper);
float randomize (float lower, float upper);

bool comparar_vectores (const std::valarray<float> & a, const std::valarray<float> & b);

std::vector<float> sumar_vectores (std::vector<float> & a, std::vector<float> & b);

std::vector<float> restar_vectores (std::vector<float> & a, std::vector<float> & b);

float multiplicar_vectores (std::vector<float> & a, std::vector<float> & b);

std::vector<float> dividir_vector (std::vector<float> & a, float divisor);

float norma2 (const std::valarray<float> &v);

int signo (float a);

void imprimir_vector (std::vector<float> & a);

#endif
