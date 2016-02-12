# Generate automatic layout Yacc Flex.

Program an compilator to generate automatic layout.

# 	AIDE POUR LANCER LE PROGRAMME	

Les prérequis techniques
========================


1 - La bibliothéque Libharu doit être disponible.

Site officiel : [Libharu]  (disponible pour linux, windows et Mac)

Installation de la bibliothéque
===============================

Nous allons clonner le dossier libharu sur notre machine à partir de Github.

	Commande 1 : git clone https://github.com/libharu/libharu.git  
	------------
	Commande 2 : cd libharu 
	------------
	Commande 3 : cmake . /*N'oubliez pas le point*/
	------------
	Commande 4 : make
	------------
	Commande 5 : make install
	------------
	Commande 6 : LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib ; /*Ajouter le chemin a la variable path*/
	------------
	Commande 7 : export LD_LIBRARY_PATH 
	------------

######Exécuter les commandes de 1 à 7. BRAVO! Libharu est maintenant disponible sur votre machine.

Fichiers néceessaires
=====================

Pour lancer l'exécution il faut avoir dans le même réperoitre les fichiers suivants.

	1 compil : 	/*Fichier pour lancer la compilation et l'exécution.*/
	2 entree : 	/*Fichier qui contient le code à afficher en format pdf*/
	3 projet.l : 	/*Le fichier flex de notre programme*/
	4 projet.y : 	/*Le fichier yacc de notre programme*/
	5 rouen.png : 	/*une image quelconque avec ce nom (vous pouvez changer le nom) */


Lancement de l'exécution
========================
- Pour lancer la compilation et l'exécution il suffit de lancer la commande :

        ./compil

#### Le fichier contient : 
    1 flex proj.l     /*compilation du fichier flex*/
    2 yacc proj.y     /*compilation du fichier yacc*/

    3 gcc y.tab.c -ly -lfl -lhpdf -lm	
    /* -lhpdf : pour avoir les bibliothéque de notre librairie /-lm : pour ajouter 'math'*/

    4 ./a.out entree  /*Lancer l'exécutable avec 'entree' comme fichier d'entrée*/

### Version
#1.0


**Free Software !**

[Libharu]:http://libharu.org/

