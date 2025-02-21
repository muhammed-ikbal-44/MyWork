#include <stdio.h>



char aa_control(char aa[]) {

	char protein;
	
	if (aa[0] == 'U') {
	  if (aa[1] == 'U') {
	    if (aa[2] == 'U') protein = 'f';
	    else if (aa[2] == 'C') protein = 'f';
	    else if (aa[2] == 'A' || aa[2] == 'G') protein = 'l';
	  } else if (aa[1] == 'C') {
	    protein = 's';
	  } else if (aa[1] == 'A') {
	    if (aa[2] == 'U' || aa[2] == 'C') protein = 'y';
	    else if (aa[2] == 'A' || aa[2] == 'G') protein = 'X';
	  } else if (aa[1] == 'G') {
	    if (aa[2] == 'U' || aa[2] == 'C') protein = 'c';
	    else if (aa[2] == 'A') protein = 'X';
	    else if (aa[2] == 'G') protein = 'w';
	  }
	}
	
	if (aa[0] == 'C') {
	  if (aa[1] == 'U') {
	   	protein = 'l';
	    } else if (aa[1] == 'C') {
	   	protein = 'p';	
	  } else if (aa[1] == 'A') {
	    if (aa[2] == 'U' || aa[2] == 'C') protein = 'h';
	    else if (aa[2] == 'A' || aa[2] == 'G') protein = 'q';
	  } else if (aa[1] == 'G') {
	    protein = 'r';
	  }
	}
	
	if (aa[0] == 'A') {
	  if (aa[1] == 'U') {
	    if (aa[2] == 'U' || aa[2] == 'C' || aa[2] == 'A') protein = 'i'; 
	    else if (aa[2] == 'G') protein = 'm'; 
	  } else if (aa[1] == 'C') {
	    protein = 't';    
	  } else if (aa[1] == 'A') {
	    if (aa[2] == 'U' || aa[2] == 'C') protein = 'n'; 
	    else if (aa[2] =='G' || aa[2] == 'A') protein = 'k'; 
	  } else if (aa[1] == 'G') {
	    if (aa[2] == 'U') protein = 's'; 
	    else if (aa[2] == 'C') protein ='s'; 
	    else if (aa[2] == 'G' || aa[2]=='A') protein = 'r'; 
	  }
	}
	
	if (aa[0] == 'G') {
	  if (aa[1] == 'U') {
	    protein='v';
	  } else if (aa[1] == 'C') {
	    protein='a'; 
	  } else if (aa[1] == 'A') {
	    if (aa[2] == 'U' || aa[2] == 'C') protein = 'd'; 
	    else if (aa[2] == 'A' || aa[2] == 'G') protein = 'e'; 
	  } else if (aa[1] == 'G') {
	    protein='g'; 
	  }
	}
				
	return protein;	
}




