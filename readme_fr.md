
# pipex

## Table des matières

- [Introduction](#introduction)
- [Fonctionnalités](#fonctionnalités)
- [Utilisation](#utilisation)
- [Fonctions importantes](#fonctions-importantes)
- [Processus parent et enfant](#processus-parent-et-enfant)
- [Partie Bonus](#partie-bonus)

---

## Introduction

**pipex** est un projet de l'école 42 conçu pour apprendre aux étudiants le fonctionnement des pipes UNIX et des descripteurs de fichiers, en particulier comment gérer la redirection d'entrées et de sorties pour simuler la fonctionnalité de pipeline de shell. Ce projet fournit un programme simplifié de type shell pour exécuter des pipelines de commandes avec redirection.

---

## Fonctionnalités

- Émule les pipelines de shell avec deux commandes en utilisant les descripteurs de fichiers et `dup2`.
- Redirige l'entrée et la sortie standard entre des fichiers et des commandes.
- Inclut une gestion robuste des erreurs pour l'accès aux fichiers et l'exécution des commandes.
- **Bonus** : Implémente des pipes multiples et une fonctionnalité `here_doc` pour lire à partir de l'entrée standard jusqu'à ce qu'un délimiteur spécifique soit atteint.

---

## Utilisation

### Utilisation de base

```bash
./pipex fichier1 cmd1 cmd2 fichier2
```

- `fichier1` : Fichier d'entrée.
- `cmd1` : Première commande.
- `cmd2` : Deuxième commande.
- `fichier2` : Fichier de sortie.

Exemple :

```bash
./pipex infile "cat" "grep hello" outfile
```

---

## Fonctions importantes

### `open`

- **Utilisation** : `int fd = open("file.txt", O_RDONLY);`
- Ouvre un fichier en lecture, écriture ou ajout et retourne un descripteur de fichier.

### `close`

- **Utilisation** : `close(fd);`
- Ferme un descripteur de fichier ouvert, libérant ainsi les ressources associées.

### `read`

- **Utilisation** : `int bytes_read = read(fd, buffer, sizeof(buffer));`
- Lit les données d'un descripteur de fichier dans un tampon.

### `write`

- **Utilisation** : `write(fd, buffer, bytes_to_write);`
- Écrit les données d'un tampon vers un descripteur de fichier.

### `pipe`

- **Utilisation** : `pipe(pipefd);`
- Crée un pipe pour la communication unidirectionnelle entre processus.

### `dup2`

- **Utilisation** : `dup2(fd, STDOUT_FILENO);`
- Duplique un descripteur de fichier sur un autre, permettant la redirection des entrées/sorties.

### `fork`

- **Utilisation** : `pid_t pid = fork();`
- Crée un nouveau processus en dupliquant le processus actuel.

### `execve`

- **Utilisation** : `execve(path, args, env);`
- Remplace le processus actuel par un nouveau programme.

### `waitpid`

- **Utilisation** : `waitpid(pid, &status, 0);`
- Attend qu'un processus enfant spécifique se termine.

### `perror`

- **Utilisation** : `perror("Message d'erreur");`
- Affiche un message d'erreur correspondant à la valeur actuelle d'`errno`.

---

## Processus parent et enfant

Dans **pipex**, des processus sont créés avec `fork()`, permettant l'exécution de commandes dans le pipeline.

---

## Partie Bonus

Le bonus de **pipex** étend la fonctionnalité pour prendre en charge `here_doc`.

