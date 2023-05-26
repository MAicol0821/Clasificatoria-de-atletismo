#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

struct corredor {
    char nombre[20];
    int camisa;
    float tiempo;
    int promedio;
    int total;
    int recorrido;
    corredor* derecha;
    corredor* izquierdo;
};

corredor* Raiz = NULL;
corredor* aux = NULL;
corredor* aux1 = NULL;

int preorden(corredor* aux2) {
    cout << "Numero de camisa: " << aux2->camisa << " "
         << "Nombre del Atleta: " << aux2->nombre << " "
         << "Tiempo: " << aux2->tiempo << endl;

    if (aux2->izquierdo != NULL) {
        preorden(aux2->izquierdo);
    }
    if (aux2->derecha != NULL) {
        preorden(aux2->derecha);
    }
    return 0;
}

int promedio_orden(corredor* aux2) {
    if (aux2 != NULL) {
        promedio_orden(aux2->izquierdo);
        cout << "Numero de camisa: " << aux2->camisa << " "
             << "Nombre del Atleta: " << aux2->nombre << " "
             << "Promedio: " << aux2->promedio << endl;
        promedio_orden(aux2->derecha);
    }
}

corredor* buscarCorredor(corredor* nodo, int camisa) {
    if (nodo == NULL || nodo->camisa == camisa) {
        return nodo;
    }
    if (camisa < nodo->camisa) {
        return buscarCorredor(nodo->izquierdo, camisa);
    } else {
        return buscarCorredor(nodo->derecha, camisa);
    }
}

void Registrart() {
    int camisa;
    cout << "Registrar el número del corredor: ";
    cin >> camisa;
    cout << "\n";
    corredor* corredorEncontrado = buscarCorredor(Raiz, camisa);

    if (corredorEncontrado != NULL) {
        corredorEncontrado->recorrido++;
        cout << "Nombre del atleta: " << corredorEncontrado->nombre << " "
             << "Tiempo incluido: " << corredorEncontrado->tiempo << " "
             << "Última vuelta: " << corredorEncontrado->recorrido << endl;
        cout << "\n";
        cout << "Registre el tiempo de la última vuelta:" << endl;
        cin >> corredorEncontrado->tiempo;
        corredorEncontrado->total += corredorEncontrado->tiempo;
        corredorEncontrado->promedio = corredorEncontrado->total / corredorEncontrado->recorrido;
    } else {
        cout << "No está el atleta en la competencia" << endl;
    }
}


int Posicionar() {
    if (aux->camisa < aux1->camisa) {
        if (aux1->izquierdo != NULL) {
            aux1 = aux1->izquierdo;
            Posicionar();
        } else {
            aux1->izquierdo = aux;
        }
    } else if (aux->camisa > aux1->camisa) {
        if (aux1->derecha != NULL) {
            aux1 = aux1->derecha;
            Posicionar();
        } else {
            aux1->derecha = aux;
        }
    }
    return 0;
}

corredor* rotacionSimpleIzquierda(corredor* nodo) {
    corredor* aux = nodo->izquierdo;
    nodo->izquierdo = aux->derecha;
    aux->derecha = nodo;
    return aux;
}

corredor* rotacionSimpleDerecha(corredor* nodo) {
    corredor* aux = nodo->derecha;
    nodo->derecha = aux->izquierdo;
    aux->izquierdo = nodo;
    return aux;
}

corredor* rotacionDobleIzquierda(corredor* nodo) {
    nodo->izquierdo = rotacionSimpleDerecha(nodo->izquierdo);
    return rotacionSimpleIzquierda(nodo);
}

corredor* rotacionDobleDerecha(corredor* nodo) {
    nodo->derecha = rotacionSimpleIzquierda(nodo->derecha);
    return rotacionSimpleDerecha(nodo);
}

int altura(corredor* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    int alturaIzquierda = altura(nodo->izquierdo);
    int alturaDerecha = altura(nodo->derecha);
    return (alturaIzquierda > alturaDerecha) ? alturaIzquierda + 1 : alturaDerecha + 1;
}

int factorEquilibrio(corredor* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izquierdo) - altura(nodo->derecha);
}

corredor* balancearArbol(corredor* nodo) {
    int factor = factorEquilibrio(nodo);
    if (factor > 1) {
        if (factorEquilibrio(nodo->izquierdo) > 0) {
            nodo = rotacionSimpleIzquierda(nodo);
        } else {
            nodo = rotacionDobleIzquierda(nodo);
        }
    } else if (factor < -1) {
        if (factorEquilibrio(nodo->derecha) < 0) {
            nodo = rotacionSimpleDerecha(nodo);
        } else {
            nodo = rotacionDobleDerecha(nodo);
        }
    }
    return nodo;
}

corredor* insertarNodo(corredor* nodo, corredor* nuevoNodo) {
    if (nodo == NULL) {
        return nuevoNodo;
    }
    if (nuevoNodo->camisa < nodo->camisa) {
        nodo->izquierdo = insertarNodo(nodo->izquierdo, nuevoNodo);
    } else if (nuevoNodo->camisa > nodo->camisa) {
        nodo->derecha = insertarNodo(nodo->derecha, nuevoNodo);
    }
    return balancearArbol(nodo);
}

int Registro() {
    aux = (struct corredor*)malloc(sizeof(struct corredor));
    cout << "Ingrese el nombre del atleta: " << endl;
    cin >> aux->nombre;
    cout << "Ingresar el número del atleta: " << endl;
    cin >> aux->camisa;
    aux->derecha = NULL;
    aux->tiempo = 0;
    aux->recorrido = 0;
    aux->izquierdo = NULL;

    if (Raiz == NULL) {
        Raiz = aux;
    } else {
        Raiz = insertarNodo(Raiz, aux);
    }

    return 0;
}

int main() {
    int datos = 0;
    do {
        cout << "Menu" << endl;
        cout << "1. Registrar Atleta" << endl;
        cout << "2. Registrar tiempo" << endl;
        cout << "3. Mostrar atleta" << endl;
        cout << "4. Promedio del atleta" << endl;
        cout << "5. Salir" << endl;
        cin >> datos;

        switch (datos) {
            case 1:
                cout << "\tRegistro" << endl;
                Registro();
                break;
            case 2:
                Registrart();
                break;
            case 3:
                cout << "\tMostrar atleta" << endl;
                preorden(Raiz);
                break;
            case 4:
                cout << "\tPromedio" << endl;
                promedio_orden(Raiz);
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while (datos != 5);

    return 0;
}

