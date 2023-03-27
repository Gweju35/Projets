#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//////////////////////////////////
// DEBUT DE L'IA A LA LIGNE 302 //
//////////////////////////////////

///////////////////////////////////////////////////////////////
// faireJouerB modifié à la ligne 162, pour faire jouer l'IA //
///////////////////////////////////////////////////////////////

// les defines & constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'O'
#define PION_B 'X'
#define VIDE ' '
#define INCONNU ' '
#define LONGUEUR_PUISSANCE4 4 // Equivaut à 4 pions alignés
const int COLONNE_DEBUT = NB_COLONNES / 2;

// les types
typedef int Grille[NB_LIGNES][NB_COLONNES];

// entêtes des procédures & fonctions
void initGrille(Grille);
void afficher(Grille, char);
bool grillePleine(Grille);
void faireJouerA(Grille, char, int *, int *);
void faireJouerB(Grille, char, int *, int *);
int choisirColonne(Grille, char);
int chercherLigne(Grille, int);
bool estVainqueur(Grille, int, int);
void finDePartie(char);

// entêtes des procédures & fonctions utilisées pour l'IA
void joue_le_coup(int, bool, Grille);
int minimax(int, Grille, bool, int, int);
int evaluation_de_la_grille(char[]);
int evaluation_heuristique(Grille);
int estVainqueur2(Grille);
bool coup_valide(int, Grille);
void copie_grille(Grille, Grille);
int minimum(int, int);
int maximum(int, int);

// Variable globale (renvoie la meilleure colonne, pour l'IA)
int IA_meilleur_coup;

// Programme principal. C'est le pion A qui commence à jouer
int main()
{
	Grille laGrille;
	char vainqueur = INCONNU;
	int ligne, colonne;
	initGrille(laGrille);
	afficher(laGrille, PION_B);
	while (vainqueur == INCONNU && !grillePleine(laGrille))
	{
		faireJouerA(laGrille, PION_B, &ligne, &colonne);
		afficher(laGrille, PION_A);
		if (estVainqueur(laGrille, ligne, colonne))
		{
			vainqueur = PION_B;
		}
		else if (!grillePleine(laGrille))
		{
			faireJouerB(laGrille, PION_A, &ligne, &colonne);
			afficher(laGrille, PION_B);
			if (estVainqueur(laGrille, ligne, colonne))
			{
				vainqueur = PION_A;
			}
		}
	}
	finDePartie(vainqueur);
	system(EXIT_SUCCESS);
}

void initGrille(Grille laGrille)
{
	int ligne, colonne;
	for (ligne = 0; ligne < NB_LIGNES; ligne++)
	{
		for (colonne = 0; colonne < NB_COLONNES; colonne++)
		{
			laGrille[ligne][colonne] = VIDE;
		}
	}
}

void afficher(Grille laGrille, char pion)
{
	int l, c;
	system("cls"); // changer en "clear" sur Linux
	printf("\t");
	printf("  %c\n", pion);
	printf("\t\xDA");
	for (c = 0; c < NB_COLONNES - 1; c++)
	{
		printf("\xC4\xC4\xC4\xC2");
	}
	printf("\xC4\xC4\xC4\xBF\n");
	for (l = 0; l < NB_LIGNES - 1; l++)
	{
		printf("\t");
		for (c = 0; c < NB_COLONNES; c++)
		{
			printf("\xB3 %c ", laGrille[l][c]);
		}
		printf("\xB3\n");
		printf("\t\xC3");
		for (c = 0; c < NB_COLONNES - 1; c++)
		{
			printf("\xC4\xC4\xC4\xC5");
		}
		printf("\xC4\xC4\xC4\xB4\n");
	}
	printf("\t");
	for (c = 0; c < NB_COLONNES; c++)
	{
		printf("\xB3 %c ", laGrille[l][c]);
	}
	printf("\xB3\n");
	printf("\t\xC0");
	for (c = 0; c < NB_COLONNES - 1; c++)
	{
		printf("\xC4\xC4\xC4\xC1");
	}
	printf("\xC4\xC4\xC4\xD9\n");
	printf("\t");
	for (c = 0; c < NB_COLONNES; c++)
	{
		printf("  %d ", c);
	}
	printf("\n\n");
}

bool grillePleine(Grille laGrille)
{
	bool plein = true;
	int c = 0;
	while (plein && c < NB_COLONNES)
	{
		if (laGrille[0][c] == VIDE)
		{
			plein = false;
		}
		c++;
	}
	return plein;
}

void faireJouerA(Grille laGrille, char pion, int *ligne, int *colonne)
{
	*ligne = -1;
	do
	{
		*colonne = choisirColonne(laGrille, pion);
		*ligne = chercherLigne(laGrille, *colonne);
	} while (*ligne == -1);
	laGrille[*ligne][*colonne] = pion;
}

