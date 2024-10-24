#Stack Yapısı
def create_stack():
    """creates an empty stack"""
    return []

def push(item, stack):
    """adds item to the top of the stack"""
    stack.append(item)

def pop(stack):
    """removes and return the item at the top of the stack"""
    return stack.pop()

def top(stack):
    """
    returns the value of the item at the top of the stack 
    without removing it"""
    return stack[-1]

def is_empty(stack):
    """checks whether stack is empty"""
    return stack==[]

##Queue yapısı
def create_queue():
    """create empty queue"""
    return []

def enqueue(item,queue):
    """adds item to the end (back) of the queue"""
    queue.append(item)

def dequeue(queue):
    """removes and return the item at the front item without removing it"""
    return queue.pop(0)

def front(queue):
    return queue[0]

def is_empty(queue):
    """checks"""
    return queue==[]

def tekrar_edenleri_temizle(liste):
    tekrar_edenler = set()
    a = []

    for i in liste:
        if i in tekrar_edenler:
            continue
        else:
            a.append(i)
            tekrar_edenler.add(i)

    return a


def unnester(T, pname):
    if T[0]==pname:
        return []#Buraya bak
    
    elif pname in T:
       
        return T
    
    else:
        for i in range(len(T)):
            if pname in T[i] and type(T[i])==list:
                return T
            
            elif type(T[i])==list and pname not in T[i]:
                if unnester(T[i],pname)!=None:
                    return unnester(T[i],pname)
                
##Bu kısımlar Brother için                    

def brothers(T,pname):

    brothers_list=[]
    unnested_list=unnester(T,pname)
    if unnested_list==[]:
        return []
    elif pname in unnested_list:
        for i in range(1,len(unnested_list)):
            if type(unnested_list[i])==list:
                
                brothers_list.append(unnested_list[i][0])
            else:
                
                brothers_list.append(unnested_list[i])
    else:
        for e in range(1,len(unnested_list)):
            if type(unnested_list[e])==list:
                
                if pname==unnested_list[e][0]:
                    
                    for a in range(1,len(unnested_list)):
                        if type(unnested_list[a])==str:
                            
                            brothers_list.append(unnested_list[a])
                        else:
                            brothers_list.append(unnested_list[a][0])
                else:
                    if pname in unnested_list[e]:
                        for h in range(1,len(unnested_list[e])):
                            if type(unnested_list[e][h])==list:
                                brothers_list.append(unnested_list[e][h][0])
                            else:
                                brothers_list.append(unnested_list[e][h])
    brothers_list.remove(pname)
    brothers_list = [name for name in brothers_list if not name[0].isupper()]
    
    return brothers_list

def sisters(T,pname):

    sisters_list=[]
    unnested_list=unnester(T,pname)
    if unnested_list==[]:
        return []
    elif pname in unnested_list:
        for i in range(1,len(unnested_list)):
            if type(unnested_list[i])==list:
                
                sisters_list.append(unnested_list[i][0])
            else:
                
                sisters_list.append(unnested_list[i])
    else:
        for e in range(1,len(unnested_list)):
            if type(unnested_list[e])==list:
                
                if pname==unnested_list[e][0]:
                    
                    for a in range(1,len(unnested_list)):
                        if type(unnested_list[a])==str:
                            
                            sisters_list.append(unnested_list[a])
                        else:
                            sisters_list.append(unnested_list[a][0])
                else:
                    if pname in unnested_list[e]:
                        for h in range(1,len(unnested_list[e])):
                            if type(unnested_list[e][h])==list:
                                sisters_list.append(unnested_list[e][h][0])
                            else:
                                sisters_list.append(unnested_list[e][h])
    sisters_list.remove(pname)
    sisters_list = [name for name in sisters_list if not name[0].islower()]
    
    return sisters_list

def siblings(T,pname):


    siblings_list=[]
    unnested_list=unnester(T,pname)
    if unnested_list==[]:
        return []
    elif pname in unnested_list:
        for i in range(1,len(unnested_list)):
            if type(unnested_list[i])==list:
                
                siblings_list.append(unnested_list[i][0])
            else:
                
                siblings_list.append(unnested_list[i])
    else:
        for e in range(1,len(unnested_list)):
            if type(unnested_list[e])==list:
                
                if pname==unnested_list[e][0]:
                    
                    for a in range(1,len(unnested_list)):
                        if type(unnested_list[a])==str:
                            
                            siblings_list.append(unnested_list[a])
                        else:
                            siblings_list.append(unnested_list[a][0])
                else:
                    if pname in unnested_list[e]:
                        for h in range(1,len(unnested_list[e])):
                            if type(unnested_list[e][h])==list:
                                siblings_list.append(unnested_list[e][h][0])
                            else:
                                siblings_list.append(unnested_list[e][h])
    siblings_list.remove(pname)
    
    
    return siblings_list       
    
def uncles(T,pname):
    unnested_list=unnester(T,pname)   
    if unnested_list==[]:
        return []
    if pname in unnested_list:
        return brothers(T,unnested_list[0])
    else:
        for i in range(1,len(unnested_list)):
            if type(unnested_list[i])==list  and unnested_list[i][0]==pname:
                return brothers(T,unnested_list[0])
            elif type(unnested_list[i])==list and pname in unnested_list[i]:
                return brothers(T,unnested_list[i][0])
            
def aunts(T,pname):
    unnested_list=unnester(T,pname)   
    if unnested_list==[]:
        return []
    if pname in unnested_list:
        return sisters(T,unnested_list[0])
    else:
        for i in range(1,len(unnested_list)):
            if type(unnested_list[i])==list  and unnested_list[i][0]==pname:
                return sisters(T,unnested_list[0])
            elif type(unnested_list[i])==list and pname in unnested_list[i]:
                return sisters(T,unnested_list[i][0])

def cousins(T,pname):
    cousins_list=[]
    relative_list=aunts(T,pname)+uncles(T,pname)
    for i in range(len(relative_list)):
        unnested_list=unnester(T,relative_list[i])
        if relative_list[i] in unnested_list:
            
            pass
        else:
            for j in range(len(unnested_list)):
                
                if type(unnested_list[j])==list and unnested_list[j][0]==relative_list[i]:
                    for a in range(1,len(unnested_list[j])):
                        if type(unnested_list[j][a])==str:
                            cousins_list.append(unnested_list[j][a])
                        elif type(unnested_list[j][a])==list:
                            cousins_list.append(unnested_list[j][a][0])
                    
    return cousins_list               


            
        
    













