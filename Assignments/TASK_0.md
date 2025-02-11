# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?

- La touche c

Comment faire pour quitter le programme ?

- Appuyer sur le touche x ou q 

A quoi sert la touche 'F' ?

- A passer en mode plein ecran ou non.

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?

- L'avion atterri, il se fait ravitailler en essence et redécolle.

Quelles informations s'affichent dans la console ?

- Les actions que l'avion fait

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

Trois avions peuvent atterir. Le dernier avion attend en l'air qu'une place se libère

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

- aircraft_types : definit les 3 différents types d'avions
- aircraft : représente un avion
- airport_type : definit les différents types d'aeroports
- airport : représente un aeroport
- config : configuration des paramètres de la simulation
- geometry : represente des points 2D ou 3D
- runway : représente une piste d'atterissage/décollage
- terminal : représente un terminal d'un aéroport
- tower_sim: simule un aéroport
- tower : Gère les flux d'un aéroport
- waypoint : représente un point de passage, sert à créer des trajectoires pour les avions


Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.


- Tower 

    WaypointQueue get_instructions(Aircraft& aircraft) :

        Donne les prochains points de passage.

    void arrived_at_terminal(const Aircraft& aircraft) :

        Averti qu'un avion atterit jusqu'au terminal.


- Aircraft

    const std::string& get_flight_num() const

        Donne le numéro de vol de l'avion.

    float distance_to(const Point3D& p) const

        Calcule la distance entre le point et l'avion.

    void display() const

        Affiche l'avion.

    void Aircraft::move()

        Déplace l'avion en suivant les points de passage.

- Airport

    Tower& get_tower()

        Donne la tour de controle associé à l'aéroport.

    void display() const

        Affiche l'aéroport.

    void move()

        Simule le déplacement de l'aéroport .


- Terminal

    bool in_use() const

        Dit si le terminal est utilisé par un avion.

    bool is_servicing() const

        Dit si un avion est en cours de ravitaillement.

    void assign_craft(const Aircraft& aircraft)

        Donne à un terminal, à avion associé.

    void start_service(const Aircraft& aircraft) 
    
        Commence le ravitaillement d'un avion .

    void finish_service()

        Termine le ravitaillement d'un avion.

    void move()

        Simule le "déplacement" d'un terminal, permet de faire "avancer" le ravitaillement.

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?

- Une succession de Waypoint

Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?

- Une deque

Expliquez les intérêts de ce choix.
- On doit garder l'ordre des waypoints

## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

- Dans aircraft_types.hpp

2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

-ticks_per_sec 
-Si on met 0 tick par seconde le programme plante
-On peut sinon faire en sorte de pas bouger les avions mais continuer la boucle


3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

- SERVICE_CYCLES

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\

- L'avion doit etre supprimé après avoir été ravitaillé, dans la fonction get_instruction() de la classe tower

Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?

- L'objet avion n'est pas référencé uniquement dans cette fonction, les itérateurs le contenant ne vont plus être valide  

A quel endroit de la callstack pourriez-vous le faire à la place ?\

- Dans la fonction move() qui elle renvoie un bool pour timer() 

Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

- Un champ refuel + la fonction move retourne un bool


5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?


6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

- La classe Tower est désigné comme friend dans la classe Airport, elle a donc acces aux méthodes privées de Airport

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

- On modifie le point avec la fonction cap_length, on est donc obligé de passer par une copie.

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.