  #ifndef FCFS_LIST_IMPL_H
#define FCFS_LIST_IMPL_H

template<class T>
FCFSNode<T>:: FCFSNode(const T& t, FCFSNode* node)
    : item(t)
    , next(node)
{}

// ============================ //
template<class T>
FCFSList<T>::FCFSList()
    : head(NULL)
{
    // Using a dummy node
    head = new FCFSNode<T>(T());
}

template<class T>
FCFSList<T>::FCFSList(const FCFSList& other)
{
    head = new FCFSNode<T>(T());
    FCFSNode<T> *othcurr=other.head->next;   
    FCFSNode<T> *curr=head;  //Node tanımlamalari
                     
                     
    while(othcurr!=NULL){
    
    curr->next=new FCFSNode<T>(othcurr->item);
    curr=curr->next;    //gecisler
    othcurr=othcurr->next;
   }
   
    // TODO: Implement
}

template<class T>
FCFSList<T>& FCFSList<T>::operator=(const FCFSList& other)
{
    // TODO: Implement
    if(this !=&other){ //aynısıysa direk geçir
        
        
        FCFSNode<T> *othcurr=other.head->next;
        FCFSNode<T> *curr=head->next;  //Node tanımlamalari
        while(curr !=NULL){
            FCFSNode<T> *indc=curr;
            curr=curr->next;
            delete indc;
            
        }
        head->next=NULL;
        curr=head;
       
        
        while(othcurr!=NULL){
        
        curr->next=new FCFSNode<T>(othcurr->item);
        curr=curr->next;    //gecisler
        othcurr=othcurr->next;
        }
    }
   

    return *this;
}  

template<class T>
FCFSList<T>::~FCFSList()
{   
    
    FCFSNode<T> *curr=head;  //Node tanımlamalari
    while(curr->next!=NULL){
        FCFSNode<T> *indc=curr;
        curr=curr->next;
        delete indc;
        
    }
    delete curr;
    
    
    // TODO: Implement
}

template<class T>
void FCFSList<T>::Enqueue(const T& item)
{
    
    FCFSNode<T> *curr=head;  //Node tanımlamalari
    while (curr->next!=NULL)
    {
        curr=curr->next;
    }
    curr->next=new FCFSNode<T>(item);
    
    // TODO: Implement
}

template<class T>
T FCFSList<T>::Dequeue()
{
    
   FCFSNode<T> *curr = head->next; 
    if (curr== NULL) {
        return T(); 
    } else {
        T val = curr->item; // degeri tut
        head->next = curr->next; 
        delete curr; //memoryleak olmaması için ŞART!
        return val; 
    }

    
}

#endif