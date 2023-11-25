# LINFO1252 (Systèmes informatiques) - PROJET 1 - GROUPE 36 (vendredi)

Projet 1 pour le cours de Systèmes Informatiques à UCL

# Arborescence du code

```
.
├── experiments.sh
├── headers
│   ├── includes.h
│   ├── philosophes.h
│   └── reader_writer.h
├── main.c
├── Makefile
├── performance
│   ├── csv
│   │   ├── ingi_temps_philo.csv
│   │   └── ingi_temps_rw.csv
│   ├── main.py
│   ├── temps_philo.sh
│   └── temps_rw.sh
├── Projet1_multithread.pdf
├── README.md
└── src
    ├── includes.c
    ├── philosophes.c
    └── reader_writer.c

4 directories, 16 files
```

---

# Structure du code

Dossier `headers` : contient les fichiers headers des fichiers dans `src`

Dossier `src` : contient les fichiers sources du projet, nécessaire au lancement du code.

Dossier `performance` : contient les scripts pour déterminer le temps d'exécution

# Utilisation du Makefile

---
## Compilation

Il y a deux manières de compiler le programme mais ils font la même chose.

1) Compile le programme et crée l'exécutable main

`make`

2) Compile le programme et crée l'exécutable main

`make run`

## Execution

Le code s'exécute en lui indiquant le nom du programme que vous souhaitez lancer et ses différentes options :

`./main -f [NAME] [OPTION]`

OPTION :

* `-f [NAME]` : NAME peut valoir *philo*, *reader_writer*

* `[OPTION]` : OPTION peut valoir *-n* ou *-i*, *-j* ou *-h*

    * -n : s'utilise avec *philo*, c'est le nombre de philosophes que vous voulez appeler 

    * -i et -j : s'utilise avec *reader_writer*, c'est le nombre de readers (*-i*) et le nombre de writers (*-j*) que vous voulez appeler

    * -h : s'utilise pour afficher l'aide du programme choisi (*-?* fonctionne aussi)

#### Exemple

* `./main -h` : affiche l'aide du `main`

* `./main -f philo -h` : affiche l'aide du programme `philo`

* `./main -f reader_writer -i 50 -j 6` : lance le programme reader_writer avec 50 readers et 6 writers

## Nettoyer le dossier

`make clean`

Supprime le fichier main créé avec `make` ou `make run`

Peut s'utiliser avec une option `ALL` par défault à `0`:  
`make clean ALL=1`  
Supprime les fichiers `.csv` dans le dossier `performance/csv/` mais ignore ceux créé par Inginious.

## Calculer le temps

`make times`

Lance tous les scripts présents dans `performance/` qui calcule le temps que mettent les différents programmes à finir.  
Peut s'utiliser avec une option `LAUNCH` par défault à `NULL`  
Précisez le nom du programme que vous souhaitez lancer (*philo* ou *rw*)  
* `make times LAUNCH=philo`
* `make times LAUNCH=rw`

# Membres du groupe
---

Bette Jonas

Lambot Romain
