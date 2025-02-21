#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "DSWTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    V &operator[](const K &key) const;

    void put(const K &key, const V &value);

    bool containsKey(const K &key); // Declaration of the new method

    bool deletekey(const K &key); // Declaration of the new method

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

    int size();

    void balance();

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    bool operator==(const KeyValuePair<K, V>& other) const;

private: // DO NOT CHANGE THIS PART.
    DSWTree<KeyValuePair<K, V> > stree;

};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    /* TODO */
    stree.removeAllNodes();
    
}




template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    /* TODO */
    
    try {
        KeyValuePair<K, V> element(key);
        const KeyValuePair<K, V>& element2 = stree.get(element); 
        return element2.getValue();
    }
    catch(NoSuchItemException& e) {
        throw NoSuchItemException();
    }
    
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    /* TODO */
    try{
    KeyValuePair<K, V> element(key);    
    return stree.getCeiling(element);}
    catch(NoSuchItemException& e){
        throw NoSuchItemException();
    }
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    /* TODO */
    try{
    return stree.getMin();}
    catch(NoSuchItemException& e){
        throw NoSuchItemException();
    }
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    /* TODO */
    try{
    return stree.getMax();}
    catch(NoSuchItemException& e){
        throw NoSuchItemException();
    }
}

template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const {
    /* TODO */
    
    std::vector<KeyValuePair<K, V> > vect;
    KeyValuePair<K, V> begining(fromKey);
   
    
    
    while(fromKey != toKey){
        
        vect.push_back(stree.get(fromKey));
        fromKey=stree.getNext(KeyValuePair<K,V>(fromKey)).getKey();
       
    }
    
    vect.push_back(stree.get(toKey));
    
   
    return vect;
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# DSWTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

template<class K, class V>
void TreeMap<K, V>::put(const K &key, const V &value) {
    /* TODO */
    KeyValuePair<K,V> element(key,value);
    if(containsKey(key)){
        KeyValuePair<K,V> result=stree.get(element);
        result.setValue(value);
    }else{
        stree.insert(element);
    }
    
}

template<class K, class V>
V& TreeMap<K, V>::operator[](const K &key) const {
    /* TODO */
    return const_cast<V&>( get(key));
}

template<class K, class V>
bool TreeMap<K, V>::deletekey(const K &key) {
/* TODO */
    
        
   /* KeyValuePair<K, V> element(key);
    const KeyValuePair<K, V>& element2=get[element];
    return stree.remove(element2);*/
        
    return stree.remove(KeyValuePair<K,V>(key));    
     
    
       
        
        
    
    
}

template<class K, class V>
bool TreeMap<K,V>::operator==(const KeyValuePair<K, V>& other) const {
        return this->key == other.key; 
}
template<class K, class V>
bool TreeMap<K, V>::containsKey(const K &key) {
    /*
    try{
    KeyValuePair<K, V> victim(key);
    const KeyValuePair<K, V>& victim2 = stree.getFloor(victim);
    if(victim2==victim){
        return true;
    }else{
        return false;
    }}
    catch(NoSuchItemException& e){
        return false;
    }*/
    
    /* TODO */
    
   try {
       KeyValuePair<K, V> victim(key);
       const KeyValuePair<K, V>& victim2 = stree.get(victim);
       return true;
   }
   catch(NoSuchItemException& e) {
       return false;
   }
    
}

template<class K, class V>
void TreeMap<K, V>::balance() {
    /* TODO */
    stree.balance();
}

#endif //TREEMAP_H
