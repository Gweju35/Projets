#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Initialisation des couleurs 
#define ROUGE "\033[00;31m"
#define JAUNE "\033[00;33m"  
#define CYAN "\033[00;36m"
#define GRAS "\033[01m"
#define NORMAL "\033[00m"

#define NBLIG (6)
#define NBCOL (7)
#define N (7)

const char PION_A = 'O';
const char PION_B = 'X';
const char VIDE = ' ';
const char INCONNU = ' ';
const int COLONNE_DEBUT = NBCOL/2;

typedef char Grille[NBLIG][NBCOL]; 
typedef char TableauIndex [N];



void initGrille (Grille);
void afficher (Grille); 
void saisie_Index (TableauIndex, char);
void afficher_Index (TableauIndex);
bool grillePleine (Grille); // retourne booléen
void jouer (Grille, TableauIndex, char, int *, int *);
int choisirColonne (Grille, TableauIndex, char); // retourne entier
int trouverLigne (Grille, int); // retourne entier
int nb_pions_dir(Grille, int, int, int, int, char);
bool estVainqueur (Grille, int, int, char); // retourne booléen
void finDePartie (char);

int main ()
{
    char vainqueur;
    int ligne, colonne;
    TableauIndex t;
    Grille g;
    initGrille(g);
    vainqueur = INCONNU;
    while ((vainqueur == INCONNU) && (!(grillePleine(g)))) 
    {
        jouer(g, t, PION_A, &colonne, &ligne);
        afficher(g);
        if (estVainqueur(g, ligne, colonne, PION_A))
        {
            vainqueur = PION_A;
        }
        else if (!(grillePleine(g)))
        {
            jouer(g, t, PION_B, &colonne, &ligne);
            afficher(g);
            if (estVainqueur(g, ligne, colonne, PION_B)) 
            {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
}




void initGrille (Grille tableau)
{
    int colonne, ligne;
    for (colonne = 0; colonne < NBCOL; colonne++)
    {
        for (ligne = 0; ligne < NBLIG; ligne++)
        {
            tableau[ligne][colonne] = VIDE;
        }
    }
}

void saisie_Index (TableauIndex tabIndex, char PION)
{
    int i;
    for (i=0; i<N; i++)
    {
        tabIndex[i] = VIDE;
    }
    tabIndex[COLONNE_DEBUT] = PION;
}


void afficher_Index (TableauIndex tabIndex)
{
    int i;
    for (i=0; i<N; i++)
        {
            printf("     %c", tabIndex[i]);
            printf("     ");
        }
        printf("\n");
}



//void afficher(Grille tableau, char PION, int indice_col)
void afficher(Grille tableau)
{
    int colonne, ligne;
    printf("\n");
    for (colonne = 1; colonne <= NBCOL; colonne++)
    {
        printf("     %d     ", colonne);
    }
    printf("\n");
    for (colonne = 1; colonne <= NBCOL; colonne++)
    {
        printf("|----------");
    }
    printf("|\n");
    for (ligne = 0; ligne < NBLIG; ligne++)
    {
        printf("|");
        for (colonne = 0; colonne < NBCOL; colonne++) 
        {
            
                printf("     %c    |", tableau[ligne][colonne]);
            
             
        }
        printf("\n");
        for (colonne = 1; colonne <= NBCOL; colonne++)
        {
            printf("|----------");
        }
        printf("|");
        printf("\n");
    }
    for (colonne = 1; colonne <= NBCOL; colonne++){
        printf("     %d     ", colonne);
    }
    printf("\n");
}


bool grillePleine (Grille tableau)
{
    int colonne, ligne;
    for (colonne = 0; colonne < NBCOL; colonne++)
    {
        for (ligne = 0; ligne < NBLIG; ligne++)
        {
            if (tableau[ligne][colonne] == VIDE)
            {
                return false;
            }
        }
    }
    return true;
}


void jouer (Grille tableau, TableauIndex tabIndex, char PION, int *col, int *lig)  
{
    *col = choisirColonne(tableau, tabIndex, PION);
    *lig = trouverLigne(tableau, *col);
    
    while (*lig == -1)
    {
        printf("Cette colonne est remplie, veuillez selectionnez une autre colonne.\n");
        *col = choisirColonne(tableau, tabIndex, PION);
        *lig = trouverLigne(tableau, *col);
    } 
    tableau[*lig][*col] = PION;
}



int choisirColonne (Grille tableau, TableauIndex tabIndex, char PION) 
{
    char touche;
    int indice_col;
    int i;
    i = COLONNE_DEBUT;
    saisie_Index(tabIndex, PION);
    while (touche != 32) //ESPACE //JAI MIS SUR ECHAP LE TEMPS DE PAS EN PERDRE JUSTEMENT DONC TU ME MODIFIERAS CETTE PU**** DE VARIABLE !!!!!! //*32
    //GAFFE AU ++, LES ++ SONT APRES LES VARIABLES PAS AVANT
    {
        if (PION == PION_A)
        {
            printf(ROUGE GRAS "Joueur 1, a votre tour de joueur.\n" NORMAL);
        }
        else if (PION == PION_B)
        {
            printf(JAUNE GRAS "Joueur 2, a votre tour de jouer.\n" NORMAL);
        }
        afficher_Index(tabIndex);
        afficher(tableau);
        touche = getchar();
        switch(touche)
        {
            case 'q' :
            if (i == 0)
            {
                tabIndex[i] = PION;
                break;
            }
            else if (i != 0)
            {
                tabIndex[i] = VIDE;
                i--;
                tabIndex[i] = PION;
                break;
            }
                
            case 'd' :
            if (i == 6)
            {
                tabIndex[i] = PION;
                break;
            }
            else if (i != 6)
            {
                tabIndex[i] = VIDE;
                i++;
                tabIndex[i] = PION;
                break;
            }

            case 32 :
                indice_col = i;
                break;

            default : printf("Veuillez appuyer sur 'q', 'd' ou 'ESPACE'.\n");
        }
    }
    return indice_col;
}



int trouverLigne (Grille tableau, int colonne)
{
    int ligne;
    int l = -1;
    for (ligne=NBLIG-1; ligne>=0; ligne--)
    {
        if (tableau[ligne][colonne] == VIDE)
        {
            l = ligne;
            break;
        }
        else 
        {
            l = -1;
        }
    }
    return l;
}

int nb_pions_dir(Grille tableau, int ligne, int colonne, int direction_x, int direction_y, char PION)
{
    int l; //ligne dans la direction +/- direction_y
    int c; //colonne dans la direction +/- direction_x
    int resultat;
    resultat = 1;

    c = colonne + direction_x;
    l = ligne + direction_y;
    while(tableau[l][c] == PION)
    {
        resultat++;
        c = c + direction_x;
        l = l + direction_y;
    }

    
    c = colonne - direction_x;
    l = ligne - direction_y;
    while(tableau[l][c] == PION)
    {
        resultat++;
        c = c - direction_x;
        l = l - direction_y;
    }
    return resultat;   
}

bool estVainqueur(Grille tableau, int ligne, int colonne, char PION)
{
    bool alignement;
    alignement = false;
   
        if (nb_pions_dir(tableau, ligne, colonne, 1, 1, PION) >= 4)
        {
            alignement = true;
        }
        if (nb_pions_dir(tableau, ligne, colonne, 1, 0, PION) >= 4) 
        {
            alignement = true;
        }
        if (nb_pions_dir(tableau, ligne, colonne, 1, -1, PION) >= 4)
        {
            alignement = true;
        }
        if (nb_pions_dir(tableau, ligne, colonne, 0, 1, PION) >= 4)
        {
            alignement = true;
        }
    
    return alignement;
}


void finDePartie (char vainqueur)
{
    if (vainqueur == PION_A)
    {
        printf(ROUGE GRAS "Le joueur 1 a remporte la partie.\n" NORMAL);
    }
    else if (vainqueur == PION_B)
    {
        printf(JAUNE GRAS "Le joueur 2 a remporte la partie.\n" NORMAL);
    }
    else if (vainqueur == VIDE)
    {
        printf(CYAN GRAS "Egalite, aucun joueur n'a remporte la partie.\n" NORMAL);
    }
}