void faireJouerB(Grille laGrille, char pion, int *ligne, int *colonne)
{
	int coups_futur = 7; // Nombre de coup où l'IA peut voir dans le futur :: Plus on augmente le nombre plus l'algo est lent
	int alpha = -1000000;
	int beta = 1000000;
	*ligne = -1;
	do
	{
		minimax(coups_futur, laGrille, true, alpha, beta); // L'IA permet de donner la meilleure colonne possible
		*colonne = IA_meilleur_coup;
		*ligne = chercherLigne(laGrille, *colonne);
	} while (*ligne == -1);
	laGrille[*ligne][*colonne] = pion;
}

int choisirColonne(Grille laGrille, char pion)
{
	int col;
	do
	{
		printf("Numero de colonne ? ");
		scanf("%d", &col);
		if (col < 0 || col > 6)
		{
			printf("Colonne invalide, choisissez dans l'intervalle [0-6].");
		}
	} while (col < 0 || col > 6);
	return col;
}

int chercherLigne(Grille laGrille, int col)
{
	int ligne = -1;
	while (ligne < NB_LIGNES - 1 && laGrille[ligne + 1][col] == VIDE)
	{
		ligne++;
	}
	return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col)
{
	// consiste à regarder si une ligne de 4 pions s'est formée autour du pion qui vient de tomber en (lig, col)
	char lePion = laGrille[lig][col];
	int cpt, i, j;

	// regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
	i = lig;
	cpt = 0;
	while (i < NB_LIGNES && laGrille[i][col] == lePion)
	{
		cpt++;
		i++;
	}
	if (cpt >= 4)
	{
		return true;
	}
	// regarder l'horizontale, en comptant le nombre de pions à l'Est et à l'Ouest
	j = col;
	cpt = 0;
	// on regarde à l'est
	while (j >= 0 && laGrille[lig][j] == lePion)
	{
		cpt++;
		j--;
	}
	j = col + 1;
	// on regarde à l'ouest
	while (j < NB_COLONNES && laGrille[lig][j] == lePion)
	{
		cpt++;
		j++;
	}
	if (cpt >= 4)
	{
		return true;
	}
	// regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
	i = lig;
	j = col;
	cpt = 0;
	// on regarde au Nord Ouest
	while (j >= 0 && i >= 0 && laGrille[i][j] == lePion)
	{
		cpt++;
		i--;
		j--;
	}
	i = lig + 1;
	j = col + 1;
	// on regarde au Sud Est
	while (i < NB_LIGNES && j < NB_COLONNES && laGrille[i][j] == lePion)
	{
		cpt++;
		i++;
		j++;
	}
	if (cpt >= 4)
	{
		return true;
	}
	// regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
	i = lig;
	j = col;
	cpt = 0;
	// on regarde au Nord Est
	while (j < NB_COLONNES && i >= 0 && laGrille[i][j] == lePion)
	{
		cpt++;
		i--;
		j++;
	}
	i = lig + 1;
	j = col - 1;
	// on regarde au Sud Ouest
	while (i < NB_LIGNES && j < NB_COLONNES && laGrille[i][j] == lePion)
	{
		cpt++;
		i++;
		j--;
	}
	if (cpt >= 4)
	{
		return true;
	}
	return false;
}

