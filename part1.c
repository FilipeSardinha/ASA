#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int position = -1;
int cntScc = 0;
int MScc = 0;

typedef struct destiny{
int _valor;
struct destiny *next;
}destiny;

typedef struct person{
int _d;
int _low;
destiny *first;
}person;

typedef struct stack{
   int value ;
}stack;

void initStack(int n, struct stack *s){
   int i = 0;
   while(i < n){
       s[i].value = -1;
       i++;
   }
}

void pushStack(stack* s , int u,int n){ 
    position++;
    s[position].value = u;	
}

int popStack(stack* s,int n){
    int result;
    if(position >= 0){
        result = s[position].value;
        s[position].value = -1;
        position--;    return result;
    }
return -1;
}

int searchStack(stack* s , int u, int n){
   int i ;
   for (i = 0 ; i < n ; i++)
   {
       if (s[i].value == u){
           return 1 ;
       }
   }
   return 0;
}

int minLink(int a, int b){
    if(a < 0) return b;
    if(b < 0) return a;
    if(b<a) return b; else return a;
}

destiny* newDestiny(){
    destiny *new;
    new = (destiny*)malloc(sizeof(destiny));
    new->_valor = 0;
    new->next = NULL;
    return new;
}

void initPerson(int n, struct person *ppl){
    int i = 0;
    while(i < n){
    ppl[i]._d = -1;
    ppl[i]._low = -1;
    ppl[i].first = NULL;
    i++;
    }
}

void insert(person* ppl, int u, int v){
    destiny* p;
    destiny* aux;
    p = (destiny*)malloc(sizeof(destiny));
    p->_valor = v;
    p->next = NULL;
    aux = ppl[u-1].first;
    if(aux == NULL)
        ppl[u-1].first = p;
    else{
        while(aux->next != NULL){
          aux = aux->next;
      }
      aux->next = p;
    }
}
/*int noExitScc(person* arraydepessoas,int n){
  int i ;
  int lowE ;
  int countNoExit = 0 ;
  int result ;
  destiny* search ;
  for (i = 0 ; i < n ; i++)
  {
    search = arraydepessoas[i].first ;
    lowE = arraydepessoas[i]._low ;
    if(arraydepessoas[i]._d == -1){
      break;
    }
    else{
      if(search != NULL)
      {
        if (arraydepessoas[search->_valor]._low != lowE)
        {
          countNoExit++ ;
        }
          while (search->next != NULL)
            {
              if (arraydepessoas[search->_valor]._low != arraydepessoas[search->next->_valor]._low)
              {
              countNoExit++;
              }
            else{
              search=search->next;
                }
            }
      }
      else{
        countNoExit++;
        }
      }
      } 
    result = cntScc - countNoExit ;
    printf("Count com saida %d\n",countNoExit );
    return result ;
}*/


void visita(person* ppl, int u, int* visited, stack* s, int n){
   int o = u-1;
   int v = -1;
   int countExit = 0 ;
   int stop = 0 ;
   
   int cntdim = 0;
   

  
   destiny* f;
   destiny* sea;
   ppl[o]._d = (*visited);
   ppl[o]._low = (*visited);
   (*visited)++;
   f = ppl[o].first;
   pushStack(s ,(o+1),n);
   while ( f != NULL) {
       if (ppl[f->_valor-1]._d == -1 || (searchStack(s,f->_valor,n))){
               if (!searchStack(s,f->_valor,n)){
                       visita(ppl,f->_valor,visited, s, n);
                   }
                      /*printf("Low 1 : %d\n",ppl[o]._low);
                      printf("Low 2 : %d\n",ppl[f->_valor-1]._low);
                      printf("D 1 : %d\n",ppl[o]._d);
                      printf("D 2 : %d\n",ppl[f->_valor-1]._d);*/
                       ppl[o]._low = minLink(ppl[f->_valor-1]._low , ppl[o]._low);
       }
       f = f->next ;
   }
       if (ppl[o]._d  == ppl[o]._low ){
           while (u != v){
               v = popStack(s,n);
               while ( stop != 1)
               {
                sea = ppl[v-1].first;
                if ( sea == NULL)
                {
                  stop = 1;
                  break;
                }
                if ( ppl[sea->_valor -1]._low != ppl[v-1]._low){
                    countExit++;
                    stop = 1 ;
                    break;
                  }
                while ( (sea != NULL) && (stop!=1)){
                    
                    if(ppl[sea->_valor-1]._d == ppl[o]._d)
                    {
                      stop = 1 ;
                      break;
                    }
                    if (ppl[sea->_valor -1 ]._low != ppl[v-1]._low){
                      countExit++ ;
                      stop = 1 ;
                      break;
                    }
                    else{
                      sea = sea->next;
                    }

                }
               }
               printf("u = %d ,v = %d \n", u , v);
               cntdim++;
            
		    }
		    if(cntdim > MScc)
		        MScc = cntdim; 
		    cntScc++;
	    	printf("scc's = %d\n", cntScc);
       	}
       	printf("maior scc = %d\n", MScc);
        printf ("Numero sem saida %d\n",cntScc - countExit);

}

void sirTarjan(person* ppl, int n, stack* s){
   int visited = 0;
   int i = 0;
   int h = 1;
   while(i < n){
       ppl[i]._d = -1;
       i++;
   }
   while(h <= n){
       if(ppl[h-1]._d == -1)
           visita(ppl, h, &visited, s, n);
       h++;
   }
}


int readIn(){
    int n, p, u, v;
    struct person* ppl;
    struct stack* s;
    scanf("%d %d", &n, &p);
    ppl = (person*)malloc(sizeof(person)*n);
    initPerson(n, ppl);
    s = (stack*)malloc(sizeof(stack)*n);
    initStack(n, s);
    while( fscanf(stdin,"%d %d",&u,&v) != EOF) {
        insert(ppl, u, v);
    }
    sirTarjan(ppl, n, s); 
    /*printf("Sccs sem said = %d\n",noExitScc(ppl,n));*/
    return 0;
}

int main(int argc, char *argv[]){
   readIn();
return 0;
}
