# Import nécessaire pour la programmation du jeu
import random
from random import choice
import sys
import pygame
from pygame.locals import *

# Initialisation de la bibliothèque Pygame
pygame.init()
# Création de la fenêtre Pygame
fenetre = pygame.display.set_mode((640, 480), RESIZABLE)

# Initilisation de toutes les images nécessaires pour le jeu
Image_Accueil = pygame.image.load("Images/Accueil-Bienvenue.png").convert()    # Accueil
Image_Accueillancement = pygame.image.load("Images/Accueil-Lancement.png").convert()  # Règles du jeu
Image_Accueiln1 = pygame.image.load("Images/Accueil-Numero1.png").convert()  # Bonne Chance!
Image_Choixlettres = pygame.image.load("Images/Choix-Lettres.png").convert()  # Choix des consonnes ou des voyelles
Image_Motjoueur1 = pygame.image.load("Images/Mot-Joueur1.png").convert()  # J1 joue
Image_Motjoueur2 = pygame.image.load("Images/Mot-joueur2.png").convert()  # J2 joue
Image_Victoirejoueur1 = pygame.image.load("Images/Victoire-Joueur1.png").convert()  # Victoire de J1
Image_Victoirejoueur2 = pygame.image.load("Images/Victoire-Joueur2.png").convert()  # Victoire de J2
Image_Egalitejoueur = pygame.image.load("Images/Egalite-Joueur.png").convert() # Egalité 


# Création des définitions pour le programme
def diff_mots_sur_tirage(mot, tirage_trier):  # diff = différents
    mot = sorted(mot)
    p, n = 0, 0
    while p < len(mot) and n < len(tirage_trier):
        if (mot[p] == tirage_trier[n]):
            p += 1
            n += 1
        elif (mot[p] < tirage_trier[n]):
            return False
        else:
            n += 1
    if p == len(mot):
        return True
    else:
        return False

def recherche_tirage_i_lettres(tirage, liste_mots_de_i_lettres):
    resultat = []
    tirage_trier = sorted(tirage)
    for mot in liste_mots_de_i_lettres:
        if diff_mots_sur_tirage(mot, tirage_trier):
            resultat.append(mot)
    return resultat

def filtre_de_mots_de_i_lettres(liste, i):
    return [mots for mots in liste if len(mots)-mots.count('-') == i]

def creation_de_la_liste_de_mots(fichier):
    f = open(fichier, "r")
    jal = f.readlines()
    liste_mots = []
    for i in jal:
        liste_mots.append(i[:-1].upper())
    return liste_mots

# Initialisation de la police et des caractères
Police_1 = pygame.font.Font(None, 35)
Caractere1 = pygame.font.Font(None, 45)
Caractere2 = pygame.font.Font(None, 80)
Texte_2 = Caractere1.render("Consonne", True, pygame.Color("white"))
Texte_1 = Caractere1.render("Voyelle", True, pygame.Color("white"))
Texte_4 = Caractere2.render("X", True, pygame.Color("white"))


# Initialisation des variables
Voyelle = ["A", "E", "I", "O", "U", "Y"]
Consonne = ["B", "C", "D", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "V", "W", "X", "Z"]
liste_de_mots = creation_de_la_liste_de_mots("liste_finale.txt") # Création du "dictionnaire"
Ordonnée_1 = 220
Ordonnée_2 = 220
Ordonnée_3 = 210
Ordonnée_4 = 210
Accueil_1 = 0
Accueil_2 = 0
Accueil_3 = 0
Joueur_N1 = 0
Joueur_N2 = 0
JN1 = 0
JN2 = 0
word1 = []
word2 = []
tirage = []
Game = 0
Game_2 = 0
Game_3 = 0
First_Screen = 0
Second_Screen = 0
infini = 0
FS1 = 0
SS2 = 0
End = 0
Choix = 0
a = 0
b = 0
x = 0
y = 0
z = 0