void finDePartie(char vainqueur)
{
	if (vainqueur != INCONNU)
	{
		printf("Joueur %c vainqueur\n", vainqueur);
	}
	else
	{
		printf("MATCH NUL");
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// DEBUT DE L'IA ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int minimax(int profondeur, Grille laGrille, bool joueur, int alpha, int beta)
{
	Grille nouvelle_grille; // copie de la grille de jeu actuelle
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
		for (colonne = 0; colonne < NB_COLONNES; colonne++)
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
		for (colonne = 0; colonne < NB_COLONNES; colonne++)
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
void joue_le_coup(int colonne, bool joueur, Grille grille)
{
	int ligne = 0;
	for (ligne = NB_LIGNES - 1; ligne >= 0; ligne--)
	{
		if (grille[ligne][colonne] == VIDE)
		{
			if (joueur)
			{
				grille[ligne][colonne] = PION_A;
				break;
			}
			else
			{
				grille[ligne][colonne] = PION_B;
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
int estVainqueur2(Grille tableau)
{
	int ligne, colonne;
	int gagnant = 0; // pas de gagnant pour l'instant

	// Vérifie s'il y a un alignement de 4 pions à la verticale
	for (ligne = NB_LIGNES - 1; ligne >= NB_LIGNES - 3; ligne--)
	{
		for (colonne = 0; colonne < NB_COLONNES; colonne++)
		{
			if (tableau[ligne][colonne] == PION_B && tableau[ligne - 1][colonne] == PION_B && tableau[ligne - 2][colonne] == PION_B && tableau[ligne - 3][colonne] == PION_B)
			{
				gagnant = 1;
			}
			else if (tableau[ligne][colonne] == PION_A && tableau[ligne - 1][colonne] == PION_A && tableau[ligne - 2][colonne] == PION_A && tableau[ligne - 3][colonne] == PION_A)
			{
				gagnant = 2;
			}
		}
	}

	// Vérifie s'il y a un alignement de 4 pions à l'horizontal
	for (ligne = NB_LIGNES - 1; ligne >= 0; ligne--)
	{
		for (colonne = 0; colonne < 4; colonne++)
		{
			if (tableau[ligne][colonne] == PION_B && tableau[ligne][colonne + 1] == PION_B && tableau[ligne][colonne + 2] == PION_B && tableau[ligne][colonne + 3] == PION_B)
			{
				gagnant = 1;
			}
			else if (tableau[ligne][colonne] == PION_A && tableau[ligne][colonne + 1] == PION_A && tableau[ligne][colonne + 2] == PION_A && tableau[ligne][colonne + 3] == PION_A)
			{
				gagnant = 2;
			}
		}
	}

	// Vérifie s'il y a un alignement de 4 pions en diagonale ascendante
	for (ligne = NB_LIGNES - 1; ligne >= NB_LIGNES - 3; ligne--)
	{
		for (colonne = 0; colonne < 4; colonne++)
		{
			if (tableau[ligne][colonne] == PION_B && tableau[ligne - 1][colonne + 1] == PION_B && tableau[ligne - 2][colonne + 2] == PION_B && tableau[ligne - 3][colonne + 3] == PION_B)
			{
				gagnant = 1;
			}
			else if (tableau[ligne][colonne] == PION_A && tableau[ligne - 1][colonne + 1] == PION_A && tableau[ligne - 2][colonne + 2] == PION_A && tableau[ligne - 3][colonne + 3] == PION_A)
			{
				gagnant = 2;
			}
		}
	}

	// Vérifie s'il y a un alignement de 4 pions en diagonale descendante
	for (ligne = NB_LIGNES - 1; ligne >= NB_LIGNES - 3; ligne--)
	{
		for (colonne = 3; colonne < NB_COLONNES; colonne++)
		{
			if (tableau[ligne][colonne] == PION_B && tableau[ligne - 1][colonne - 1] == PION_B && tableau[ligne - 2][colonne - 2] == PION_B && tableau[ligne - 3][colonne - 3] == PION_B)
			{
				gagnant = 1;
			}
			else if (tableau[ligne][colonne] == PION_A && tableau[ligne - 1][colonne - 1] == PION_A && tableau[ligne - 2][colonne - 2] == PION_A && tableau[ligne - 3][colonne - 3] == PION_A)
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
		if (grille[i] == PION_A)
		{
			pion++;
		}
		else if (grille[i] == VIDE)
		{
			vide++;
		}
		else if (grille[i] == PION_B)
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
int evaluation_heuristique(Grille laGrille)
{
	int score = 0;
	int ligne, colonne, i;
	char grille[LONGUEUR_PUISSANCE4];
	char grille2[LONGUEUR_PUISSANCE4];
	char ligne_grille[NB_COLONNES];
	char colonne_grille[NB_LIGNES];
	char diagonale_ascendante[LONGUEUR_PUISSANCE4];
	char diagonale_descendante[LONGUEUR_PUISSANCE4];

	// Le score de la colonne centrale
	for (ligne = 0; ligne < NB_LIGNES; ligne++)
	{
		if (laGrille[ligne][COLONNE_DEBUT] == PION_A)
		{
			score = score + 3;
		}
	}

	// Score à l'horizontal
	for (ligne = NB_LIGNES - 1; ligne >= 0; ligne--)
	{
		// On regarde toutes les lignes, une par une
		for (colonne = 0; colonne < NB_COLONNES; colonne++)
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
	for (colonne = 0; colonne < NB_COLONNES; colonne++)
	{
		// On regarde toutes les colonnes, une par une
		for (ligne = 0; ligne < NB_LIGNES; ligne++)
		{
			colonne_grille[ligne] = laGrille[ligne][colonne];
		}
		// Compare 4 pions de chaque colonne à la fois
		for (ligne = NB_LIGNES - 1; ligne >= 3; ligne--)
		{
			for (i = 0; i < LONGUEUR_PUISSANCE4; i++)
			{
				grille2[i] = colonne_grille[i + ligne];
			}
			score = score + evaluation_de_la_grille(grille2);
		}
	}

	// Score diagonale ascendante
	for (ligne = NB_LIGNES - 1; ligne >= 3; ligne--)
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
	for (ligne = NB_LIGNES - 1; ligne >= 3; ligne--)
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
bool coup_valide(int colonne, Grille tableau)
{
	bool valide = false;
	int ligne;
	for (ligne = NB_LIGNES - 1; ligne >= 0; ligne--)
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
void copie_grille(Grille tableau, Grille tmp_grille)
{
	int ligne = 0, colonne = 0;
	for (ligne = 0; ligne < NB_LIGNES; ligne++)
	{
		for (colonne = 0; colonne < NB_COLONNES; colonne++)
		{
			tmp_grille[ligne][colonne] = tableau[ligne][colonne];
		}
	}
}