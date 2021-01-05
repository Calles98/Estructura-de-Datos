//
// Created by Rodrigo Calles on 2020-11-28.
//

#ifndef MONTON_MONTONMIN_H
#define MONTON_MONTONMIN_H

#include <iostream>
#include <cmath>
#include "Excepcion.h"
 using namespace std;

template <typename T>
bool Min(T a, T b){
    return a < b;
}


template <typename T, bool(*criterio)(T,T) = Min>
class MontonMin {
public:

    /**
     *@brief Constructor de la clase
     */
    MontonMin();

    /**
     *@brief Destructor de la clase
     */
    ~MontonMin();

    /**
     * @brief Constructor de copias de la clase
     * @param M Una referencia a un montón
     */
    MontonMin(const MontonMin<T,criterio> &M);

    /**
     * @brief Operador igual sobrecargado
     * @param M Una referencia a un montón
     * @return Regresa el resultado de la copia
     */
    MontonMin<T, criterio> &operator=(const MontonMin<T, criterio> &M);

    /**
     * @brief Método para agregar un valor al montón
     * @param valor el valor que se va a agregar al montón
     */
    void Agregar(T valor);

    /**
     * @brief Método para eliminar un elemento del montón
     */
    void Eliminar();

    /**
     * @brief Método para obtener el valor mínimo del montón
     * @return el valor mínimo del montón
     */
    int ObtenerMin();

    /**
     * @brief Método para saber si el montón está vacío o no
     * @return Un valor booleano que indica si el montón está vacío o no
     */
    bool EstaVacio();

    /**
     * @brief Método para vaciar el montón
     */
    void Vaciar();

    /**
     * @brief Método para obtener el tamño del montón
     * @return un entero con el valor del tamaño del montón
     */
    int ObtenerTam();

    /**
     * @brief Método para imprimir el montón
     */
    void Imprimir();

private:

    int ultimo;
    int capacidad;
    T * elemento;

    /**
     * @brief Método para redimensionar el arreglo
     */
    void Redimensionar();

    /**
     * @brief Método para empujar un elemento hacia arriba
     * @param indice El índice desde donde se va a empujar el elemento
     */
    void EmpujarArriba(int indice);

    /**
     * @brief Método para empujar un elemento hacia abajo
     * @param indice El índice desde donde se va a empujar el elemento, que será 0 por default
     *
     */
     void EmpujarAbajo(int indice = 0);

     /**
      *
      * @param a referencia del elemento a a intercambiar
      * @param b referencia del elemento b a intercambiar
      */
     void intercambia(T &a, T &b);


};


//********************************************************************************************************************+*

template<typename T, bool (*criterio)(T, T)>
MontonMin<T, criterio>::MontonMin(): ultimo(-1), capacidad(0), elemento(NULL) {

}

template<typename T, bool (*criterio)(T, T) >
MontonMin<T, criterio>::~MontonMin() {

    delete[] elemento;

}

template<typename T, bool (*criterio)(T, T) >
MontonMin<T, criterio>::MontonMin(const MontonMin<T,criterio> &M): ultimo(-1), capacidad(0), elemento(NULL) {
    *this = M;
}


template<typename T, bool (*criterio)(T, T) >
MontonMin<T, criterio> &MontonMin<T, criterio>::operator=(const MontonMin<T,criterio> &M) {
    if(this == &M) return *this;

    delete[] elemento;

    capacidad = M.capacidad;
    ultimo = M.ultimo;

    if(!M.estaVacio()){
        elemento = new T[capacidad];
        for(int i = 0 ; i < M.ObtenerTam() ; ++i){
            elemento[i] = M.elemento[i];
        }
    }else elemento = NULL;
    return *this;
}




template<typename T, bool (*criterio)(T, T) >
void MontonMin<T, criterio>::Agregar(T valor) {
    if(capacidad == ObtenerTam()) Redimensionar();
    elemento[++ultimo] = valor;
    EmpujarArriba(ultimo);


}

template<typename T, bool (*criterio)(T, T) >
void MontonMin<T, criterio>::Eliminar() {
    if(EstaVacio()) throw Excepcion("Arbol vacio");
    intercambia(elemento[0], elemento[ultimo]);
    --ultimo;
    EmpujarAbajo();

}

template<typename T, bool (*criterio)(T, T) >
int MontonMin<T, criterio>::ObtenerMin() {
    int min = elemento[0];
    for (int i = 0; i < ObtenerTam(); i++)
    {
        if (min > elemento[i])
            min = elemento[i];
    }
    return min;

}

template<typename T, bool (*criterio)(T, T) >
bool MontonMin<T, criterio>::EstaVacio() {
    return ultimo == -1;
}

template<typename T, bool (*criterio)(T, T) >
void MontonMin<T, criterio>::Vaciar() {
    ultimo = -1;

}


template<typename T, bool (*criterio)(T, T)>
int MontonMin<T, criterio>::ObtenerTam() {
    return ultimo+1;
}

template<typename T, bool (*criterio)(T, T) >
void MontonMin<T, criterio>::Imprimir() {
    for(int i = 0; i < ObtenerTam(); i++){
        cout << "[" << elemento[i] << "], ";
    }
    cout << "\b\b ";

}



//**********************************************************************************************************************
//********************************************* METODOS PRIVADOS *******************************************************
//**********************************************************************************************************************


template<typename T, bool (*criterio)(T, T) >
void MontonMin<T, criterio>::Redimensionar() {
    if(capacidad == 0){
        ++capacidad;
    } else{
        capacidad = pow(2, capacidad)-1;
    }
    T * aux = new T[capacidad];
    for(int i = 0; i < ObtenerTam(); i ++){
        aux[i] = elemento[i];
    }
    delete[] elemento;
    elemento = aux;

}

template<typename T, bool (*criterio)(T, T) >
void MontonMin<T, criterio>::EmpujarArriba(int indice) {
    int padre = (indice - 1) / 2;
    while(indice != 0 && criterio(elemento[indice], elemento[padre])){
        intercambia(elemento[padre], elemento[indice]);
        indice = padre;
        padre = (indice - 1) / 2;
    }

}

template<typename T, bool (*criterio)(T, T)>
void MontonMin<T, criterio>::EmpujarAbajo(int indice) {
    while(indice < ObtenerTam()){
        if(2*indice + 1 >= ObtenerTam() && 2*indice + 2 >= 0){
            return;
        }
        if(2*indice + 1 < ObtenerTam() && 2*indice + 2 >= ObtenerTam()){
            if(!criterio(elemento[indice], elemento[2*indice + 1])){
                intercambia(elemento[indice], elemento[2*indice + 1]);
                indice = 2*indice + 1;
            } else{
                return;
            }
        }  else if(criterio(elemento[2*indice + 1], elemento[2*indice + 2])) {
            intercambia(elemento[indice], elemento[2 * indice + 1]);
            indice = 2 * indice + 1;
        }else{
            intercambia(elemento[indice], elemento[2*indice + 2]);
            indice = 2*indice + 2;
        }
    }
}

template<typename T, bool (*criterio)(T, T) >
void MontonMin<T, criterio>::intercambia(T &a, T &b) {
    T aux = a;
    a = b;
    b = aux;
}


#endif //MONTON_MONTONMIN_H
