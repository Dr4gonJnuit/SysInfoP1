# LINFO1252 (Systèmes informatiques) - PROJET 1 - GROUPE 36 (vendredi)

Projet 1 pour le cours de Systèmes Informatiques à UCL

# Arborescence du code

```
.
├── Makefile
├── Projet1_multithread.pdf
├── README.md
├── Rapport
│   ├── LINFO1252_rapport_groupe1.aux
│   ├── LINFO1252_rapport_groupe1.fdb_latexmk
│   ├── LINFO1252_rapport_groupe1.fls
│   ├── LINFO1252_rapport_groupe1.log
│   ├── LINFO1252_rapport_groupe1.out
│   ├── LINFO1252_rapport_groupe1.pdf
│   ├── LINFO1252_rapport_groupe1.synctex.gz
│   ├── LINFO1252_rapport_groupe1.tex
│   └── images
│       └── uclougo.jpg
├── experiments.sh
├── headers
│   ├── algorithmes
│   │   ├── philosophes.h
│   │   ├── produc_conso.h
│   │   └── reader_writer.h
│   ├── attente_active
│   │   ├── my_mutex.h
│   │   └── my_semaphore.h
│   └── includes.h
├── main.c
├── performance
│   ├── bash
│   │   ├── temps_TAS.sh
│   │   ├── temps_pc.sh
│   │   ├── temps_philo.sh
│   │   └── temps_rw.sh
│   ├── csv
│   │   ├── Ingi_temps_philo_POSIX.csv
│   │   ├── Ingi_temps_philo_TAS.csv
│   │   ├── Ingi_temps_philo_TATAS.csv
│   │   ├── Ingi_temps_prod_cons_POSIX.csv
│   │   ├── Ingi_temps_prod_cons_TAS.csv
│   │   ├── Ingi_temps_prod_cons_TATAS.csv
│   │   ├── Ingi_temps_read_write_POSIX.csv
│   │   ├── Ingi_temps_read_write_TAS.csv
│   │   ├── Ingi_temps_read_write_TATAS.csv
│   │   ├── Ingi_temps_test_TAS.csv
│   │   └── Ingi_temps_test_TATAS.csv
│   ├── main.py
│   ├── perf_TAS.c
│   └── result
│       ├── Temps_TAS_TATAS.png
│       ├── Temps_philo.png
│       ├── Temps_prod_cons.png
│       └── Temps_read_write.png
└── src
    ├── algorithmes
    │   ├── philosophes.c
    │   ├── produc_conso.c
    │   └── reader_writer.c
    ├── attente_active
    │   ├── my_mutex.c
    │   └── my_semaphore.c
    └── includes.c

12 directories, 47 files
```

---

# Structure du code

Dossier `headers` : contient les fichiers headers des fichiers dans `src`

Dossier `src` : contient les fichiers sources du projet, nécessaire au lancement du code.

Dossier `performance` : contient les scripts pour déterminer le temps d'exécution

Dossier `Rapport` : contient le code source du rapport

# Utilisation du Makefile

---

## Compilation

Il y a deux manières de compiler le programme mais ils font la même chose.

1. Compile le programme et crée l'exécutable main

`make`

2. Compile le programme et crée l'exécutable main

`make run`

Il y a aussi moyen de choisir le programme que vous souhaitez lancer avec ces commandes :

1. Compile simplement les problèmes

`make main`

2. Compile simplement les performances du TAS et TATAS

`make TAS`

## Execution

Le code s'exécute en lui indiquant le nom du programme que vous souhaitez lancer et ses différentes options :

`./main -f [NAME] [OPTION]`

OPTION :

- `-f [NAME]` : NAME peut valoir _philo_, _prod_cons_ ou _read_write_

- `[OPTION]` : OPTION peut valoir _-n_ ou _-h_

  - -n : s'utilise pour indiquer le nombre de threads que vous souhaitez lancer (pour _prod_cons_ et _read_write_, ça lancera le même nombre de producteurs et consomateurs ou lecteurs et écrivains)

  - -h : s'utilise pour afficher l'aide du programme choisi (_-?_ fonctionne aussi)

#### Exemple

- `./main -h` : affiche l'aide du `main`

- `./main -f philo -h` : affiche l'aide du programme `philo`

- `./main -f read_write -n 7` : lance le programme reader_writer avec 7 readers et 7 writers

## Nettoyer le dossier

`make clean`

Supprime le fichier main créé avec `make` ou `make run`

Peut s'utiliser avec une option `ALL` par défault à `0`:  
`make clean ALL=1`  
Supprime les fichiers `.csv` dans le dossier `performance/csv/` mais ignore ceux créé par Inginious.

## Calculer le temps

`make tests`

Lance tous les scripts présents dans `performance/` qui calcule le temps que mettent les différents programmes à finir.  
Peut s'utiliser avec une option `LAUNCH` par défault à `NULL`  
Précisez le nom du programme que vous souhaitez lancer (_philo_ ou _rw_ dans l'exemple ci-dessous)

- `make tests LAUNCH=philo`
- `make tests LAUNCH=rw`

# Membres du groupe

---

Bette Jonas

Lambot Romain
