//
// Created by Rodrigo Calles on 2020-11-30.
//

#ifndef MONTÓN_EXCEPCION_H
#define MONTÓN_EXCEPCION_H

#include <cstring>

class Excepcion {
public:
    Excepcion(const char *msn){ strcpy(mensaje,msn); }
    const char * quePaso(){ return mensaje; }
private:
    char mensaje[100];
};


#endif //MONTÓN_EXCEPCION_H
