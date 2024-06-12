#ifndef EDDFINAL_PILA_H
#define EDDFINAL_PILA_H

#include <stdexcept>

template <typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
    };

    Nodo* cima;
    int tamanio;

public:
    Pila() : cima(nullptr), tamanio(0) {}

    ~Pila() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() const {
        return cima == nullptr;
    }

    int size() const {
        return tamanio;
    }

    void push(const T& dato) {
        Nodo* nuevoNodo = new Nodo{dato, cima};
        cima = nuevoNodo;
        tamanio++;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("La pila está vacía");
        }

        Nodo* temp = cima;
        cima = cima->siguiente;
        delete temp;
        tamanio--;
    }

    T& top() {
        if (empty()) {
            throw std::runtime_error("La pila está vacía");
        }
        return cima->dato;
    }

    const T& top() const {
        if (empty()) {
            throw std::runtime_error("La pila está vacía");
        }
        return cima->dato;
    }
};

#endif // EDDFINAL_PILA_H
