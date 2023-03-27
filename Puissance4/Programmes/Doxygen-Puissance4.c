/**
* \file Puissance4.c
* \page Programme Puissance 4
* \author Julien PERRIGUEY (1ère Année de BUT Informatique)
* \version 1.0
* \date 24 Novembre 2022
*
* Ce programme réalise le jeu Puissance 4, en utilisant un tableau à 2 dimensions et un tableau à 1 dimension.
*/


/************************
 * LIBRAIRIES UTILISEES *
************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*******************************************************
 * DEFINITIONS DES COULEURS ET DES VARIANTES DE POLICE *
*******************************************************/
#define ROUGE "\033[00;31m" /* Utilisation des codes de couleurs syntaxiques */
#define JAUNE "\033[00;33m"  
#define CYAN "\033[00;36m"
#define GRAS "\033[01m"
#define NORMAL "\033[00m"


/***************************
 * DEFINITIONS DES DEFINES *
***************************/
/**
* \def NBLIG 
* \brief Nombre de lignes maximum de la grille de Jeu 
*/
#define NBLIG (6)

/**
* \def NBCOL
* \brief Nombre de colonnes maximum de la grille de Jeu 
*/
#define NBCOL (7)

/**
* \def N
* \brief Nombre de colonnes maximales pour le tableau apparaissant au-dessus de la grille 
*/
#define N (7)

/******************************
 * DEFINITIONS DES CONSTANTES *
******************************/
/**
* \def PION_A
* \brief constante pour le pion 'O' du Joueur 1
*/
const char PION_A = 'O';

/**
* \def PION_B
* \brief constante pour le pion 'X' du Joueur 2
*/
const char PION_B = 'X';

/**
* \def VIDE
* \brief constante pour qu'un pion soit VIDE dans la grille
*/
const char VIDE = ' ';

/**
* \def INCONNU
* \brief constante qui détermine le vainqueur du jeu (prendra PION_A ou PION_B)
*/
const char INCONNU = ' ';

/**
* \def COLONNE_DEBUT
* \brief constante qui définit la position où se placera le jeton en cour au-dessus de la grille
*/
const int COLONNE_DEBUT = NBCOL/2;      // Le pion affiché au-dessus de la grille apparaîtra en occurence 3


/****************************
 * DEFINITIONS DES TYPEDEFs *
****************************/
/**
* \typedef Grille
* \brief Tableau à 2 entrées : d'abord les LIGNES (qui prend en paramètres NBLIG), puis les COLONNES (qui prend en paramètres NBCOL)
*/
typedef char Grille[NBLIG][NBCOL];      // Grille de jeu (Tableau en 2D) de type 'chaîne'

/**
* \typedef TableauIndex
* \brief Tableau à 1 entrée, qui prend en paramètre N
*/
typedef char TableauIndex [N];      // Tableau qui apparaît au-dessus de la grille de jeu (Tableau en 1D) de type 'chaîne'. Ce tableau sera appelé "Tableau Index" 


/*******************************************
 * ENTETES DES PROCEDURES ET DES FONCTIONS *
*******************************************/
void initGrille (Grille);
void afficher (Grille); 
void saisie_Index (TableauIndex, char);
void afficher_Index (TableauIndex);
bool grillePleine (Grille); 
void jouer (Grille, TableauIndex, char, int *, int *);
int choisirColonne (Grille, TableauIndex, char); 
int trouverLigne (Grille, int); 
int nb_pions_dir(Grille, int, int, int, int, char);
bool estVainqueur (Grille, int, int, char);
void finDePartie (char);


