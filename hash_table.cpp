#include "../headers/hash_table.h"
#include <iostream>
#include <string.h>

HashTable::HashTable() {
    // выделение памяти, инициализация
    mem_size = 8;
    chain_tops = new ChainNode*[mem_size];
    for(int i = 0; i < mem_size; i++) {
        chain_tops[i] = nullptr;
    }
    count = 0;
}
HashTable::~HashTable() {
    // прибираем за собой
    for(int i = 0; i < mem_size; i++)
        if(chain_tops[i] != nullptr)
            delete chain_tops[i];
    delete[] chain_tops;
}

int HashTable::hash_func(FruitName fr_name) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for(; i < strlen(fr_name); i++) {
        sum += fr_name[i];
    }
    return sum % mem_size; // значение точно будет между 0 и memsize
}

void HashTable::add(FruitName fr_name, int fr_count) {
    int index = hash_func(fr_name); // вычислили индекс в массиве
    if(chain_tops[index] != nullptr) {
        /* если список таким индексом уже есть, то
        создаем новый узел и делаем его верхним */
        ChainNode* newNode = new ChainNode(fr_name, fr_count);
        newNode->next = chain_tops[index];
        chain_tops[index] = newNode;
    } else {
        // если нет списка, задаем его верхний узел
        chain_tops[index] = new ChainNode(fr_name, fr_count);
    }
    count++;
}

int HashTable::find(FruitName fr_name) {
    int index = hash_func(fr_name);
    ChainNode* node = chain_tops[index];
    while(node != nullptr) {
        if(! strcmp(node->fruit_name, fr_name)) {
            return index;
        } else {
            node = node->next;
        }
    }
    return -1;
}

void HashTable::del(FruitName fr_name) {
    int index = hash_func(fr_name);
    ChainNode* node = chain_tops[index];
    if(! strcmp(node->fruit_name, fr_name)) {
        ChainNode *del_node = node;
        chain_tops[index] = node->next;
        del_node->next = nullptr;
        delete del_node;
        count--;
    } else {
        while(node->next != nullptr) {
            if(! strcmp(node->next->fruit_name, fr_name)) {
                ChainNode *del_node = node->next;
                node->next = del_node->next;
                del_node->next = nullptr;
                delete del_node;
                count--;
                return;
            } else {
                node = node->next;
            }
        }
    }
}

void HashTable::print() {
    if(chain_tops != nullptr) {
        std::cout << std::endl;
        for(int i = 0; i < mem_size; i++) {
            ChainNode* node = chain_tops[i];
            if(node != nullptr) {
                std::cout << node->fruit_name << "\t";
                while(node->next != nullptr) {
                    std::cout << node->next->fruit_name << "\t";
                    node = node->next;
                }
            }
            std::cout << std::endl;
        }
    }
}