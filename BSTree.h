#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        // Atributos privados
        int nelem;
        BSNode<T> *root;
        
        // Métodos privados
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                throw std::runtime_error("Elemento no encontrado");
            } else if (n->elem < e) {
                return search(n->right, e);
            } else if (n->elem > e) {
                return search(n->left, e);
            } else {
                return n;
            }
        }
        
        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                nelem++;
                return new BSNode<T>(e);
            } else if (n->elem == e) {
                throw std::runtime_error("Elemento duplicado");
            } else if (n->elem < e) {
                n->right = insert(n->right, e);
            } else {
                n->left = insert(n->left, e);
            }
            return n;
        }
        
        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }
        }
        
        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr) {
                throw std::runtime_error("Elemento no encontrado");
            } else if (n->elem < e) {
                n->right = remove(n->right, e);
            } else if (n->elem > e) {
                n->left = remove(n->left, e);
            } else {
                // Elemento encontrado
                if (n->left != nullptr && n->right != nullptr) {
                    // Nodo con dos hijos: reemplazar por máximo del subárbol izquierdo
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                } else {
                    // Nodo con 0 o 1 hijo
                    BSNode<T>* temp = n;
                    n = (n->left != nullptr) ? n->left : n->right;
                    delete temp;
                    nelem--;
                }
            }
            return n;
        }
        
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw std::runtime_error("Árbol vacío");
            } else if (n->right != nullptr) {
                return max(n->right);
            } else {
                return n->elem;
            }
        }
        
        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                BSNode<T>* temp = n->left;
                delete n;
                nelem--;
                return temp;
            } else {
                n->right = remove_max(n->right);
                return n;
            }
        }
        
        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }
        
    public:
        // Métodos públicos
        
        // Constructor
        BSTree() : nelem(0), root(nullptr) {}
        
        // Tamaño
        int size() const {
            return nelem;
        }
        
        // Búsqueda
        T search(T e) const {
            return search(root, e)->elem;
        }
        
        T operator[](T e) const {
            return search(e);
        }
        
        // Inserción
        void insert(T e) {
            root = insert(root, e);
        }
        
        // Sobrecarga del operador 
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }
        
        // Eliminación
        void remove(T e) {
            root = remove(root, e);
        }
        
        // Destructor
        ~BSTree() {
            delete_cascade(root);
        }
};

#endif