/***********************
 * PROGRAMME PRINCIPAL *
***********************/
/**
* \fn int main()
* \brief Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principal simule un jeu de Puissance 4, il créer 1 tableau 1D, 
* et 1 tableau 2D. 2 joueurs placent à tour de rôle un pion dans la grille de jeu 
* (composée de 7 colonnes et 6 lignes). Celui qui aligne 4 pions identiques remporte la partie.
*/
int main ()
{
    char vainqueur;
    int ligne, colonne;
    TableauIndex t;
    Grille g;
    initGrille(g);      // Initialisation de la grille de jeu
    vainqueur = INCONNU;
    while ((vainqueur == INCONNU) && (!(grillePleine(g))))      // Tant que le vainqueur ne vaut ni PION_A ni PION_B, ou VIDE ET que la grille n'est pas pleine
    {
        jouer(g, t, PION_A, &colonne, &ligne);      // Le joueur 1 joue 
        afficher(g);        // La grille est affichée 
        if (estVainqueur(g, ligne, colonne, PION_A))        // Si 4 pions 'O' sont alignés, le joueur 1 gagne      
        {
            vainqueur = PION_A;
        }
        else if (!(grillePleine(g)))        // Si la grille n'est toujours pas pleine : 
        {
            jouer(g, t, PION_B, &colonne, &ligne);      // Le joueur 2 joue
            afficher(g);        // La grille est affichée
            if (estVainqueur(g, ligne, colonne, PION_B))        // Si 4 pions 'X' sont alignés, le joueur 1 gagne 
            {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);     // Le résultat de la partie est affiché 
    return EXIT_SUCCESS;
}



/***************************
 * PROCEDURES ET FONCTIONS *
***************************/
/**
 * \fn void initGrille (Grille tableau)
 * \brief Procédure qui initialise la grille de jeu 
 * \param tableau : Grille, les pions sont stockés dans la Grille de jeu
 * 
 * Permet d'initaliser la grille en attribuant la constante VIDE à toutes les cases du tableau 
 */
void initGrille (Grille tableau)
{
    int colonne, ligne;
    for (colonne = 0; colonne < NBCOL; colonne++)       // Pour chaque colonne (de 0 à 7)
    {
        for (ligne = 0; ligne < NBLIG; ligne++)     // Pour chaque ligne (de 0 à 6)
        {
            tableau[ligne][colonne] = VIDE;     // Chaque case contient maintenant le caractère ' '
        }
        /* L'attribution se fait donc comme cela : [0][0], [0][1], (...), [6][7] */
    }
}



/**
 * \fn void saisie_Index (TableauIndex tabIndex, char PION)
 * \brief Procédure qui initialise le Tableau Index 
 * \param tabIndex : TableauIndex,  les chaines de caractères sont stockées dans le tableau Index
 * \param PION : char, chaîne qui prendra 'PION_A' ou 'PION_B'
 * 
 * Permet d'initaliser le Tableau Index en attribuant la constante VIDE à toutes les cases du tableau
 * Puis on attribue à l'occurence 3 (=COLONNE_DEBUT), le pion en cours
 */
void saisie_Index (TableauIndex tabIndex, char PION)
{
    int i;
    for (i=0; i<N; i++)
    {
        tabIndex[i] = VIDE;     // Toutes les valeurs sont initialisées à ' '
    }
    tabIndex[COLONNE_DEBUT] = PION;     // Seule la 3ème occurence possède un pion (qui sera ensuite déplacé)
}



/**
 * \fn void afficher_Index (TableauIndex tabIndex)
 * \brief Procédure qui affiche le Tableau Index 
 * \param tabIndex : TableauIndex, les chaînes de caractères sont stockées dans le Tableau Index
 * 
 * Affiche chaque valeur du Tableau Index (1 occurrence à PION, et le reste à VIDE)
 */
void afficher_Index (TableauIndex tabIndex)
{
    int i;
    for (i=0; i<N; i++)
        {
            printf("     %c", tabIndex[i]);     // Chaque occurence est affichée au-dessus d'un chiffre de la grille de jeu,
            printf("     ");                    // mais un seul est visible (puisqu'il n'y a qu'un pion, et le reste vaut VIDE) 
        }
        printf("\n");
}



/**
 * \fn void afficher (Grille tableau)
 * \brief Procédure qui affiche la grille de jeu
 * \param tableau : Grille,  les pions stockés dans la grille sont affichés
 * 
 * Affiche chaque valeurs de la Grille de jeu (soit VIDE, soit PION_A, soit PION_B)
 */
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
            
                printf("     %c    |", tableau[ligne][colonne]);        // Les pions seront affichés grâce à cette ligne 
            
             
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



/**
 * \fn bool grillePleine (Grille tableau)
 * \brief Fonction booléenne qui détermine si la grille est pleine ou non
 * \param tableau : Grille, les pions sont stockés dans la grille
 * \return bool, false si la grille est pleine, true sinon
 * 
 * Teste si toutes les cases de la grille sont occupées ou non. La fonction parcourt la 
 * grille de jeu, si elle rencontre une case vide, le jeu continue, sinon, le jeu est arrêté
 */
bool grillePleine (Grille tableau)
{
    int colonne, ligne;
    for (colonne = 0; colonne < NBCOL; colonne++)
    {
        for (ligne = 0; ligne < NBLIG; ligne++)
        {
            if (tableau[ligne][colonne] == VIDE)
            {
                return false;       //  Si une case vide est détectée, la fonction renvoie false au main, et le jeu continu
            }
        }
    }
    return true;        // Si aucune case vide n'est trouvée, la fonction renvoie true au main, et celui-ci stoppe la partie
}



/**
 * \fn void jouer (Grille tableau, TableauIndex tabIndex, char PION, int *col, int *lig)  
 * \brief Procédure  qui détermine si la grille est pleine ou non
 * \param tableau : Grille,  les chaines de caractères sont stockées dans le Tableau Index
 * \param tabIndex : TableauIndex, les chaînes de caractères sont stockées dans le Tableau Index
 * \param PION : char, chaîne qui prendra 'PION_A' ou 'PION_B'
 * \param col : int, utilisé en sortie, il renvoie l'indice de la colonne où le joueur souhaite placer son pion
 * \param lig : int, utilisée en sortie, elle renvoie l'indice de la ligne où le pion se placera
 * 
 * La procédure jouer permet au joueur de jouer son pion. Pour cela, elle renvoie les coordonnées 
 * d'où sera joué le prochain coup, grâce à l'appel des fonctions choisirColonne et trouverLigne 
 */
void jouer (Grille tableau, TableauIndex tabIndex, char PION, int *col, int *lig)  
{
    *col = choisirColonne(tableau, tabIndex, PION);     // *col prend la valeur que la fonction choisirColonne renvoie
    *lig = trouverLigne(tableau, *col);     // *lig prend la valeur que la fonction trouverLigne renvoie
    while (*lig == -1)      // Lorsque trouverLigne renvoie '-1', cela veut dire que la colonne demandée par le joueur est pleine
    {   // On demande alors au joueur de choisir une autre colonne, jusqu'à ce que celle-ci soit valide
        printf("Cette colonne est remplie, veuillez selectionnez une autre colonne.\n");
        *col = choisirColonne(tableau, tabIndex, PION);
        *lig = trouverLigne(tableau, *col);
    } 
    tableau[*lig][*col] = PION;     // Le pion du joueur se place aux coordonnées récupérées
}



/**
 * \fn int choisirColonne (Grille tableau, TableauIndex tabIndex, char PION) 
 * \brief Fonction qui détermine l'indice de la colonne où le prochain pion sera joué
 * \param tableau : Grille,  les chaines de caractères sont stockées dans le Tableau Index
 * \param tabIndex : TableauIndex, les chaînes de caractères sont stockées dans le Tableau Index
 * \param PION : char, chaîne qui prendra 'PION_A' ou 'PION_B' 
 * \return int, l'indice de la colonne où le joueur décide de jouer
 * 
 * Le joueur voit son pion au-dessus de la grille, elle lui permet de déplacer son pion vers la gauche ou vers la droite, pour chosir dans quelle colonne son pion ira
 * Si le joueur souhaite déplacer son pion vers la gauche, il entrera la touche 'q', puis sur ENTREE.
 * Si le joueur souhaite déplacer son pion vers la droite, il entrera la touche 'd', puis sur ENTREE.
 * Une fois que le joueur à décider dans quelle colonne il souhaite jouer, il appuie sur la touche ESPACE, puis sur ENTREE, pour que son pion tombe dans la grille. 
 */
int choisirColonne (Grille tableau, TableauIndex tabIndex, char PION) 
{
    char touche;
    int indice_col;
    int i;
    i = COLONNE_DEBUT;
    saisie_Index(tabIndex, PION);       // On utilise saisie_Index pour initialiser les variables du Tableau Index se trouvant au-dessus de la grille de jeu
    while (touche != 32) 
    {
        // Selon le pion, le message ne s'affiche pas de la même couleur 
        if (PION == PION_A)
        {
            /* L'utilisation des polices s'exécutent comme ceci : on définit la couleur (ROUGE), 
            puis le style de la police (GRAS), on insère notre texte, puis on fait un retour 
            à la normale (NORMAL), pour que les styles n'affectent pas les prochains printf */
            printf(ROUGE GRAS "Joueur 1, a votre tour de joueur.\n" NORMAL);
        }
        else if (PION == PION_B)
        {
            printf(JAUNE GRAS "Joueur 2, a votre tour de jouer.\n" NORMAL);
        }
        afficher_Index(tabIndex);       // On affiche ensuite le tableau au-dessus de la grille de jeu
        afficher(tableau);      // Puis on affiche la grille de jeu
        touche = getchar();     // La touche du joueur sera enregistrée (celle-ci ne peut être que 'q', 'd', ou 'ESPACE')
        switch(touche)
        {
            case 'q' :      // 'q' effectue un déplacement vers la gauche
            if (i == 0)
            {
                tabIndex[i] = PION;     // Si la colonne est 0, alors le joueur ne peut plus se déplacer à gauche, et reste dans les limites de la grille
                break;
            }
            else if (i != 0)
            {
                tabIndex[i] = VIDE;     // On "efface" la précédente position du pion, pour la passer à VIDE 
                i--;
                tabIndex[i] = PION;     // Puis on affiche le pion à la nouvelle position
                break;
            }
                
            case 'd' :      // 'd' effectue un déplacement vers la droite
            if (i == 6)
            {
                tabIndex[i] = PION;     // Si la colonne est 6 (7ème colonne, mais 6ème occurence), alors le joueur ne peut plus se déplacer à droite, et reste dans les limites de la grille
                break;
            }
            else if (i != 6)
            {
                tabIndex[i] = VIDE;     // On "efface" la précédente position du pion, pour la passer à VIDE 
                i++;
                tabIndex[i] = PION;     // Puis on affiche le pion à la nouvelle position
                break;
            }

            case 32 :       // 'ESPACE' confirme la colonne où le joueur souhaite jouer | *32 est le code décimal qui renvoie à la touche ESPACE
                indice_col = i;
                break;

            default : printf("Veuillez appuyer sur 'q', 'd' ou 'ESPACE'.\n");       // Si la touche pressée n'est ni un 'q', un 'd', ou un 'ESPACE', 
                                                                                    // le programme demande au joueur de recommencer lors saisie de touche 
        }
    }
    return indice_col;      // On retourne l'indice de la colonne grâce au Tableau Index
}



/**
 * \fn int trouverLigne (Grille tableau, int colonne)
 * \brief retourne l'indice de la ligne où le coup sera joué
 * \param tableau : Grille,  les chaines de caractères sont stockées dans le Tableau Index
 * \param colonne : int, indice de la colonne où le pion sera joué
 * \return int, l'indice de la ligne où le pion tombera
 * 
 * Cette fonction consiste à trouver la première case non occupée de la colonne. Si la colonne est pleine, la
 * fonction retourne -1, et le joueur doit une nouvelle fois choisir dans quelle colonne il souhaite jouer son pion.
 */
int trouverLigne (Grille tableau, int colonne)
{
    int ligne;
    int l = -1;
    for (ligne=NBLIG-1; ligne>=0; ligne--)
    {
        if (tableau[ligne][colonne] == VIDE)        // Parcourt la colonne donnée par le joueur, on vérifie si celle-ci n'est pas déjà remplie
        {
            l = ligne;
            break;
        }
        else 
        {
            l = -1;
        }
    }
    return l;       // On retourne l'indice de la ligne
}



/**
 * \fn int nb_pions_dir (Grille tableau, int ligne, int colonne, int direction_x, int direction_y, char PION)
 * \brief détermine combien de pions identiques sont alignés à chaque coup
 * \param tableau : Grille,  les chaines de caractères sont stockées dans le Tableau Index
 * \param ligne : int, indice de la ligne où le pion a été joué
 * \param colonne : int, indice de la colonne où le pion a été joué
 * \param direction_x : int, direction dans le sens des colonnes (soit vers le haut, ou vers le bas)
 * \param direction_y : int, direction dans le sens des lignes (soit vers la gauche, soit vers la droite)
 * \param PION : char, chaîne qui prendra 'PION_A' ou 'PION_B' 
 * \return int, le nombre de pions alignés
 * 
 * Cette fonction est utilisée pour détecter un alignement de 4 pions dans la grille
 */
int nb_pions_dir(Grille tableau, int ligne, int colonne, int direction_x, int direction_y, char PION)
{
    int l;      // ligne dans la direction + ou - 
    int c;      // colonne dans la direction + ou -
    int resultat;
    resultat = 1;       // resultat initialisé à '1', car il compte le jeton qui vient d'être joué 

    /* Cette partie va vers "l'avant" (la droite) */
    c = colonne + direction_x;
    l = ligne + direction_y;
    while(tableau[l][c] == PION)
    {
        resultat++;     // Si on détecte un pion, résultat prend +1
        c = c + direction_x;
        l = l + direction_y;
    }

    /* Cette partie va vers "l'arrière" (la gauche) */
    c = colonne - direction_x;
    l = ligne - direction_y;
    while(tableau[l][c] == PION)
    {
        resultat++;     // Si on détecte un pion, résultat prend +1
        c = c - direction_x;
        l = l - direction_y;
    }
    return resultat;        // On retourne le nombre de jetons alignés 
}



/**
 * \fn bool estVainqueur(Grille tableau, int ligne, int colonne, char PION)
 * \brief détermine s'il y a eu un alignement de 4 pions identiques
 * \param tableau : Grille,  les chaines de caractères sont stockées dans le Tableau Index
 * \param ligne : int, indice de la ligne où le pion a été joué
 * \param colonne : int, indice de la colonne où le pion a été joué
 * \param PION : char, chaîne qui prendra 'PION_A' ou 'PION_B' 
 * \return bool, true si 4 pions identiques sont alignés, false sinon.
 * 
 * Indique si le pion situé dans la case repérée par les paramètres ligne et colonne a gagné la partie,
 * c’est-à-dire s’il y a une ligne, une colonne ou une diagonale formée d’au moins 4 de ses pions (la
 * ligne et la colonne passées en paramètres correspondent à la case où le joueur vient de jouer,
 * c’est-à-dire la case à partir de laquelle il faut rechercher 4 pions successifs identiques).
 */
bool estVainqueur(Grille tableau, int ligne, int colonne, char PION)
{
    bool alignement;
    alignement = false;
   
        if (nb_pions_dir(tableau, ligne, colonne, 1, 1, PION) >= 4)     // Détecte un alignement de 4 pions en diagonale descendante (comme cela: \)
        {
            alignement = true;
        }
        if (nb_pions_dir(tableau, ligne, colonne, 1, 0, PION) >= 4)     // Détecte un alignement de 4 pions à l'horizontal (comme cela: --)
        {
            alignement = true;
        }
        if (nb_pions_dir(tableau, ligne, colonne, 1, -1, PION) >= 4)    // Détecte un alignement de 4 pions en diagonale ascendante (comme cela: /)
        {
            alignement = true;
        }
        if (nb_pions_dir(tableau, ligne, colonne, 0, 1, PION) >= 4)     // Détecte un alignement de 4 pions à la verticale (comme cela: |)
        {
            alignement = true;
        }
    /* Si 4 pions identiques ou plus sont alignés on retourne vrai au programme principal */
    return alignement;
}



/**
 * \fn void finDePartie (char vainqueur)
 * \brief détermine s'il y a un gagnant, et si oui, lequel
 * \param vainqueur : char, paramètre qui prend la valeur PION_A, PION_B, ou VIDE
 * 
 * Affiche le résultat de la partie lorsque celle-ci est terminée
 */
void finDePartie (char vainqueur)
{
    if (vainqueur == PION_A)        // Si le vainqueur est égal au pion du joueur 1, alors celui-ci remporte la partie
    {
        printf(ROUGE GRAS "Le joueur 1 a remporte la partie.\n" NORMAL);
    }
    else if (vainqueur == PION_B)       // Si le vainqueur est égal au pion du joueur 2, alors celui-ci remporte la partie
    {
        printf(JAUNE GRAS "Le joueur 2 a remporte la partie.\n" NORMAL);
    }
    else if (vainqueur == VIDE)     // Si le vainqueur est égal à VIDE, personne ne gagne, il y a donc égalité 
    {
        printf(CYAN GRAS "Egalite, aucun joueur n'a remporte la partie.\n" NORMAL);
    }
}