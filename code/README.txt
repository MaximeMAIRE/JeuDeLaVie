Projet : Jeu_De_La_Vie

Ce programme contient toute les fonctionnalités des 5 premiers niveau du jeu de la vie.
Pour compiler ce programme en mode graphique : make
Pour compiler ce programme en mode Text : make MODE=Text
Pour suprimer tout les executables : make clean
Pour lancer le programme une fois compilé : bin/main <le nom d'une grille>
Par exemple : bin/main grilles/grille1.txt

Une fois le programme lancé:
- la touche entree permet de faire evoluer la grille.
- la touche n permet de charger une nouvelle grille(et supprime l'ancienne)
- la touche v active/desactive le mode vieillissement
- la touche c acrive/desactive le mode cyclique
- la touche o (en mode graphique) teste si la grille est oscillante