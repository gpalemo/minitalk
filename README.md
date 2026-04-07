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

**Dans minitalk, on utilise `sigaction()` avec le flag `SA_SIGINFO`**, qui nous permet d'avoir une signature plus complète:

```c
void handler(int sig, siginfo_t *info, void *context)
```

**Avantages:**
- `siginfo_t *info` contient des informations sur le signal
- **Surtout: `info->si_pid` donne le PID du processus qui a envoyé le signal**
- Permet au serveur de savoir à quel client répondre

<pre>
Exemple conceptuel:
- Serveur en cours d'exécution
- SIGUSR1 arrive du client avec PID 5843
- Le système dit "wsh, t'as un signal du PID 5843"
- Le handler se déclenche avec info->si_pid = 5843
- Le handler reconstruit le bit reçu
- Le serveur envoie un ACK (SIGUSR1) AU CLIENT pour confirmer
- On continue
</pre>

### **2.6 Le Protocole d'ACK (Acknowledgment)**

**Le problème:** Si on envoie juste les signaux sans rien, il y a un risque que certains signaux se perdent ou arrivent dans le désordre, surtout avec de longs messages.

**La solution:** Un mécanisme d'**ACK (accusé de réception)** bit par bit:

1. **Client envoie 1 bit** au serveur (SIGUSR1 ou SIGUSR2)
2. **Client se bloque** en attente (`pause()`)
3. **Serveur reçoit le bit**, le traite, puis **envoie un SIGUSR1 au client** (= "j'ai reçu, OK")
4. **Client reçoit l'ACK**, sort de la pause, **envoie le bit suivant**
5. Répète jusqu'à 8 bits par caractère

**Avantages:**
- Les signaux ne se perdent pas (chaque bit est confirmé)
- **Stop-and-wait:** très fiable
- Fonctionne avec de longs messages (300+ caractères testés)

<pre>
Échange bit par bit avec ACK:

CLIENT:                   SERVEUR:
┌──────────────┐          
│ SIGUSR1/2 ──────────────> Reçoit bit
│              │          │ Reconstruit
│ pause() pour ACK        │ Envoie SIGUSR1 (ACK)
│              <──────────── SIGUSR1 (ACK)
│ g_ack = 1  │          
│ Bit suivant ──────────────> Reçoit bit
│              │          │ ...
│ pause()      <──────────────
└──────────────┘          
</pre>

**Variables clés:**
- `volatile sig_atomic_t g_ack` = flag pour tracker l'ACK reçu
- `signal(SIGUSR1, ack_handler)` = le client écoute les ACK
- `while (g_ack == 0) pause()` = attendre l'ACK avant le prochain bit

### **2.7 Le Flux Complet (Vue d'ensemble)**

<pre>
SERVEUR                              CLIENT
────────────────────────────────────────────────

Démarrage
Affiche PID: 12345
Enregistre handlers SIGUSR1/2
avec sigaction() + SA_SIGINFO
                                    Démarre avec:
                                    ./client 12345 "Hi"
                                    
                                    Enregistre handler SIGUSR1 (ACK)
                                    
                                    Pour chaque caractère:
                                      Pour chaque bit (0-7):
                                        Envoie SIGUSR1/SIGUSR2
Reçoit SIGUSR1/SIGUSR2 ◄──────────────────
Handler:
  Extrait PID client via info->si_pid
  Reconstruit le bit
  Envoie SIGUSR1 (ACK) au client
Envoie SIGUSR1 ────────────────────>
                                        Reçoit ACK (g_ack = 1)
                                        Sort de pause()
(Après 8 bits = 1 char)                Envoie le prochain bit...
Affiche le caractère
Réinitialise
                                        
(Répète pour chaque caractère)

Reçoit '\0' (8 zéros)            ◄────  Client envoie '\0' à la fin
Affiche le message complet
Réinitialise et attend client suivant...
</pre>

### **2.8 `volatile` et `sig_atomic_t`: Pourquoi?**

**Problème:** Sans protection, le compilateur optimise les variables et crée des boucles infinies:

```c
int g_ack = 0;
while (g_ack == 0)  // Le compilateur dit "ça ne change jamais"
	pause();    // et transforme ça en while(1) ← FREEZE!
```

**Solution:**
```c
volatile sig_atomic_t g_ack = 0;
```

- **`volatile`** = force le compilateur à relire la variable à chaque fois (pas d'optimisation)
- **`sig_atomic_t`** = type POSIX qui garantit une opération atomique (une seule instruction machine, pas interruptible par les signaux. Atomique = opération en 1 seule étape, introuvable par les signaux, et non-atomique = opération en plusieurs étapes, les signaux peuvent foutre le bordel au milieu)

**Sans ça:** boucles infinies, freeze, corruption. **Avec ça:** safe et fiable. 

---
_**Ce qui est utilisé :**_

Fonctions POSIX essentielles:

- **`sigaction()`**: configurer les handlers avec plus d'infos (vs `signal()`)
- **`SA_SIGINFO`**: flag pour avoir `siginfo_t` avec le PID du sender
- **`kill(pid, signal)`**: envoyer SIGUSR1/SIGUSR2 à un PID spécifique
- **`getpid()`**: récupérer le PID du processus
- **`pause()`**: bloquer jusqu'à un signal (économe en CPU)
- **`volatile sig_atomic_t`**: type spécial pour les variables partagées avec les signaux — atomique + protégé du compilateur (voir section 2.8)
- **`sigemptyset()`**: initialiser un masque de signaux vide

Pas de sockets, pas de pipes, pas de files. Juste des signaux, bastacusi.

---
_**Ce qu'on DOIT gérer**_

1. **Les erreurs**: PID invalide, pas d'arguments, processus qui n'existe pas
2. **Le protocole ACK**: chaque bit doit être confirmé avant le suivant
3. **Les memory leaks**: chaque malloc a son free
4. **Les segfaults**: on doit JAMAIS crash
5. **La conformité POSIX**: utiliser les bons types et drapeaux
6. **La stabilité**: le serveur doit pouvoir traiter plusieurs clients de suite


## 3. Résumé du Protocole Implémenté

**C'est un handshaking per-bit "Stop-and-Wait":**

```
Pour chaque bit du message:
  1. Client          : Envoie SIGUSR1/SIGUSR2
  2. Client         : Bloque en attente (pause)
  3. Serveur        : Reçoit dans handler, reconstruit le bit
  4. Serveur        : Envoie SIGUSR1 au client (ACK)
  5. Client (ACK)   : Reçoit SIGUSR1, met g_ack = 1
  6. Client         : Sort de pause(), prêt pour le prochain bit
```

**Avantages:**
- ✅ Fiable (chaque bit confirmé)
- ✅ Pas de perte de signaux
- ✅ Marche avec de longs messages
- ✅ Respecte les standards POSIX

**Variables critiques:**
- `volatile sig_atomic_t g_ack` — Le flag qui track l'ACK reçu
- `signal(SIGUSR1, ack_handler)` — Enregistre le handler pour les ACKs
- `sigaction() + SA_SIGINFO + sigemptyset()` — Configuration robuste du serveur