#include <iostream>
#include "cstdlib"
#include <ctime>
#include "MontonMin.h"
#include "MontonMax.h"

using namespace std;

int main() {

    try {
        cout << "MONT\242 MIN" << endl;
        srand (time(NULL));

        cout << "Agregando valores al mont\242n..." << endl;
        MontonMin<int> montonMin;
        for(int i = 0; i < 10; ++i){
            montonMin.Agregar(1 + rand() % 100 );
        }
        montonMin.Imprimir();
        int x;
        cout << endl << "Elija la cantidad de elementos que desea eliminar: " << endl;
        cin >> x;
        if (x <= montonMin.ObtenerTam()){
            for(int i = 0; i < x; i++){
                cout  << endl << "Eliminando elemento: " << endl;
                montonMin.Eliminar();
                cout << endl;
                montonMin.Imprimir();
            }
        } else{
            cout << endl << "No se puede eliminar mas elementos de los que hay en el mont\242n...";
        }

        cout << endl << "El menor valor en el mont\242n es: " << montonMin.ObtenerMin() << endl;


    }catch(Excepcion &exc){
        cout << "Error: " << exc.quePaso() << endl;
    }catch(bad_alloc &exc) {
        cout << "Error en la asignaci\242n de memoria" << endl;
    }

    try {
        cout << "MONT\242 MAX" << endl;
        srand (time(NULL));

        cout << "Agregando valores al mont\242n..." << endl;
        MontonMax<int> montonMax;
        for(int i = 0; i < 10; ++i){
            montonMax.Agregar(1 + rand() % 100 );
        }
        montonMax.Imprimir();
        int y;
        cout << endl << "Elija la cantidad de elementos que desea eliminar: " << endl;
        cin >> y;
        if (y <= montonMax.ObtenerTam()){
            for(int i = 0; i < y; i++){
                cout  << endl << "Eliminando elemento: " << endl;
                montonMax.Eliminar();
                cout << endl;
                montonMax.Imprimir();
            }
        } else{
            cout << endl << "No se puede eliminar mas elementos de los que hay en el mont\242n...";
        }

        cout << endl << "El menor valor en el mont\242n es: " << montonMax.ObtenerMin() << endl;


    }catch(Excepcion &exc){
        cout << "Error: " << exc.quePaso() << endl;
    }catch(bad_alloc &exc) {
        cout << "Error en la asignaci\242n de memoria" << endl;
    }

    system("pause");
    return 0;
}