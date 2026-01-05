#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;
    }

    // Número de entradas
    int entries() override {
        return tree->size();
    }

    // Insertar
    void insert(std::string key, V value) override {
        tree->insert(TableEntry<V>(key, value));
    }

    // Buscar
    V search(std::string key) override {
        TableEntry<V> result = tree->search(TableEntry<V>(key));
        return result.value;
    }

    // Eliminar
    V remove(std::string key) override {
        TableEntry<V> entry = tree->search(TableEntry<V>(key));
        V value = entry.value;
        tree->remove(TableEntry<V>(key));
        return value;
    }

    // Operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Operador <<
    friend std::ostream& operator<<(std::ostream &out,
                                    const BSTreeDict<V> &bs) {
        out << *bs.tree;
        return out;
    }
};

#endif

