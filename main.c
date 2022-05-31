#include "stdio.h"
#include "gmp.h"
#include <string.h>
#include <stdlib.h> 
#include "time.h"








void square_and_multiply(mpz_t a, mpz_t n, mpz_t exp, mpz_t r){

    if ( mpz_cmp_ui(exp, 1) == 0) {
        mpz_mod(r, a, n);
    }

    else {
char* h;
h=mpz_get_str(NULL,2,exp);  //decomposition binaire de l'exposant
//printf("h : %s\n", h);  // affichage de mon exposant en binaire 
    	mpz_set(r,a); //  on met r=a
		int i;
    	for( i=1; i<strlen(h);i++) 
		
   	 	{                  
			//r²mod n            
			mpz_mul(r,r,r);
			mpz_mod(r,r,n);

			if(h[i] == '1')
			{
				//r*a mod n
				mpz_mul(r,r,a);
				mpz_mod(r,r,n);
			}
		}
    }
}


int Fermat(mpz_t n, int  k)
{
    //Initialisation du rand
    gmp_randstate_t state; 
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    
    mpz_t exp,a,m,r;
    int i = 1;

   
    mpz_init(exp);
    mpz_init(a);
    mpz_init(r);
    mpz_init(m);

    

    mpz_sub_ui(exp,n,1);
    mpz_sub_ui(m,n,2);//strictement plus petit que n-1

    
        char* h;
    while(i <= k)
    {

        if (mpz_cmp_si(n,2)==0 || mpz_cmp_si(n,3)==0)break; //test

        mpz_urandomm(a,state,m);
        mpz_add_ui(a,a,1);  //Genere l'entier a aleatoirement entre 1 < a < n-1


    

       square_and_multiply(a, n, exp, r);


        if(mpz_cmp_si(r,1)!=0)
        {
            
            
            mpz_clear(exp);
            mpz_clear(a);
            mpz_clear(r);
            mpz_clear(m);
            
            gmp_randclear(state);

            return 0;
        }
        i++; 
    }

    
    mpz_clear(exp);
    mpz_clear(a);
    mpz_clear(r);
    mpz_clear(m);
    gmp_randclear(state);
    return 1;
    
    
}

int Miller_Rabin(mpz_t n, int  k)
{
if(mpz_get_ui(n) % 2 == 0) 
	{
		if(mpz_cmp_ui(n,2) == 0)     // on test si n pair et différent de 2
		{
			return 1;					
		}
        else
        {
            return 0;							
        }
	}

    //declarations de variables 
    mpz_t t, var, a, y, m;

    int s = 0;
    mpz_init(a);
    mpz_init(m);
    mpz_init(y);
    mpz_init(t);
    mpz_sub_ui(t, n, 1);
    mpz_init(var);
    mpz_mod_ui(var,t,2);


    gmp_randstate_t state; 
    gmp_randinit_default(state);//Initialisation du rand
    gmp_randseed_ui(state, time(NULL));


    //Décomposition du nombre 
        while (mpz_cmp_ui(var, 0) == 0) {
            mpz_cdiv_q_ui (t, t, 2) ;    // on devise t sur 2 
            mpz_mod_ui(var,t,2); 
            s++; // on compte le nombre de fois ou on devise t
        }
        mpz_sub_ui (m, n, 1);

    for (int i = 1; i <= k; i++) {

          mpz_urandomm(a,state,m);   //Genere l'entier a aleatoirement entre 1 < a < n
          mpz_add_ui(a,a,1); 

        
            
        square_and_multiply(a, n, t, y);
        mpz_mod(var, y, n);

        if (mpz_cmp_ui(var, 1) != 0 && mpz_cmp(var, m) != 0) {
            int j = 1;
            while (j <= s-1) {
                mpz_mul(y,y,y);
                mpz_mod (y,y,n);
                mpz_mod(var, y, n);
                if (mpz_cmp_ui(var, 1) == 0) {
                    mpz_clear(a);
                    mpz_clear(m);
                    mpz_clear(y);
                    mpz_clear(t);
                    mpz_clear(var);
                    return 0;
                }
                else if (mpz_cmp(var, m) == 0) {
                    j = s+1;   // on sort de la boucle j 
                }
                j++;
            }
            if (j != s+2) {
                mpz_clear(a);
                mpz_clear(m);
                mpz_clear(y);
                mpz_clear(t);
                mpz_clear(var);
                return 0;}
        }
    }

    mpz_clear(a);
    mpz_clear(m);
    mpz_clear(y);
    mpz_clear(t);
    mpz_clear(var);
   
    return 1;
}






int main()
{
    mpz_t n;
    int k;
    int choix;
    int test;

    mpz_init(n);
    
        printf("Fermat ou Miller-Rabin ?\n");
        printf("Fermat: Tappez 0\n");
        printf("Miller-Rabin: Tappez 1\n");
        scanf("%d",&choix);

        while (choix != 0 && choix != 1) {printf("Veuillez tappez 0 ou 1 "); 
        scanf("%d",&choix);}


        printf("Choisir n : ");
        gmp_scanf("%Zd", &n);
        if(mpz_cmp_ui(n,1)<=0)
        {   
            printf("\n Erreur nombre inférieur à 2\n");
        }
        else
        {
            printf("Choisir k : ");
            scanf("%d", &k);

            
            if (choix == 0) {
                printf ("Algorithme choisit: Fermat\n");
                test = Miller_Rabin(n, k);}
            else { printf ("Algorithme choisit: Miller-Rabin\n"); 
                    test=Fermat(n,k);}
            
            if (test==1)gmp_printf("%Zd est premier \n",n);
            else gmp_printf("%Zd est composé \n",n);//
            
        }   

    mpz_clear(n);   
   

    return 0;
}

