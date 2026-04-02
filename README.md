# MINITALK

## Sommaire

1. [Introduction](#1-introduction)
   1. [Qu'est-ce que c'est ?](#11-quest-ce-que-cest-)
2. [Concepts clés](#2-concepts-clés)
   1. [Les Processus et les PIDs](#21-les-processus-et-les-pids)
   2. [Les Signaux UNIX](#22-les-signaux-unix)
   3. [Le Problème: Envoyer du texte avec seulement 2 signaux](#23-le-problème-envoyer-du-texte-avec-seulement-2-signaux)
   4. [Le Binaire et les Bits](#24-le-binaire-et-les-bits)
   5. [Les Handlers (Gestionnaire de Signaux)](#25-les-handlers-gestionnaire-de-signaux)
   6. [La Performance: Pourquoi c'est limitant?](#26-la-performance-pourquoi-cest-limitant)
   7. [Le Flux Complet (Vue d'ensemble)](#27-le-flux-complet-vue-densemble)
3. [Workflow & TODO](#3-workflow--todo)
   1. [Phase 1: Préparation et Setup](#phase-1-préparation--setup)
   2. [Phase 2: Comprendre les Fonctions Unix](#phase-2-comprendre-les-fonctions-unix)
   3. [Phase 3: Implémentation du Serveur](#phase-3-implémentation-du-serveur)
   4. [Phase 4: Implémentation du Client](#phase-4-implémentation-du-client)
   5. [Phase 5: Gestion d'Erreurs Robuste](#phase-5-gestion-derreurs-robuste)
   6. [Phase 6: Test et Performance](#phase-6-test--performance)
   7. [Phase 7: Optimisation & Bonus](#phase-7-optimisation--bonus-optionnel)
4. [Par Où Commencer?](#4-par-où-commencer-tldr)



## 1. Introduction

## 1.1 Qu'est-ce que c'est ?

*Minitalk est un projet qui apprend à faire communiquer deux programmes séparés sur la même machine, en utilisant les signaux Unix. C'est un peu comme si deux personnes se parlaient uniquement en levant la main (**signal**) plutôt que de se parler directement.*

**Concrètement**:

- **Un serveur** qui attend des messages
- **Un client** qui envoie des messages
- **Une seule méthode de communication:** les signaux `SIGUSR1` et `SIGUSR2`

## 2. Concepts clés
### **2.1 Les Processus et les PIDs**

Chaque programme en cours d'exécution est un **processus**. Chaque processus a un identifiant unique appelé **`PID`** (Process ID).

Exemple: le serveur démarre et affiche `PID: 12345`. C'est comme son adresse, le client l'utilise pour savoir à qui envoyer le message.

<pre>
Serveur démarré
PID: 12345

Client se lance avec:
./client 12345 "Bonjour"
          ↑
      L'adresse du serveur
</pre>

### **2.2 Les Signaux UNIX**

Un **signal** est une **notification** qu'un processus envoie à un autre. C'est une interruption : le système dit "wsh, t'as reçu quelque chose".

Il existe plein de signaux (SIGTERM pour tuer, SIGKILL pour forcer, etc.), mais pour ce projet, on n'utilise que **deux**:

- **`SIGUSR1`**: signal utilisateur 1 (pas de sens prédéfini : on le définit nous)
- **`SIGUSR2`**: signal utilisateur 2 (pareil)

**_Pourquoi ces deux-là_? Parce que ce sont les seuls que les programmeurs peuvent utiliser librement sans avoir besoin d'être root et sans risquer de casser le système.**

### **2.3 Le Problème: Envoyer du texte avec seulement 2 signaux**

C'est LE défi du projet.

Comme dit plus haut, il y a :

- Signal A (SIGUSR1)
- Signal B (SIGUSR2)

Il faut envoyer: `"Hello"` (5 caractères, des centaines de valeurs possibles)

**Comment faire avec seulement 2 choix?**

Réponse: **binaire**. On peut représenter n'importe quel nombre avec des 0 et des 1.

### **2.4 Le Binaire et les Bits**

Un **bit** est la plus petite unité d'information: soit 0, soit 1.
Un **octet** (byte) = 8 bits. C'est la taille d'un caractère en ASCII.

Exemple avec le caractère `'A'`

<pre>
'A' en ASCII = 65
65 en binaire = 01000001
                ↑ ↑ ↑ ↑ ↑ 
             bit7 bit6 bit5... bit0
</pre>

**L'idée du projet:**

- Pour envoyer `'A'`, on envoie 8 signaux (un pour chaque bit)
- SIGUSR1 = envoyer un 0
- SIGUSR2 = envoyer un 1

Donc pour `'A'` (01000001):
<pre>
0 → SIGUSR1
1 → SIGUSR2
0 → SIGUSR1
0 → SIGUSR1
0 → SIGUSR1
0 → SIGUSR1
0 → SIGUSR1
1 → SIGUSR2
</pre>

Le serveur reçoit ces 8 signaux, reconstruit les bits dans le bon ordre (`01000001`), convertit en décimal (65), puis en caractère (`'A'`). Baw, un caractère reçu.

### **2.5 Les Handlers (Gestionnaire de Signaux)**

Quand un signal arrive, c'est le **bordel**. Le processus ne sait pas qu'il a reçu quelque chose.

On doit dire au système: "quand tu reçois SIGUSR1, appelle **cette fonction**".

Cette fonction s'appelle un **`signal handler`** (gestionnaire de signal).

<pre>
Exemple conceptuel:
- Serveur en cours d'exécution
- SIGUSR1 arrive
- Le système dit "wsh, t'as un signal"
- Le handler se déclenche
- Le handler reconstruit le bit reçu
- On continue
</pre>

### **2.6 La Performance: Pourquoi c'est limitant?**

100 caractères = 800 bits = 800 signaux à envoyer.

**Le défi**: le sujet demande d'envoyer tout ça en 1 seconde maximum.

Entre chaque signal, il y a un petit délai (sinon le système peut perdre des signaux). C'est comme si on devait taper 800 fois très vite : il y a une limite à la vitesse.

Solution: on peut utiliser `usleep()` pour mettre des tout petits délais (quelques microsecondes) entre chaque signal.

### **2.7 Le Flux Complet (Vue d'ensemble)**

<pre>
SERVEUR                              CLIENT
────────────────────────────────────────────────

Démarrage
Affiche PID: 12345
Attend...
                                    Démarre avec:
                                    ./client 12345 "Hi"
                                    
                                    Pour chaque caractère:
                                    Pour chaque bit:
                                        Envoie SIGUSR1/SIGUSR2
                                        Attend un peu                                       
Reçoit SIGUSR1/SIGUSR2 ◄──────────────
Handler reconstruit les bits
Accumule les caractères
Quand '\0' reçu: affiche "Hi"
Attend le client suivant...
</pre>

---
_**Ce qui est autorisé :**_

Pour faire ça, on a besoin de:

- `signal() / sigaction()`: pour configurer nos handlers
- `kill()`: pour envoyer les signaux
- `getpid()`: pour récupérer le PID
- `usleep()`: pour les délais (sinon trop rapide)
- `pause() / sleep()`: pour attendre le serveur

Pas de sockets, pas de pipes, pas de files. Juste des signaux, bastacusi.

---
_**Ce qu'on DOIT gérer**_

1. **Les erreurs**: PID invalide, pas d'arguments, processus qui n'existe pas
2. **Les memory leaks**: chaque malloc a son free
3. **Les segfaults**: on doit JAMAIS crash
4. **La stabilité**: le serveur doit pouvoir traiter `10` clients de suite

## 3. Workflow & TODO

### **Phase 1: Préparation et Setup**

- [x] Créer la structure des fichiers:
  - `src/server.c` - Programme serveur
  - `src/client.c` - Programme client
  - `include/minitalk.h` - Header avec les fonctions communes
  - `Makefile` - Compilation

- [x] Mettre à jour le `Makefile` pour compiler `server` et `client` exécutables

- [x] Vérifier que `libft` et `ft_printf` compilent correctement

### **Phase 2: Comprendre les Fonctions Unix** 

Avant de coder, comprendre chaque fonction:

- [ ] **`signal()` / `sigaction()`** - Comment configurer un handler
- [ ] **`kill()`** - Comment envoyer un signal à un PID
- [ ] **`getpid()`** - Récupérer le PID du processus
- [ ] **`pause()`** - Le serveur s'arrête en attente (comment ça marche?)
- [ ] **`usleep()`** - Faire des petits délais précis en microsecondes

### **Phase 3: Implémentation du Serveur**

**Étape 3.1 - Structure de base**
- [ ] Afficher le PID au démarrage
- [ ] Configurer le handler pour SIGUSR1
- [ ] Configurer le handler pour SIGUSR2
- [ ] Faire un `pause()` infini pour attendre les signaux

**Étape 3.2 - Reconstruction des bits**
- [ ] Dans le handler, récupérer quel signal a été reçu
- [ ] Accumuler les bits dans une variable (8 bits = 1 caractère)
- [ ] Quand on a 8 bits, convertir en caractère et l'afficher
- [ ] Quand on reçoit `\0`, on a fini le message

**Étape 3.3 - Gestion de plusieurs clients**
- [ ] S'assurer que le serveur continue après un premier message
- [ ] Réinitialiser l'accumulateur pour le client suivant

### **Phase 4: Implémentation du Client**

**Étape 4.1 - Parse des arguments**
- [ ] Vérifier qu'on a exactement 2 arguments (PID + message)
- [ ] Convertir le PID en entier (erreur si invalide)
- [ ] Vérifier que le message n'est pas vide

**Étape 4.2 - Envoi bit par bit**
- [ ] Pour chaque caractère du message:
  - [ ] Pour chaque bit (de 0 à 7):
    - [ ] Si bit = 0 → envoyer SIGUSR1
    - [ ] Si bit = 1 → envoyer SIGUSR2
    - [ ] Attendre un petit peu (`usleep()`)

**Étape 4.3 - Finalisation**
- [ ] Après le dernier caractère, envoyer le `\0` (8 zéros)
- [ ] Attendre un peu, puis exit

### **Phase 5: Gestion d'Erreurs Robuste**

- [ ] **Client:**
  - [ ] PID invalide (pas un nombre)
  - [ ] PID qui n'existe pas (le processus n'existe pas)
  - [ ] Pas d'arguments
  - [ ] Message qui n'existe pas / vide

- [ ] **Serveur:**
  - [ ] Vérifier que `kill()` ne retourne pas d'erreur
  - [ ] Gérer les signaux correctement même en cas de problème

- [ ] **Général:**
  - [ ] Pas de fuites mémoire
  - [ ] Pas de segfault
  - [ ] Pas de double-free

### **Phase 6: Test et Performance**

- [ ] Tester avec un message court (ex: "Hi")
- [ ] Tester avec un message long (100+ caractères)
  - [ ] Chronomètrer: doit être ≤ 1 seconde pour 100 caractères
- [ ] Tester avec plusieurs clients de suite
- [ ] Tester avec des caractères spéciaux (accents, symboles, etc.)
- [ ] Vérifier memory leaks avec `valgrind`

### **Phase 7: Optimisation & Bonus (Optionnel)**

- [ ] Optimiser `usleep()` pour être plus rapide (sans perdre de signaux)
- [ ] **Bonus**: Serveur envoie ACK au client (pour confirmer réception)
- [ ] **Bonus**: Afficher la PID du client qui a envoyé le message

---

## 4. Par ou commencer ?

1. Créer le premier squelette de fichiers (Phase 1)
2. Comprendre les 5 fonctions Unix (Phase 2) — lire les man pages
3. Coder le serveur simple (Phase 3.1 + 3.2)
4. Coder le client simple (Phase 4.1 + 4.2)
5. Tester "Hi" → affichage simple
6. Ajouter la gestion d'erreurs (Phase 5)
7. Tester la performance (Phase 6)
8. Bonus? (Phase 7 — optionnel)