#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <ostream>
#include <stdexcept>

#include "Dict.h"
#include "TableEntry.h"
#include "../../P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;      // número de elementos
    int max;    // número de cubetas
    ListLinked<TableEntry<V>>* table;

    // Función hash
    int h(std::string key) {
        int sum = 0;
        for (int i = 0; i < (int)key.length(); i++) {
            sum += int(key.at(i));
        }
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Número de entradas
    int entries() override {
        return n;
    }

    // Capacidad
    int capacity() {
        return max;
    }

    // Insertar
    void insert(std::string key, V value) override {
        int pos = h(key);
        TableEntry<V> entry(key, value);

        if (table[pos].search(entry) != -1) {
            throw std::runtime_error("Key '" + key + "' already exists!");
        }

        table[pos].insert(0, entry);   // insertar al inicio
        n++;
    }

    // Buscar
    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int idx = table[pos].search(entry);
        if (idx == -1) {
            throw std::runtime_error("Key '" + key + "' not found!");
        }

        return table[pos].get(idx).value;
    }

    // Eliminar
    V remove(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int idx = table[pos].search(entry);
        if (idx == -1) {
            throw std::runtime_error("Key '" + key + "' not found!");
        }

        V value = table[pos].remove(idx).value;
        n--;
        return value;
    }

    // Operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Operador <<
    friend std::ostream& operator<<(std::ostream& out,
                                    const HashTable<V>& ht) {

        out << "HashTable [entries: " << ht.n
            << ", capacity: " << ht.max << "]\n";
        out << "==============\n\n";

        for (int i = 0; i < ht.max; i++) {
            out << "== Cubeta " << i << " ==\n\n";
            out << "List => " << ht.table[i] << "\n\n";
        }

        out << "==============\n";
        return out;
    }
};

#endif

