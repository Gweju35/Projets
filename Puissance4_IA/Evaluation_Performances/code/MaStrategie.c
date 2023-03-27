#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LIGNE 6
#define COLONNE 7
#define LONGUEUR_PUISSANCE4 4 // Equivaut à 4 pions alignés
const int COLONNE_DEBUT = (COLONNE / 2);
const int VIDE = 0;
const int JOUEUR = 1;
const int ADVERSAIRE = 2;

typedef int t_grille[LIGNE][COLONNE];

int main(int argc, char **argv);
void chargerGrille(char **argv, t_grille grille);
void joue_le_coup(int, bool, t_grille);
int minimax(int, t_grille, bool, int, int);
int evaluation_de_la_grille(char[]);
int evaluation_heuristique(t_grille);
int estVainqueur2(t_grille);
bool coup_valide(int, t_grille);
void copie_grille(t_grille, t_grille);
int minimum(int, int);
int maximum(int, int);

int IA_meilleur_coup;

/*
 * VOTRE STRATEGIE
 */
int maStrategie(t_grille grille)
{
	// La variable grille est un tableau à deux dimensions d'entiers, c'est la grille du tour.
	// Un VIDE représente une case vide, 1 représente vos jetons et 2 représente les jetons adverses.
	// A vous de choisir le meilleur prochain coup
	int colonne;
	int coups_futur = 7; // Nombre de coup où l'IA peut voir dans le futur :: Plus on augmente le nombre plus l'algo est lent
	int alpha = -1000000;
	int beta = 1000000;
	minimax(coups_futur, grille, true, alpha, beta); // L'IA permet de donner la meilleure colonne possible
	colonne = IA_meilleur_coup;
	return colonne;
}

// La fonction principale reçoit la grille du tour et retourne le coup choisi
// Vous n'avez pas à modifier cette fonction
int main(int argc, char **argv)
{
	t_grille grille;

	chargerGrille(argv, grille);

	return maStrategie(grille);
}

// Charge la grille du tour actuel
// Vous n'avez pas à modifier cette fonction
void chargerGrille(char **argv, t_grille grille)
{
	for (int i = 0; i < LIGNE; i++)
		for (int j = 0; j < COLONNE; j++)
			grille[i][j] = atoi(argv[i * COLONNE + j + 1]);
}