# Programme:
while infini == 0:
    while Accueil_1 == 0:
        for event in pygame.event.get():
            # L'image "Accueil-Bienvenue" apparaît à l'écran
            fenetre.blit(Image_Accueil, (0, 0))
            pygame.display.flip()  # Rafraichissement de l'image
            if event.type == KEYDOWN:
                if event.key == K_SPACE:  # Touche Espace
                    Accueil_1 = 1
                    Accueil_2 = 1
            if event.type == QUIT:  # Pour pouvoir quitter le jeu à tout moment
                pygame.quit()
                infini = 1
    while Accueil_3 == 0:
        for event in pygame.event.get():
            fenetre.blit(Image_Accueillancement, (0, 0))
            pygame.display.flip()
            if event.type == KEYDOWN:
                if event.key == K_RETURN:  # Touche Entrée
                    Accueil_3 = 1
            if event.type == QUIT:
                pygame.quit()
                infini = 1
    while Accueil_2 == 1:
        fenetre.blit(Image_Accueiln1, (0, 0))
        pygame.display.flip()
        if event.type == QUIT:
            pygame.quit()
            infini = 1
        for event in pygame.event.get():
            if event.type == KEYDOWN:
                while Choix == 0:
                    if event.type == KEYDOWN:
                        if event.key == K_RETURN:  # Touche Entrée
                            Choix = 1
                            Accueil_2 = 0
                            First_Screen = 1
                            Second_Screen = 1
                            Game = 1
    while Game == 1:
        tirage = []
        nb_voyelle = 0
        nb_consonne = 0
        fenetre.blit(Image_Choixlettres, (0, 0))
        pygame.display.flip()
        while a == 1:
            for i in range(9):
                a = input("C or V ?\n=> ").upper()
                print(a)
                if a == "C" or "V":
                    if a == "C":
                        tirage.append(random.choice(Consonne))
                        nb_consonne += 1
                    if a == "V":
                        tirage.append(random.choice(Voyelle))
                        nb_voyelle += 1
            b = 1
            a = 0
            End = 1
        while First_Screen == 1:
            while FS1 == 0:
                fenetre.blit(Image_Choixlettres, (0, 0))
                pygame.display.flip()
                FS1 = 1
            if event.type == QUIT:
                pygame.quit()
                infini = 1
            event = pygame.event.wait()
            if nb_consonne+nb_voyelle == 9:
                End = 1
                First_Screen = 0
            if event.type == KEYDOWN:
                if event.key == K_c:
                    nb_consonne += 1
                    tirage.append(random.choice(Consonne))
                    fenetre.blit(Texte_2, (80, Ordonnée_1))
                    Ordonnée_1 += 30  # Contrôle l'espacement du mot "Consonne" entre les autres "Consonne"
                    pygame.display.flip()
                elif event.key == K_v:
                    tirage.append(random.choice(Voyelle))
                    nb_voyelle += 1
                    # Contrôle l'espacement du mot "Voyelle" entre les autres "Voyelle"
                    fenetre.blit(Texte_1, (365, Ordonnée_2))
                    Ordonnée_2 += 30
                    pygame.display.flip()
                elif not event.key == K_c or event.key == K_c:
                    pygame.quit()
        while End == 1:
            if int(nb_voyelle) < 2:
                sys.exit()
            if int(nb_consonne) + int(nb_voyelle) < 9:
                sys.exit()  
                # INFORMATION IMPORTANTE: Je n'ai pas réussi à trouver un moyen pour revenir à la page précédente, 
                # s'il n'y a pas assez de voyelles ou trop de consonnes. Du coup cela résulte à un crash du jeu, 
                # il faut donc fermer la fenêtre et relancer le jeu
            while b == 1:
                print("Insertion des mots")
                word1 = input("\nICI, Joueur N°1\n=>").upper()
                word2 = input("\nICI, Joueur N°2\n=>").upper()
                b = 0
                lettres_mot_1 = sorted(word1.upper())
                lettres_mot_2 = sorted(word2.upper())
                print(word1)
                print(word2)
            Tirage = ""
            Tirage = ",".join(tirage)
            while Second_Screen == 1:
                while SS2 == 0:
                    Texte_3 = Police_1.render(
                        Tirage, True, pygame.Color("white"))
                    fenetre.blit(Image_Motjoueur1, (0, 0))
                    pygame.display.flip()
                    fenetre.blit(Texte_3, (420, 78))
                    pygame.display.flip()
                    SS2 = 1
                if event.type == QUIT:
                    pygame.quit()
                    infini = 1
                while Joueur_N1 == 0:
                    while JN1 == 0:
                        JN1 = 1
                    for event in pygame.event.get():
                        if event.type == QUIT:
                            pygame.quit()
                            infini = 1
                        if event.type == KEYDOWN:
                            if event.key == K_RETURN:
                                Joueur_N2 = 1
                                Joueur_N1 = 1
                            else:
                                # Cette partie-ci permet de cacher le mot, comme ceci les 2 Joueurs ne peuvent pas voir le mot de l'autre, avec l'aide du "Texte_3"
                                fenetre.blit(Texte_4, (Ordonnée_3, 300))
                                Ordonnée_3 += 45
                                pygame.display.flip()
                                lettre = event.unicode.upper()
                                word1.append(lettre)
                while Joueur_N2 == 1:
                    while JN2 == 0:
                        fenetre.blit(Image_Motjoueur2, (0, 0))
                        pygame.display.flip()
                        fenetre.blit(Texte_3, (420, 78))
                        pygame.display.flip()
                        JN2 = 1
                    for event in pygame.event.get():
                        if event.type == QUIT:
                            pygame.quit()
                            infini = 1
                        if event.type == KEYDOWN:
                            if event.key == K_RETURN:
                                Joueur_N2 = 0
                            else:
                                fenetre.blit(Texte_4, (Ordonnée_4, 300))
                                Ordonnée_4 += 45
                                pygame.display.flip()
                                lettre = event.unicode.upper()
                                word2.append(lettre)
                lettres_word_1 = word1
                lettres_word_2 = word2
                word1 = "".join(word1)
                word2 = "".join(word2)
                Second_Screen = 0
            print(word1)
            print(word2)
            tirage_1 = []
            tirage_2 = []
            check_1 = []
            check_2 = []
            for a in tirage:
                tirage_1.append(a)
            for a in tirage:
                tirage_2.append(a)
            if (word1 in liste_de_mots) and (word2 in liste_de_mots):
                for a in lettres_word_1:  # Insertion Mot Joueur N°1
                    if a in tirage_1:
                        check_1.append(a)
                        tirage_1.remove(a)
                    else:
                        sys.exit(
                            "Error: Les lettres tirées au sort n'ont pas été utilisée.")
                for a in lettres_word_2:  # Insertion Mot Joueur N°2
                    if a in tirage_2:
                        check_2.append(a)
                        tirage_2.remove(a)
                    else:
                        sys.exit(
                            "Error: Les lettres tirées au sort n'ont pas été utilisée.")
                L_Mot_1_lettre = filtre_de_mots_de_i_lettres(liste_de_mots, 1)
                L_Mot_2_lettres = filtre_de_mots_de_i_lettres(liste_de_mots, 2)
                L_Mot_3_lettres = filtre_de_mots_de_i_lettres(liste_de_mots, 3)
                L_Mot_4_lettres = filtre_de_mots_de_i_lettres(liste_de_mots, 4)
                L_Mot_5_lettres = filtre_de_mots_de_i_lettres(liste_de_mots, 5)
                L_Mot_6_lettres = filtre_de_mots_de_i_lettres(liste_de_mots, 6)
                L_Mot_7_lettres = filtre_de_mots_de_i_lettres(liste_de_mots, 7)
                L_Mot_8_lettres = filtre_de_mots_de_i_lettres(liste_de_mots, 8)
                L_Mot_9_lettres = filtre_de_mots_de_i_lettres(liste_de_mots, 9)
                
                liste_resultat_1 = recherche_tirage_i_lettres(
                    tirage, L_Mot_1_lettre)
                liste_resultat_2 = recherche_tirage_i_lettres(
                    tirage, L_Mot_2_lettres)
                liste_resultat_3 = recherche_tirage_i_lettres(
                    tirage, L_Mot_3_lettres)
                liste_resultat_4 = recherche_tirage_i_lettres(
                    tirage, L_Mot_4_lettres)
                liste_resultat_5 = recherche_tirage_i_lettres(
                    tirage, L_Mot_5_lettres)
                liste_resultat_6 = recherche_tirage_i_lettres(
                    tirage, L_Mot_6_lettres)
                liste_resultat_7 = recherche_tirage_i_lettres(
                    tirage, L_Mot_7_lettres)
                liste_resultat_8 = recherche_tirage_i_lettres(
                    tirage, L_Mot_8_lettres)
                liste_resultat_9 = recherche_tirage_i_lettres(
                    tirage, L_Mot_9_lettres)

                if len(liste_resultat_1) > 0:
                    nbre_lettres_maximum = 1
                elif len(liste_resultat_2) > 0:
                    nbre_lettres_maximum = 2
                elif len(liste_resultat_3) > 0:
                    nbre_lettres_maximum = 3
                elif len(liste_resultat_4) > 0:
                    nbre_lettres_maximum = 4
                elif len(liste_resultat_5) > 0:
                    nbre_lettres_maximum = 5
                elif len(liste_resultat_6) > 0:
                    nbre_lettres_maximum = 6
                elif len(liste_resultat_7) > 0:
                    nbre_lettres_maximum = 7
                elif len(liste_resultat_8) > 0:
                    nbre_lettres_maximum = 8
                elif len(liste_resultat_9) > 0:
                    nbre_lettres_maximum = 9

                i = 1
                while i == 1:
                    if nbre_lettres_maximum == 1:
                        mot_max = liste_resultat_1
                        i = 0
                    elif nbre_lettres_maximum == 2:
                        mot_max = liste_resultat_2
                        i = 0
                    elif nbre_lettres_maximum == 3:
                        mot_max = liste_resultat_3
                        i = 0
                    elif nbre_lettres_maximum == 4:
                        mot_max = liste_resultat_4
                        i = 0
                    elif nbre_lettres_maximum == 5:
                        mot_max = liste_resultat_5
                        i = 0
                    elif nbre_lettres_maximum == 6:
                        mot_max = liste_resultat_6
                        i = 0
                    elif nbre_lettres_maximum == 7:
                        mot_max = liste_resultat_7
                        i = 0
                    elif nbre_lettres_maximum == 8:
                        mot_max = liste_resultat_8
                        i = 0
                    elif nbre_lettres_maximum == 9:
                        mot_max = liste_resultat_9
                        i = 0
            else:
                sys.exit()
            if len(word1) > len(word2):
                # Victoire Joueur N°1
                fenetre.blit(Image_Victoirejoueur1, (0, 0))
                pygame.display.flip()
                pygame.time.delay(3000)
                pygame.quit()
                sys.exit()
            elif len(word1) < len(word2):
                # Victoire Joueur N°2
                fenetre.blit(Image_Victoirejoueur2, (0, 0))
                pygame.display.flip()
                pygame.time.delay(3000)
                pygame.quit()
                sys.exit()
            else:
                # Egalité entre les Joueurs
                fenetre.blit(Image_Egalitejoueur, (0, 0))
                pygame.display.flip()
                pygame.time.delay(3000)
                pygame.quit()
                sys.exit()