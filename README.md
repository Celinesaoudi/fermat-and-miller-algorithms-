# Fermat_MillerRabin
Ce Projet a pour but d'implémentater les algorithmes de primalités de Fermat et Miller-Rabin en utilisant la librairie GMP 


Commandes d'utilisation
 Pour compiler :
  Pour utiliser ce programme la bibliothèque GMP MP doit étre installé
  celle ci peut étre installer avec la commande sous linux "sudo apt install libgmp-dev"
  Pour executer le programme il suffit de lancer le makefile en tappant la commande make.

 dans une premiere etape le programme vous demande de tapper soit 0 ou 1 a fin de choisir l'algorithme a executer: 
 0 pour l'algorithme de Fermat 
 1 pour l'algorithme de Miller Rabin 

La deuxième étape est de tapper le nombre N à tester.
La dernière étape est de tapper le nombre K, le nombre de fois qu'on veut effectuer le test.

Comme valeur de retour, le programme affiche dans la console si le nombre est composé ou premier.



Le programme principale est ecrit dans le fichier main.c, il est constitué de: 
La fonction square_and_multiply(mpz_t a, mpz_t n, mpz_t exp, mpz_t r):
Cette derniere  utilise les techniques d'exponentiation rapide avec un modulo à mod. (a^exp) % mod

int Fermat(mpz_t n, int k);
La fonction fermat prend en paramètres un entier de type mpz_t de la bibliothèque GMP et un entier k et exécute k fois le test de Fermat sur l'entier. Renvoie un entier (0 pour premier ou bien 1 composé).


int Miller_Rabin(mpz_t n, int k);
La fonction miller_rabin prend en paramètres un entier de type mpz_t de la bibliothèque GMP et un entier k et exécute k fois le test de Miller-Rabin sur l'entier. Renvoie un entier (0 pour premier ou bien 1 composé).

Et une fonction main.




