#include <stdio.h>
#include <stdlib.h>

int transform_name(const char *name)
{
    /* WRITE YOUR CODE HERE */
    int count=0,sum=0;
    char character;
    
       while (*(name+count)!='\0') {
    character=*(name + count++);    
    sum+=character * count * count;
    
    }            
    return sum;      
}

int** initialize_storage(int IA_size, int DA_size, int** DA_sizes) {
  int i;
  int** arr;
  
  arr = (int**) calloc(IA_size, sizeof(int*));
  
  for (i = 0; i < IA_size; i++) {
    arr[i] = (int*) calloc(DA_size, sizeof(int));
    
  }
  *DA_sizes = (int*) malloc(IA_size*sizeof(int));
  for (i = 0; i<IA_size; i++){   
      (*DA_sizes)[i]=DA_size;   
  }
  return arr;
}

void print_storage(int** storage, int IA_size, int* DA_sizes)
{
    int i=0,j=0;
    while(i<IA_size){
        printf("%d ->",i);
        j=0;
        while(j<*(DA_sizes+i)){
            printf(" %d",*(*(storage+i)+j));
            j++;
        }
        printf("\n");
        i++;
    }
    
}

void insert(int** storage, int IA_size, const char* name, int* DA_sizes)
{
    
    int module,name_code,i=0,flag=0,j=0;
    name_code=transform_name(name);
    module=(name_code % IA_size); 
    if(name_code!=0){
    
        while(i<*(DA_sizes+module)){
        	if((*(*(storage+module)+i))==0){
        		*(*(storage+module)+i)=name_code;
        		flag=0;
        		break;
        	} else {
        		flag=1;
    		}
        	i++;
    	}
    	
    	if(flag==1){
            (*(DA_sizes+module))*=2;
            storage[module] = (int *) realloc (storage[module], sizeof(int) * (*(DA_sizes+module)));
    		while(j<*(DA_sizes+module)/2){
                *(*(storage+module)+j+(*(DA_sizes+module)/2))=0;    
                j++;
            }
    		i=0;
    		while(i<*(DA_sizes+module)){            /*DA_size 2 ye katlandi*/
    			if((*(*(storage+module)+i))==0){
        		*(*(storage+module)+i)=name_code;
        		break;
    			}
                i++;
    		}
    	}
        
    }   
}

void insert2(int** storage, int IA_size, int name_code, int* DA_sizes)
{

    
    int module,i=0,flag=0,j=0;
    
    module=(name_code % IA_size); 
    
    if(name_code!=0){
        while(i<*(DA_sizes+module)){
        	if((*(*(storage+module)+i))==0){
        		*(*(storage+module)+i)=name_code;
        		flag=0;
        		break;
        	} else {
        		flag=1;
    		}
        	i++;
    	}
    	
    	if(flag==1){
            (*(DA_sizes+module))*=2;
            
            storage[module] = (int *) realloc (storage[module], sizeof(int) * (*(DA_sizes+module)));
    		while(j<*(DA_sizes+module)/2){
                *(*(storage+module)+j+(*(DA_sizes+module)/2))=0;    /*DA_size 2 ye katlandi*/
                j++;
            }
    		i=0;
    		while(i<*(DA_sizes+module)){
    			if((*(*(storage+module)+i))==0){
        		*(*(storage+module)+i)=name_code;
        		break;
    			}
                i++;
    		}
    	}
    }
    /* WRITE YOUR CODE HERE */
}

void fill_new_storage(int** storage, int IA_size, int** new_storage, int* DA_sizes, int** new_DA_sizes) {
    int i,j,numeric_code;
    for (i=0;i<IA_size;i++) {
        for (j=0;j<DA_sizes[i];j++) {  
            numeric_code = storage[i][j];
            insert2(new_storage, IA_size*2, numeric_code, *new_DA_sizes);
        }
    }
    

    
}

void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes)
{
    int i,capacity=0;
    float ratio;
    int *array,**new_storage;
    ratio=(*IA_size)*DA_size*(1.5);
    for(i=0;i<*IA_size;i++){
        capacity+=(*DA_sizes)[i];
    }
    
   if (ratio <= capacity) {
        new_storage=initialize_storage((*IA_size)*2,DA_size,&array);
        fill_new_storage(*storage, *IA_size, new_storage, *DA_sizes, &array);

        for (i=0;i<(*IA_size);i++) {        /*Memory Leak fixed.*/
            free((*storage)[i]);
        }
        free(*storage);
        free(*DA_sizes);
        
        
        *DA_sizes =  array;             /*Updates*/
        *IA_size *= 2;
        *storage = new_storage;
        
        
    }
   
    /* WRITE YOUR CODE HERE */
}