int minimax(int profondeur, t_grille laGrille, bool joueur, int alpha, int beta)
{
	t_grille nouvelle_grille; // copie de la grille de jeu actuelle
	int valeur, best_valeur, meilleur_coup;
	int gagnant = estVainqueur2(laGrille); // renvoie 1 si 4 'X' alignés, renvoie 2 si 4 'O' alignés, renvoie 0 si pas encore de gagnant
	int colonne = 0;
	if ((profondeur == 0) || (gagnant != 0))
	{
		if (profondeur == 0)
		{
			return evaluation_heuristique(laGrille);
		}
		else if (gagnant != 0)
		{
			if (gagnant == 2)
			{
				return (1000000);
			}
			else if (gagnant == 1)
			{
				return (-1000000);
			}
		}
	}
	// On maximise le score (pour l'IA)
	if (joueur == true)
	{
		best_valeur = -10000;
		meilleur_coup = 1;
		for (colonne = 0; colonne < COLONNE; colonne++)
		{
			copie_grille(laGrille, nouvelle_grille);   // Copie la grille de jeu
			if (coup_valide(colonne, nouvelle_grille)) // On vérifie si la colonne selectionnée est remplie ou pas (coup valide ou pas)
			{
				joue_le_coup(colonne, joueur, nouvelle_grille); // On joue un coup dans la copie de la grille
				valeur = minimax(profondeur - 1, nouvelle_grille, false, alpha, beta);
				if (valeur > best_valeur)
				{
					best_valeur = valeur;
					meilleur_coup = colonne;
				}
				alpha = maximum(alpha, best_valeur); // Renvoie le maximum des 2 valeurs
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		IA_meilleur_coup = meilleur_coup; // La variable globale prend la meilleure colonne trouvée
		return best_valeur;
	}
	// On minimise le score (pour l'adversaire)
	else
	{
		best_valeur = 10000;
		for (colonne = 0; colonne < COLONNE; colonne++)
		{
			copie_grille(laGrille, nouvelle_grille);   // Copie la grille de jeu
			if (coup_valide(colonne, nouvelle_grille)) // On vérifie si la colonne selectionnée est remplie ou pas (coup valide ou pas)
			{
				joue_le_coup(colonne, joueur, nouvelle_grille); // On joue un coup dans la copie de la grille
				valeur = minimax(profondeur - 1, nouvelle_grille, true, alpha, beta);
				best_valeur = minimum(valeur, best_valeur); // Renvoie le minimum des 2 valeurs
				beta = minimum(beta, best_valeur);			// Renvoie le minimum des 2 valeurs
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		return best_valeur;
	}
}

// Joue un coup (le coup joué n'est pas "réel", il n'interfère pas dans la grille de jeu, mais seulement dans sa copie)
void joue_le_coup(int colonne, bool joueur, t_grille grille)
{
	int ligne = 0;
	for (ligne = LIGNE - 1; ligne >= 0; ligne--)
	{
		if (grille[ligne][colonne] == VIDE)
		{
			if (joueur)
			{
				grille[ligne][colonne] = JOUEUR;
				break;
			}
			else
			{
				grille[ligne][colonne] = ADVERSAIRE;
				break;
			}
		}
	}
}

/* Seconde version de la fonction 'estVainqueur.
La première fonction 'estVainqueur' recherchait un gagnant en se basant sur le dernier pion joué.
'estVainqueur2' permet de vérifier s'il y a un vainqueur, en se basant sur tous les pions joués.
Cette fonction est utilisée dans 'minimax', quand cette dernière prédit les coups prochains, elle verifie également
s'il n'y aura pas un gagnant après un certains nombre de coups, grâce à 'estVainqueur2'. */
int estVainqueur2(t_grille tableau)
{
	int ligne, colonne;
	int gagnant = 0; // pas de gagnant pour l'instant

	// Vérifie s'il y a un alignement de 4 pions à la verticale
	for (ligne = LIGNE - 1; ligne >= LIGNE - 3; ligne--)
	{
		for (colonne = 0; colonne < COLONNE; colonne++)
		{
			if (tableau[ligne][colonne] == ADVERSAIRE && tableau[ligne - 1][colonne] == ADVERSAIRE && tableau[ligne - 2][colonne] == ADVERSAIRE && tableau[ligne - 3][colonne] == ADVERSAIRE)
			{
				gagnant = 1;
			}
			else if (tableau[ligne][colonne] == JOUEUR && tableau[ligne - 1][colonne] == JOUEUR && tableau[ligne - 2][colonne] == JOUEUR && tableau[ligne - 3][colonne] == JOUEUR)
			{
				gagnant = 2;
			}
		}
	}

	// Vérifie s'il y a un alignement de 4 pions à l'horizontal
	for (ligne = LIGNE - 1; ligne >= 0; ligne--)
	{
		for (colonne = 0; colonne < 4; colonne++)
		{
			if (tableau[ligne][colonne] == ADVERSAIRE && tableau[ligne][colonne + 1] == ADVERSAIRE && tableau[ligne][colonne + 2] == ADVERSAIRE && tableau[ligne][colonne + 3] == ADVERSAIRE)
			{
				gagnant = 1;
			}
			else if (tableau[ligne][colonne] == JOUEUR && tableau[ligne][colonne + 1] == JOUEUR && tableau[ligne][colonne + 2] == JOUEUR && tableau[ligne][colonne + 3] == JOUEUR)
			{
				gagnant = 2;
			}
		}
	}

	// Vérifie s'il y a un alignement de 4 pions en diagonale ascendante
	for (ligne = LIGNE - 1; ligne >= LIGNE - 3; ligne--)
	{
		for (colonne = 0; colonne < 4; colonne++)
		{
			if (tableau[ligne][colonne] == ADVERSAIRE && tableau[ligne - 1][colonne + 1] == ADVERSAIRE && tableau[ligne - 2][colonne + 2] == ADVERSAIRE && tableau[ligne - 3][colonne + 3] == ADVERSAIRE)
			{
				gagnant = 1;
			}
			else if (tableau[ligne][colonne] == JOUEUR && tableau[ligne - 1][colonne + 1] == JOUEUR && tableau[ligne - 2][colonne + 2] == JOUEUR && tableau[ligne - 3][colonne + 3] == JOUEUR)
			{
				gagnant = 2;
			}
		}
	}

	// Vérifie s'il y a un alignement de 4 pions en diagonale descendante
	for (ligne = LIGNE - 1; ligne >= LIGNE - 3; ligne--)
	{
		for (colonne = 3; colonne < COLONNE; colonne++)
		{
			if (tableau[ligne][colonne] == ADVERSAIRE && tableau[ligne - 1][colonne - 1] == ADVERSAIRE && tableau[ligne - 2][colonne - 2] == ADVERSAIRE && tableau[ligne - 3][colonne - 3] == ADVERSAIRE)
			{
				gagnant = 1;
			}
			else if (tableau[ligne][colonne] == JOUEUR && tableau[ligne - 1][colonne - 1] == JOUEUR && tableau[ligne - 2][colonne - 2] == JOUEUR && tableau[ligne - 3][colonne - 3] == JOUEUR)
			{
				gagnant = 2;
			}
		}
	}
	return gagnant;
}

// On calcule le score possible, en évaluant les différents éléments
int evaluation_de_la_grille(char grille[])
{
	int i = 0, score = 0, pion = 0, adversaire = 0, vide = 0;
	for (i = 0; i < LONGUEUR_PUISSANCE4; i++)
	{
		if (grille[i] == JOUEUR)
		{
			pion++;
		}
		else if (grille[i] == VIDE)
		{
			vide++;
		}
		else if (grille[i] == ADVERSAIRE)
		{
			adversaire++;
		}
	}

	// Le score est proportionnel au nombre de pions
	if (pion == 4)
	{
		score = score + 100;
	}
	else if ((pion == 3) && (vide == 1))
	{
		score = score + 5;
	}
	else if ((pion == 2) && (vide == 2))
	{
		score = score + 2;
	}
	else if ((adversaire == 3) && (vide == 1))
	{
		score = score - 4;
	}
	return score;
}

// On calcule le score en évaluant les différentes positions des pions dans le jeu
// Cette fonction fait appel à 'evaluation_de_la_grille'
int evaluation_heuristique(t_grille laGrille)
{
	int score = 0;
	int ligne, colonne, i;
	char grille[LONGUEUR_PUISSANCE4];
	char grille2[LONGUEUR_PUISSANCE4];
	char ligne_grille[COLONNE];
	char colonne_grille[LIGNE];
	char diagonale_ascendante[LONGUEUR_PUISSANCE4];
	char diagonale_descendante[LONGUEUR_PUISSANCE4];

	// Le score de la colonne centrale
	for (ligne = 0; ligne < LIGNE; ligne++)
	{
		if (laGrille[ligne][COLONNE_DEBUT] == JOUEUR)
		{
			score = score + 3;
		}
	}

	// Score à l'horizontal
	for (ligne = LIGNE - 1; ligne >= 0; ligne--)
	{
		// On regarde toutes les lignes, une par une
		for (colonne = 0; colonne < COLONNE; colonne++)
		{
			ligne_grille[colonne] = laGrille[ligne][colonne];
		}
		// Comparer 4 pions de chaque ligne à la fois
		for (colonne = 0; colonne < 4; colonne++)
		{
			for (i = 0; i < LONGUEUR_PUISSANCE4; i++)
			{
				grille[i] = ligne_grille[i + colonne];
			}
			score = score + evaluation_de_la_grille(grille);
		}
	}

	// Score Vertical
	for (colonne = 0; colonne < COLONNE; colonne++)
	{
		// On regarde toutes les colonnes, une par une
		for (ligne = 0; ligne < LIGNE; ligne++)
		{
			colonne_grille[ligne] = laGrille[ligne][colonne];
		}
		// Compare 4 pions de chaque colonne à la fois
		for (ligne = LIGNE - 1; ligne >= 3; ligne--)
		{
			for (i = 0; i < LONGUEUR_PUISSANCE4; i++)
			{
				grille2[i] = colonne_grille[i + ligne];
			}
			score = score + evaluation_de_la_grille(grille2);
		}
	}

	// Score diagonale ascendante
	for (ligne = LIGNE - 1; ligne >= 3; ligne--)
	{
		// On regarde toutes les diagonales ascendantes, une par une
		for (colonne = 0; colonne < 4; colonne++)
		{
			// Compare 4 pions de chaque diagonale ascendante à la fois
			for (i = 0; i < LONGUEUR_PUISSANCE4; i++)
			{
				diagonale_ascendante[i] = laGrille[ligne - i][colonne + i];
			}
			score = score + evaluation_de_la_grille(diagonale_ascendante);
		}
	}

	// Score diagonale descendante
	for (ligne = LIGNE - 1; ligne >= 3; ligne--)
	{
		// On regarde toutes les diagonales descendantes, une par une
		for (colonne = 3; colonne < 7; colonne++)
		{
			// Compare 4 pions de chaque diagonale descendante à la fois
			for (i = 0; i < LONGUEUR_PUISSANCE4; i++)
			{
				diagonale_descendante[i] = laGrille[ligne - i][colonne + i];
			}
			score = score + evaluation_de_la_grille(diagonale_descendante);
		}
	}
	return score; // On retourne le score total obtenu
}

// Vérifie si le coup joué est valide (si la colonne est comprise entre 0 et 6, et si la colonne n'est pas complètement remplie)
bool coup_valide(int colonne, t_grille tableau)
{
	bool valide = false;
	int ligne;
	for (ligne = LIGNE - 1; ligne >= 0; ligne--)
	{
		if (tableau[ligne][colonne] == VIDE)
		{
			valide = true;
			break;
		}
	}
	return valide;
}

// Retourne le maximum de 2 variables
int maximum(int a, int b)
{
	if (a >= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// Retourne le minimum de 2 variables
int minimum(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// Copie la grille de jeu pour permettre à l'IA de prédire les coups, sans interférer sur la grille principale
void copie_grille(t_grille tableau, t_grille tmp_grille)
{
	int ligne = 0, colonne = 0;
	for (ligne = 0; ligne < LIGNE; ligne++)
	{
		for (colonne = 0; colonne < COLONNE; colonne++)
		{
			tmp_grille[ligne][colonne] = tableau[ligne][colonne];
		}
	}
}