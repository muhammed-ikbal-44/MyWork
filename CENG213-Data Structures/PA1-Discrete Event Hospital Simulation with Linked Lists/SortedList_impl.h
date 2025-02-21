#ifndef SORTED_LIST_IMPL_H
#define SORTED_LIST_IMPL_H

template<class T>
SortedListNode<T>::SortedListNode(T* itemIn,
                                  SortedListNode* nextNodeIn,
                                  SortedListNode* prevNodeIn)
    : item(itemIn)
    , next(nextNodeIn)
    , prev(prevNodeIn)
{}

template<class T>
SortedList<T>::SortedList()
    : head(NULL)
    , back(NULL)
{}

template<class T>
SortedList<T>::SortedList(const SortedList& other)
    : head(NULL)
    , back(NULL)
{   
    
    if(other.head!=NULL){
        SortedListNode<T> *curr;
        SortedListNode<T> *othcurr = other.head;
        SortedListNode<T> *prevpointer = NULL;
        int flag=0;
        while (othcurr !=NULL) {
            T *val=new T(*othcurr->item);
            curr = new SortedListNode<T>(val, NULL, prevpointer);
            if(flag== 0){   //ilk kez girildiginde flag 0 olacagi icin ilk eleman
                head= curr;
            } else {
                prevpointer->next=curr;
            }
            prevpointer= curr;
            back= curr;                  
            othcurr= othcurr->next;
            flag=1;
        }
         
        // TODO: Implement
        }
}

template<class T>
SortedList<T>& SortedList<T>::operator=(const SortedList& other)
{
    // TODO: Implement
    if(this!=&other ){
        SortedListNode<T> *curr=head;
        while (curr != NULL) {                          
                SortedListNode<T>* indc = curr;         //destructurla aynı zaten
                curr = curr->next;
                delete indc->item;
                delete indc;
        }
        back=NULL; 
        head=NULL;
        
        if( other.head!=NULL){
            
            SortedListNode<T> *othcurr=other.head;
            
            SortedListNode<T> *prevpointer=NULL;
            
             //tamamen sifirlama.
                
                
            int flag=0;
            while (othcurr !=NULL) {
                T *val=new T(*othcurr->item);
                curr = new SortedListNode<T>(val, NULL, prevpointer);
                if(flag== 0){ //ilk kez girildiginde flag 0 olacagi icin ilk eleman
                    head= curr;
                } else {
                    prevpointer->next=curr;
                }
                prevpointer= curr;
                back= curr;                  
                othcurr= othcurr->next;
                flag=1;
            }
        }
        
    }
    return *this;
    
}
template<class T>
SortedList<T>::~SortedList()
{
    SortedListNode<T> *curr = head;
        while (curr!= NULL) {
            SortedListNode<T> *indc =curr;
            curr =curr->next;
            delete indc->item;
            delete indc; 
        }
        back=NULL; head=NULL; //tamamen sifirlama.

    // TODO: Implement
}

template<class T>
void SortedList<T>::InsertItem(T* i)
{
    SortedListNode<T> *curr=head;
    SortedListNode<T> *prevpointer=NULL;
    SortedListNode<T> *newnode = new SortedListNode<T>(i,NULL,NULL);
    int flag=0;
    if(head !=NULL){
        
        while(curr!=NULL){
            if(*curr->item<*i || *curr->item==*i){ //aradigimiz elamani bulma, esitse veya büyükse 
                prevpointer =curr;                //aradigimiz bosluk orasidir, 
                curr=curr->next;                 //nnormalde esitligi eklememistim ama hata verdi
                flag=1;                         //mantigini anlamadim
            } else {
                break;
            }
        }
        
        //bir kere bile flaga girmediyse en küçük elemandır
        if(flag==0){
            newnode->next=head;
            head->prev=newnode;
            head=newnode;
        } else if(curr==NULL){   //direk en sonda
            prevpointer->next= newnode;
            newnode->prev= prevpointer;
            back= newnode;
        }else{          //arada
            newnode->prev= prevpointer;
            newnode->next= curr;
            prevpointer->next= newnode;
            curr->prev= newnode;
        }
        
    }else {
        
        head=newnode;
        back=newnode; 
        curr=head;//liste boşsa herşeyi noda ata
    }
    



    
    // TODO: Implement
}


template<class T>
void SortedList<T>::InsertItemPrior(T* i)
{
     SortedListNode<T> *curr=head;
    SortedListNode<T> *prevpointer=NULL;
    SortedListNode<T> *newnode = new SortedListNode<T>(i,NULL,NULL);
    int flag=0;
    if(head !=NULL){
        
        while(curr!=NULL){
            if(*curr->item<*i ){ //aradigimiz elamani bulma, esitse veya büyükse 
                prevpointer =curr;                //aradigimiz bosluk orasidir, 
                curr=curr->next;                 //nnormalde esitligi eklememistim ama hata verdi
                flag=1;                         //mantigini anlamadim
            } else {
                break;
            }
        }
            
            
            
            
            
            
            
        //bir kere bile flaga girmediyse en küçük elemandır
        if(flag==0){
            newnode->next=head;
            head->prev=newnode;
            head=newnode;
        } else if(curr==NULL){   //direk en sonda
            prevpointer->next= newnode;
            newnode->prev= prevpointer;
            back= newnode;
        }else           {          //arada
            newnode->prev= prevpointer;
            newnode->next= curr;
            prevpointer->next= newnode;
            curr->prev= newnode;
        }
        
    }else {
        
        head=newnode;
        back=newnode; 
        curr=head;//liste boşsa herşeyi noda ata
    }
    // TODO: Implement
}
template<class T>
T* SortedList<T>::RemoveFirstItem()
{
    if (head== NULL) {return NULL; } else {
        SortedListNode<T> *curr= head;
        T* val= curr->item;  

        head= head->next;  
        if(head==NULL){
            back=NULL;
        } else{
            head->prev=NULL;}//tek eleman varsa liste bos olcak
        delete curr;  
        return val;  
    }
}

