# Team_22 : Projet en informatique pour SV 2018-2019

Voici le README de notre programme:



			I/Présentation du programme

Notre programme permet de simuler l'évolution d'un réseau de neurones au cours du temps. Lors de l'initialisation un certain nombre de neurones sont crées en fonction des paramètres donnés par l'utilisateur. Les neurones peuvent être soit des inhibiteurs soit des excitateurs avec des sous-types, conformément au modèle d'Izhikevich: RS,CH,IB pour les excitateurs et FS et LTS pour les inhibiteurs.

Les neurones appartient à un réseau appelé le Network, qui permet de classifier les neurones et gerer leur évolution au cours du temps.

Dès lors les neurones vont former des connections alétoires, ces connections sont unidirectionnelles et possèdent une force de liaison régie par une distribution uniforme.

Un courant va fluctuer dans le Network au cours de la Simulation.

Chaque neurone possède un potentiel de menbrane qui évolue au cours du temps via les connections qui sont faites entre ce neurone et ses voisins.

Le potentiel est donc fonction du temps et des voisins du neurone qui lui sont associés lors de l'initialisation, ceux si influent sur le potentiel selon leur types. En effet, comme leurs noms l'indique les excitateurs vont augmenter le potentiel d'un neurone de même que les inhibiteurs vont diminuer le potentiel.

De surcroit, le courant synaptique d'un neurone va être transformer par les types des neurones avec qui il est lié et par l'input thalamique qui agit comme un bruit externe.

Lorsque que le potentiel de membrane est supérieur au seuil de décharge T = 30[mV], qui correspond à la valeur de potentiel à laquelle le neurone transmet une impulsion le long de son axone. On dira qu'un neurone est "Firing" si son potentiel dépasse le seuil de décharge. Lorsqu'un neurone est 'firing" le programme affiche un '1' et '0' sinon ,dans la matrice associée à la simulation. Après une décharge (spike) le potentiel de menbrane retombe à -65mV.

PS:
La matrice associée est intitulée "1-raster_data.txt" et se situe dans le dossier results.

Tests:
Des tests sont disponibles dans le dossier test. Ils permettent de faire des vérifications sur le bon fonctionnement des classes codées au préalables.
Il y a des tests pour les classes: Neurone, Network, Simulation.

Extensions:

* Dossier auxiliaire qui donne les pas de temps auxquel les neurones spikes dans le dossier results: "2-Spike.txt".
* La variation du poids des connections est également possible selon le choix de l'utilisateur.
* L'affichage du poids des liens de chaque neurone dans le dossier results.
Attention: comme le programme créer un fichier texte pour chaque neurone cela demande beaucoup plus de temps (le programme est plus lent).
Il est convenable d'utiliser cette extension pour des valeurs de neurones ne dépassant pas 1000.



			II/Compilation et utilisation du programme
NB:
Le programme utilise les différentes librairies:

* TCLAP pour les paramètres du programme
* GTEST pour les tests du programme
* CMAKE pour la compilation du programme
* DOXYFILE pour la génération des fichiers de documentation

1) La Compilation

La compilation s'effectue sous la norme cmake (dans le terminal) et fonctionne sous la norme CMAKE:

-> Création des dossiers nécéssaire au lancement du programme:

mkdir build   

mkdir results

-> Aller dans le dossier build, lieu de compilation et de lancement du programme:

cd build

-> Compilation:

cmake ..

make

make doc

2) Les Tests

Pour lancer les tests:

./testNeuroNet

Un test qui fonctionne affiche "OK" dans le terminal alors que si le test échoue "FAILED" sera écrit dans le terminal.

3) Le programme

Les variables sont:

* -N   :le nombre de neurones (nombre entier positif)
* -p   :la proportion de neurones excitateurs (nombre décimal entre [0;1])
* -c   :la connectivité moyenne (nombre entier positif)
* -T   :le temps de la simulation (nombre entier positif)
* -r   :la proportion de neurones RS (nombre décimal entre [0;1])
* -a   :la proportion de neurones CH (nombre décimal entre [0;1-r])
* -f   :la proportion de neurones FS (nombre décimal entre [0;1])
* -nes :la borne superieure de l'input thalamique des excitateurs (nombre décimal entre [0;infini[)
* -nis :la borne superieure de l'input thalamique des inhibiteurs (nombre décimal entre [0;infini[)
* -k   :la valeur booléenne sur le choix de l'extension (ext [true;false])
* -l   :la valeur booléenne sur le choix d'affichage des liens et leurs poids au cours du temps(evo [true;false]). 
Pour l'éxecution:

./NeuroNet -N -p -T -c -r -a -f -nes -nis -k -l

NB:

Comme la proportion de neurones excitateurs doit être comprise entre 0 et 1, la somme des proportions de chaque type de neurones excitateurs ne doit pas dépasser 1.

Donc la proportion de neurones CH est à chosir entre 0 et 1-r où r est la proportion de neurones RS.

exemples de commande:

i)
Pour lancer le programme avec 1000 neurones, 70% de neurones excitateurs (30% d'inhibiteurs) et une connectivité moyenne de 60.

./NeuroNet -N 1000 -p 0.7 -c 60   

ii)
Pour lancer le programme avec 2000 neurones, 21% de neurones excitateurs (79% d'inhibiteurs), une connectivité moyenne de 80,
45% de RS, 12% de CH, 43% de IB, 76% de FS et 24% de LTS

./NeuroNet -N 2000 -p 0.79 -c 80 -r 0.45 -a 0.12 -f 0.76

iii)
Pour lancer le programme avec l'évolution des liens et l'affichage des liens de neurones au cours du temps.

./NeuroNet -k 1 -l 1

4) Valeurs par défaut

taper dans le terminal: ./NeuroNet 

Le programme va prendre des valeurs par défaut: 

* -N   =100
* -p   =0.5
* -T   =100
* -c   =40
* -r   =0.33
* -a   =0.33
* -f   =0.5
* -nes =1
* -nis =1
* -k   =false
* -l   =false

5) Accés à la documentation Doxygen:

Dans le dossier doc, aller dans le dossier html et ouvrir index.html
