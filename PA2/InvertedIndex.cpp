#include "InvertedIndex.h"

#include <fstream>
#include <iostream>

InvertedIndex::InvertedIndex() {

}

InvertedIndex::InvertedIndex(const InvertedIndex &obj) {

    this->invertedIndex = obj.invertedIndex; // uses operator= of BST
}

InvertedIndex::~InvertedIndex() {

}

TreeMap<std::string, std::vector<int> >  &InvertedIndex::getInvertedIndex() {

    return invertedIndex;
}


InvertedIndex &InvertedIndex::addDocument(const std::string &documentName, int docid) {
    /* TODO */
    std::ifstream file(documentName.c_str(), std::ifstream::in);
    
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << documentName << std::endl;
        return *this;
    }

    std::string word;
    while (file >> word) {
        // Check if the word is already in the inverted index
        if (invertedIndex.containsKey(word)) {
            /* TODO */
            int size=invertedIndex[word].size();
            int sayac=0;
            
            for(sayac=0;sayac<size;sayac++){
                
                if(invertedIndex[word][sayac]==docid){
                    break;
                }//else nothing
                
            }
            if(sayac==size){
                invertedIndex[word].push_back(docid);
            }
        } else {
            std::vector<int> vect;
            vect.push_back(docid);
            invertedIndex.put(word,vect);
            /* TODO */

        }
    }

    file.close();
    return *this;

}

//Sort fonsyonunu buraya koydum sakın krasitirma
void InvertedIndex::sort(std::vector<int>& vec) {
    int n =vec.size();
    for (int i=0; i < n-1; ++i) {
        int min=i;
        
        for (int j= i+1;j< n; ++j) {
            if (vec[j] < vec[min]) {
            min= j;
    }
        }
        if (min!=i) {
            int temp =vec[min];
            vec[min]=vec[i];
            vec[i] =temp;
        }
}
}

std::vector<int> InvertedIndex::search(const std::string &query) {
    /* TODO */
    std::string trgt;
    std::vector<std::string> vect;
    
    std::vector<int> result;
    
    
    //int vectsize=(int) vect.size();
    int sayac=0;
    
    
    for(int i=0;i<(int)query.size();i++){
        if(query[i]!=' '){
           
            trgt.push_back(query[i]);
        }else{
             vect.push_back(trgt);
            trgt="";
        }
    }
    
    vect.push_back(trgt);
    for(int k=0;k<(int)vect.size();k++){
        
         if(getInvertedIndex().containsKey(vect[k])){
             
            int size3=(int)getInvertedIndex().get(vect[k]).size(); 
            for(int j=0;j<size3;j++){
                
                for(sayac=0;sayac<(int)result.size();sayac++){
                    
                    
                    
                    if(result[sayac]==getInvertedIndex().get(vect[k])[j]){
                        break;
                    }   
                    
                } 
                if(sayac==(int)result.size()){
                    result.push_back(getInvertedIndex().get(vect[k])[j]);
                }
         }
    }
    
    }
    sort(result);
    return result;
}

InvertedIndex & InvertedIndex::printInvertedIndex() const {

    invertedIndex.print();

}

InvertedIndex &InvertedIndex::operator=(const InvertedIndex &rhs) {

    this->invertedIndex = rhs.invertedIndex; // uses operator= of BST

    return *this;
}