template<class T>
T* SortedList<T>::RemoveFirstItem(int priority)
{
    // TODO: Implement
    if(head==NULL){
    return NULL;
        
    }   else {
        SortedListNode<T> *curr=head;
       
        int flag=0;
        while(curr!=NULL){
            if( *curr->item==priority){
                flag=1;
                T* val= curr->item; 
                if(curr==head){//ilk elean
                    head= head->next;  
                    head->prev=NULL; 
                } else if(curr==back){
                    back = back->prev;  
                    back->next = NULL;
                } else {
                    curr->prev->next=curr->next;
                    curr->next->prev=curr->prev;
                }
                delete curr;
                return val;
            } 
            
            
            curr=curr->next;
            
            
        }
        if(flag==0){ //aradigimiz deger yoksa bura
            return NULL;
        }
    }
}

template<class T>
T* SortedList<T>::RemoveLastItem(int priority)
{
    // TODO: Implement
    // TODO: Implement
    if(head==NULL){return NULL;}   else {
        SortedListNode<T> *curr=back;       //headleri back'e
                                            //prevleri next'e
        int flag=0;                         //nextleri prev'e çevirdim direk çalıştı :D
        while(curr!=NULL){
            if( *curr->item==priority){
                flag=1;
                T* val= curr->item; 
                if(curr==back){//ilk elean
                    back= back->prev;  
                    back->next=NULL; 
                } else if(curr==head){
                    head = head->next;  
                    head->prev = NULL;
                } else {
                    curr->next->prev=curr->prev;
                    curr->prev->next=curr->next;
                }
                delete curr;
                return val;
            } 
            
            
            curr=curr->prev;
            
            
        }
        if(flag==0){ //aradigimiz deger yoksa bura
            return NULL;
        }
    }
    
}

template<class T>
const T* SortedList<T>::FirstItem() const
{
    return (head) ? head->item : NULL;
}

template<class T>
const T* SortedList<T>::LastItem() const
{
    return (back) ? back->item : NULL;
}

template<class T>
bool SortedList<T>::IsEmpty() const
{
    return head == NULL;
}






template<class T>
void SortedList<T>::ChangePriorityOf(int priority, int newPriority) {
    if (head==NULL || newPriority==priority) {return;}
    bool greater=0;
    
    SortedListNode<T>* curr;
    if(priority>newPriority){
        greater=1;
        curr=head;
    }else{curr=back;}
    while (curr != NULL) {
        SortedListNode<T>* newnode;
        if(greater){
            newnode=curr->next;
        } else {
            newnode=curr->prev;
        }
        

        if (curr->item->getPriority()==priority) {
    
            curr->item->setPriority(newPriority);

            if (curr==head) {
                head=curr->next;    
                head->prev = NULL;
            } else if (curr == back) {
                back = curr->prev;
                back->next = NULL;
            } else {
                if (curr->prev!=NULL){
                    curr->prev->next = curr->next;      
                }
                if (curr->next!=NULL){
                     curr->next->prev = curr->prev;
                }
            }
            
            if(greater)
            {
            InsertItem(curr->item);         //basa ekle
            } else {
                InsertItemPrior(curr->item);  //sona ekle
            }
            delete curr;
        }
        
        
        
        
        curr = newnode;
    }
}


template<class T>
void SortedList<T>::Split(SortedList& listLeft,
                          SortedList& listRight,
                          int priority)
{
    assert(listLeft.head == NULL);
    assert(listRight.head == NULL);
    
    
    
    
        while (head!=NULL)       {  
        T *val=RemoveFirstItem();
        if (val->getPriority()<priority) { //direk büyk olanı al insert et, küçük olanı öbürüne 
                                        //insert et, asıl listeden de removla böylece olur
            listLeft.InsertItem(val);
        } else {
            listRight.InsertItem(val);
        }
    }
        
    // TODO: Implement
}

template<class T>
SortedList<T> SortedList<T>::Merge(const SortedList& list0,
                                   const SortedList& list1)
{
   
    
    SortedList<T> List0= list0;
    SortedList<T> List1=list1;
    SortedList<T> siralilist;
    while(List0.head != NULL) {
        T *val= List0.RemoveFirstItem();
        siralilist.InsertItem(val);
    }

   
    while(List1.head != NULL){
        T *val=List1.RemoveFirstItem();
        siralilist.InsertItem(val);
    }

    return siralilist;
    
   
   //return SortedList<T>();
}

#endif