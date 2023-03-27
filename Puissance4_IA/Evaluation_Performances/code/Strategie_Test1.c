#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIGNE 6
#define COLONNE 7

typedef int t_grille[LIGNE][COLONNE];

int main(int argc, char** argv);
void chargerGrille(char** argv, t_grille grille);

const int VIDE = 0;
const int JOUEUR = 1;
const int ADVERSAIRE = 2;


int chercherLigne(t_grille laGrille, int col);
// fonction qui vérifie si la case visé et des alignements de 3 autour d'elle et retourne 1 si c'est le cas

int chercherLigne(t_grille laGrille, int col){
    int ligne = -1;

    while (ligne<LIGNE-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}

int aligne3(t_grille lagrille, char pion, int line, int col) {
    int alignement=0;
    int i,j=0;
    int cmpt=0;

    // vérifie un alignement vertical 
    if (line < 3) {
        i = line+1;

        while (cmpt<3 && i<=line+3) {
            if (lagrille[i][col] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i++;
        }
        if (cmpt == 3) {
            alignement = 1;
            
        }        
    }

    cmpt=0;
    // vérifie un alignement horizontal à gauche
    if (col > 2) {
        i = col-1;

        while (cmpt<3 && i>=col-3) {
            if (lagrille[line][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i--;
        }
        if (cmpt == 3) {
            alignement = 1;
            
        }   
    }

    cmpt=0;
    // vérifie un alignement horizontal à droite
    if (col < 4) {
        i = col+1;

        while (cmpt<3 && i<=col+3) {
            if (lagrille[line][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i++;       
        }
        if (cmpt == 3) {
            alignement = 1;
        }   
    }

    cmpt=0;
    // vérifie un alignement diagonale SUD-OUEST
    if (col > 2 && line < 3) {
        i = col-1;
        j = line+1;
        
        while (cmpt<3 && i>=col-3 && j <= line+3) {
            if (lagrille[j][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i--;
            j++;       
        }
        if (cmpt == 3) {
            alignement = 1;
        }   
    }

    cmpt=0;
    // vérifie un alignement diagonale SUD-EST
    if (col < 4 && line < 3) {
        i = col+1;
        j = line+1;
        
        while (cmpt<3 && i<=col+3 && j <= line+3) {
            if (lagrille[j][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i++;
            j++;       
        }
        if (cmpt == 3) {
            alignement = 1;
        }   
    }

    cmpt=0;
    // vérifie un alignement diagonale NORD-OUEST
    if (col > 2 && line > 2) {
        i = col-1;
        j = line-1;
        
        while (cmpt<3 && i>=col-3 && j >= line-3) {
            if (lagrille[j][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i--;
            j++;       
        }
        if (cmpt == 3) {
            alignement = 1;
        }   
    }

    cmpt=0;
    // vérifie un alignement diagonale NORD-EST
    if (col < 4 && line > 2) {
        i = col+1;
        j = line-1;
        
        while (cmpt<3 && i<=col+3 && j >= line-3) {
            if (lagrille[j][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i++;
            j++;       
        }
        if (cmpt == 3) {
            alignement = 1;
        }   
    }
    return alignement;
}

// fonction qui vérifie si la case visé et des alignements de 2 autour d'elle et retourne 1 si c'est le cas
int aligne2(t_grille lagrille, char pion, int line, int col) {
    int alignement=0;
    int i,j=0;
    int cmpt=0;

    // vérifie un alignement vertical 
    if (line < 4) {
        i = line+1;

        while (cmpt<2 && i<=line+2) {
            if (lagrille[i][col] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i++;
        }
        if (cmpt == 2) {
            alignement = 1;
            
        }        
    }

    cmpt=0;
    // vérifie un alignement horizontal à gauche
    if (col > 1) {
        i = col-1;

        while (cmpt<2 && i>=col-2) {
            if (lagrille[line][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i--;
        }
        if (cmpt == 2) {
            alignement = 1;
            
        }   
    }

    cmpt=0;
    // vérifie un alignement horizontal à droite
    if (col < 5) {
        i = col+1;

        while (cmpt<2 && i<=col+2) {
            if (lagrille[line][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i++;       
        }
        if (cmpt == 2) {
            alignement = 1;
        }   
    }

    cmpt=0;
    // vérifie un alignement diagonale SUD-OUEST
    if (col > 1 && line < 4) {
        i = col-1;
        j = line+1;
        
        while (cmpt<2 && i>=col-2 && j <= line+2) {
            if (lagrille[j][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i--;
            j++;       
        }
        if (cmpt == 2) {
            alignement = 1;
        }   
    }

    cmpt=0;
    // vérifie un alignement diagonale SUD-EST
    if (col < 5 && line < 4) {
        i = col+1;
        j = line+1;
        
        while (cmpt<2 && i<=col+2 && j <= line+2) {
            if (lagrille[j][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i++;
            j++;       
        }
        if (cmpt == 2) {
            alignement = 1;
        }   
    }

    cmpt=0;
    // vérifie un alignement diagonale NORD-OUEST
    if (col > 1 && line > 1) {
        i = col-1;
        j = line-1;
        
        while (cmpt<2 && i>=col-2 && j >= line-2) {
            if (lagrille[j][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i--;
            j++;       
        }
        if (cmpt == 2) {
            alignement = 1;
        }   
    }

    cmpt=0;
    // vérifie un alignement diagonale NORD-EST
    if (col < 5 && line > 1) {
        i = col+1;
        j = line-1;
        
        while (cmpt<2 && i<=col+2 && j >= line-2) {
            if (lagrille[j][i] == pion) {
                cmpt++;
            }
            else {
                cmpt=0;
            }
            i++;
            j++;       
        }
        if (cmpt == 2) {
            alignement = 1;
        }   
    }
    return alignement;
}

int maStrategie(t_grille laGrille) {
    int col = COLONNE/2;
    int start = 0;
    int i = 0;
    int pos_pion[] = {5, 5, 5, 5, 5, 5, 5};
    char monpion = JOUEUR;
    char sonpion = ADVERSAIRE;
    int alignement = 0;

    // ####### RECUPERATION DES POSITIONS DES PIONS #######
    for (int pos=0; pos<COLONNE; pos++) {
        pos_pion[pos] = chercherLigne(laGrille, pos);
    }
    
    // ####### COMMENCEMENT DE LA PARTIE #######

    // ---- Recherche si un pion est déjà posé pour savoir qui commence ----
    for (i=0; i<7; i++){
        start = start+pos_pion[i];
    }
    if (start == 35) {
        return col;
    }
    else if (start == 34) {
        i=0;
        while (pos_pion[i] == 5) {
            i++;
        }
        return i;
    }

    // ####### NIEME COUPS #######

    // ---- Si 3 pions alliés sont alignés et qu’il y a possibilité de gagner ----
    i=0;

    while (i<7 && alignement==0) {
        alignement = aligne3(laGrille, monpion, pos_pion[i], i);
        i++;
    }
    if (alignement == 1) {
        return i-1;
    }

    // ---- Si 3 pions adverses sont alignés et qu’il y a possibilité de défendre ----
    i=0;

    while (i<7 && alignement==0) {
        alignement = aligne3(laGrille, sonpion, pos_pion[i], i);
        i++;
    }
    if (alignement == 1) {
        return i-1;
    }
    
     // ---- Si 2 pions adverses sont alignés et qu’il y a possibilité de défendre ----
    i=0;

    while (i<7 && alignement==0) {
        alignement = aligne2(laGrille, sonpion, pos_pion[i], i);
        i++;
    }
    if (alignement == 1) {
        return i-1;
    }

    // ---- Sinon jouer au dessus du dernier pion rouge placé ET non obstrué par un pion adverse par le dessus ----

    i=0;
    bool trouve=false;
    
    while (i<7 && trouve==false){
        if (laGrille[pos_pion[i]-1][i] == monpion) {
            return i;
        }
        i++;
    }

    // ---- Sinon jouer à la première colonne ou encore a droite ----
    if (i==7){
        col = 0;
        while (pos_pion[col] < 0) {
            col++;
        }
        return col;
    }
    return 2;
}

// La fonction principale reçoit la grille du tour et retourne le coup choisi
// Vous n'avez pas à modifier cette fonction
int main(int argc, char** argv) 
{
    t_grille grille;

    chargerGrille(argv, grille);

    return maStrategie(grille);
}

// Charge la grille du tour actuel
// Vous n'avez pas à modifier cette fonction
void chargerGrille(char** argv, t_grille grille) 
{
    for(int i = 0; i < LIGNE; i++)
        for(int j = 0; j < COLONNE; j++)
            grille[i][j] = atoi(argv[i * COLONNE + j + 1]);
}