int main() {
	char dna[3001];												
    char nukleotid,aminoacid;
    char temp[4]={'A'};
    int i=0,middle_p=0;
    int intron_1_start,intron_1_end,intron_2_start,intron_2_end,protein_counter_reverse;
	int flag=0,y=0,protein_counter=0,o=0,j=0,a=0,b=0,c=0,flag2=0,flag3=0,ulusal_c=0,flag4=0;
    char protein[2901];
    char converted_dna[3001];
    
    
    while (nukleotid= getchar(),nukleotid!='.') {		/*this part take the nucleotid input*/
        if (nukleotid!=' ' && nukleotid!='\n'){
        	dna[i]=nukleotid;
        	i++;	}
       }
    
    while(dna[j]=='T' || dna[j]=='A' || dna[j]=='G' || dna[j]=='C'){
    	switch (dna[j]){
    		case 'T':
    			converted_dna[j]='A';
    			break;
    		case 'A':
    			converted_dna[j]='U';
    			break;
    		case 'G':							/*converts DNA to RNA*/
    			converted_dna[j]='C';
    			break;
    		case 'C':
    			converted_dna[j]='G';
    			break;
		}
		j++;
	}
    
    while (aminoacid= getchar(),aminoacid!='.') {		/*this part take the aminoacid input*/
        if (aminoacid!=' ' && aminoacid!='\n'){
        	protein[y]=aminoacid;
        	y++;
        	protein_counter++;
		}
       
    }
    
    	

	while(o<protein_counter-1){
		b=0;
		while(b<3){
			temp[b]=converted_dna[c];
			b++;
			c++;
		}
		if(protein[a]==aa_control(temp)){		/* find intron start 1 */
			
			a++;
			
			if(a==protein_counter-1){
				intron_1_start=a*3;
				flag4=1;
				break;

			}
		} else {
			intron_1_start=c-3;
			break;
		}
		o++;
	}


	protein_counter_reverse=protein_counter-1;
	middle_p=intron_1_start/3;
	j=j-4;
	while(1){
		if(flag4){
			intron_2_end=i-7;
			middle_p++;
			break;
		}
 		b=2;
		while(b>=0){
			temp[b]=converted_dna[j];
			b--;							/*count how many proteins there are in the middle exon*/
			j--;
		}			
		if(protein[protein_counter_reverse]==aa_control(temp)){
			protein_counter_reverse--;
			
			middle_p++;
			
			
			
		} else {
			intron_2_end=j+3;
			break;
		}
		
	}
	
	


	c=intron_1_start+1;
	if(protein_counter-middle_p>1){
		while(c<3010){
			b=0;
			while(b<3){
				temp[b]=converted_dna[c];
				b++;
				c++;
			}
			if(protein[a]==aa_control(temp)){	
					b=0;
					while(b<3){
						temp[b]=converted_dna[c];
						b++;
						c++;
					}
					if(protein[a+1]==aa_control(temp)){
						intron_1_end=c;
						intron_1_end=intron_1_end-7;	
						intron_2_start=intron_1_end+(protein_counter-middle_p)*3+1;	
						break;
					} else {
						
						c=c-5;
					}
					
			} else { 
				
					c=c-2;
			}
		}
	} else if(protein_counter-middle_p==1){
		while(c<3010){
				b=0;
				while(b<3){
					temp[b]=converted_dna[c];
					b++;
					c++;
				}
			if(protein[a]==aa_control(temp)){
					intron_1_end=c;
					intron_1_end=intron_1_end-4;
					intron_2_start=intron_1_end+(protein_counter-middle_p)*3+1;
					break;
				} else {
					c=c-2;
				}
		}
	} else {
		intron_1_start=intron_1_start-3;
		a--;
		c=intron_1_start+1;
		ulusal_c=c;
		while(c<i-4-2*(i-intron_2_end-1)/3){
				b=0;
				while(b<3){
					temp[b]=converted_dna[c];
					b++;
					c++;
				}
			if(protein[a]==aa_control(temp)){
					intron_1_end=c;
					intron_1_end=intron_1_end-4;
					middle_p--;
					intron_2_start=intron_1_end+(protein_counter-middle_p)*3+1;
					flag3=1;
					break;
				} else {
					c=c-2;
				}
		}		
		if(flag3==0){
			c=intron_2_end+2;	
			intron_1_start=intron_1_start+3;
			intron_2_end=intron_2_end+3;
			a=protein_counter-a-1;
			while(c<3010  && c>-10){
					b=2;
					while(b>=0){
						temp[b]=converted_dna[c];
						b--;
						c--;
					} 
					if(protein[a]==aa_control(temp)){
						intron_2_start=c+4;
						intron_1_end=c;

						break;
					} else {
						c=c+2;
					}	
			}			
	
		}
	}
	
	
	
	
	
	y=i;
	i=0;
	a=0;
	while(1){
		
		
		if(i==intron_1_start){
			i=intron_1_end+1;
		} else if(i==intron_2_start) {
			i=intron_2_end+1;
		}
		
		b=0;
		while(b<3){
			temp[b]=converted_dna[i];
			b++;							
			i++;
		} 
		
		if(aa_control(temp)==protein[a]){
			a++;
			
			flag = 1;
		} else if(aa_control(temp)=='X'){
			flag=1;
			break;

		}else {
			
			flag = 0;
			break;
		}


	}
	
	y--;
	b=2;
	while(b>=0){
		temp[b]=converted_dna[y];		
		b--;
		y--;
	}
	if(intron_1_end-intron_1_start<0 || intron_2_end-intron_2_start<0){
		flag=0;
	}
	
	if(c<3001 && aa_control(temp)=='X' ){
		if(flag==1 && flag2!=1){
			printf("%d ",intron_1_start);
			printf("%d ",intron_1_end);
			printf("%d ",intron_2_start);
			printf("%d",intron_2_end);
		} else {
			printf("NONE");
		}

	} else {
		printf("NONE");
	}

	
	return 0;
}