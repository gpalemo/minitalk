# Fonctions utilisées
---

## 1. signal()

```c
sighandler_t signal(int signum, sighandler_t handler);
```

### Explication
La fonction `signal()` en C est un moyen de spécifier une **fonction callback**, appelée **gestionnaire de signal** (signal handler), à appeler automatiquement quand un signal spécifique est reçu par le programme.

Un **signal** est un message du système d'exploitation à un processus indiquant qu'un événement s'est produit (ex: Ctrl+C, termination demand, etc.).

### Utilité dans Minitalk
C'est la fonction que l'on utilisera pour **dire au serveur** : "quand il reçoit SIGUSR1, appelle cette fonction". C'est le point d'entrée pour récupérer les signaux du client.

### Exemple simple
```c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler(int signum) 
{
  printf("Received SIGINT!\n");
  exit(0);
}

int main() 
{
  // Set the signal handler for the SIGINT and SIGTERM signals
  // to the signal_handler function
  
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  while (1) {
    // Do some work here...
  }

  return 0;
}
```

### Important
- `signal()` est plus simple mais moins portable. Pour ce projet, **`sigaction()` est préférable** (voir plus bas).
- Le handler s'exécute de manière **asynchrone** (à n'importe quel moment).

---

## 2. sigaction()

```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

### Explication
`sigaction()` est la version **plus robuste et portable** de `signal()`. Elle permet de spécifier l'action à prendre quand un signal est reçu.

Les arguments :
- **`signum`** : le numéro du signal (ex: SIGUSR1, SIGUSR2)
- **`act`** : pointeur vers une structure `sigaction` contenant la fonction handler et les options
- **`oldact`** : pointeur pour récupérer l'ancienne action (peut être NULL)

### Structure sigaction
```c
struct sigaction {
    void (*sa_handler)(int);  // Pointeur vers la fonction handler
    sigset_t sa_mask;          // Signaux à bloquer pendant l'exécution du handler
    int sa_flags;              // Options (ex: SA_RESTART)
};
```

### Utilité dans Minitalk
C'est la meilleure façon de **configurer les gestionnaires de signaux**. On l'utilisera au démarrage du serveur pour dire : "quand il reçoit SIGUSR1 ou SIGUSR2, appelle le handler".

### Exemple
```c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler(int signum) {
  printf("Received signal %d\n", signum);
}

int main(void) {
  struct sigaction action;
  action.sa_handler = signal_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  sigaction(SIGINT, &action, NULL);

  while (1) {
    // Do some work
  }

  return 0;
}
```

---

## 3. sigemptyset()

```c
int sigemptyset(sigset_t *set);
```

### Explication
`sigemptyset()` initialise un **ensemble de signaux vide**, c'est-à-dire un ensemble qui ne contient aucun signal.

Les ensembles de signaux sont utilisés par certaines fonctions (comme `sigaction()`) pour définir :
- Quels signaux traiter
- Quels signaux bloquer pendant l'exécution du handler

### Utilité dans Minitalk
On l'utilisera pour **préparer l'ensemble de signaux** avant d'utiliser `sigaction()`.

### Exemple
```c
#include <signal.h>

int main(void)
{
    sigset_t signal_set;

    // Initialize an empty signal set
    sigemptyset(&signal_set);

    // Add SIGINT to the signal set
    sigaddset(&signal_set, SIGINT);

    return 0;
}
```

---

## 4. sigaddset()

```c
int sigaddset(sigset_t *set, int signum);
```

### Explication
`sigaddset()` **ajoute un signal spécifique** à un ensemble de signaux.

Se complémente toujours avec `sigemptyset()` : tu vides d'abord l'ensemble, puis tu ajoutes les signaux que tu veux traiter.

### Utilité dans Minitalk
On l'utilisera pour ajouter SIGUSR1 et/ou SIGUSR2 à l'ensemble de signaux que l'on veux bloquer pendant l'exécution du handler (pour éviter les chevauchements).

### Exemple
```c
sigset_t set;
sigemptyset(&set);
sigaddset(&set, SIGUSR1);
sigaddset(&set, SIGUSR2);

struct sigaction sa;
sa.sa_handler = handler;
sa.sa_mask = set;  // Ces signaux seront bloqués pendant le handler
sa.sa_flags = 0;
```

---

## 5. kill()

```c
int kill(pid_t pid, int sig);
```

### Explication
`kill()` est un appel système qui **envoie un signal à un processus**.

Les arguments :
- **`pid`** : l'identifiant du processus destinataire
- **`sig`** : le numéro du signal à envoyer (SIGUSR1, SIGUSR2, etc.)

**Retour** : 0 si succès, -1 si erreur

### Utilité dans Minitalk
C'est la fonction que l'on utilisera côté **client** pour **envoyer les signaux au serveur**. On enverra SIGUSR1 pour un bit 0, SIGUSR2 pour un bit 1.

### Exemple
```c
int server_pid = 12345;

kill(server_pid, SIGUSR1);  // Envoie un bit 0
usleep(100);
kill(server_pid, SIGUSR2);  // Envoie un bit 1
```

### Important
- Si le PID n'existe pas, `kill()` retourne -1 et met `errno` à ESRCH
- Il faut vérifier le retour de `kill()` pour détecter les erreurs

---

## 6. getpid()

```c
pid_t getpid(void);
```

### Explication
`getpid()` retourne l'**identifiant du processus** (PID) du processus actuel.

C'est comme le "numéro de téléphone" du processus : c'est ce qui permet aux autres processus de le trouver.

### Utilité dans Minitalk
On l'utilisera côté **serveur** pour afficher son PID au démarrage. Le client aura besoin de ce PID pour savoir à qui envoyer les signaux.

### Exemple
```c
int main(void) {
    pid_t my_pid = getpid();
    printf("Server PID: %d\n", my_pid);
    // Client lancera: ./client 12345 "Hello"
}
```

---

## 7. pause()

```c
int pause(void);
```

### Explication
`pause()` **endort le processus appelant indéfiniment** jusqu'à ce qu'un signal soit reçu.

Quand un signal arrive, le handler s'exécute, puis le programme continue (par défaut).

### Utilité dans Minitalk
C'est la fonction que l'on utilisera côté **serveur** pour le faire **attendre les signaux** du client.

### Exemple
```c
int main(void) {
    printf("Server PID: %d\n", getpid());
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    
    while (1) {
        pause();  // Attend un signal
        // Après réception d'un signal, le handler s'exécute
        // puis pause() reprend à cette ligne
    }
}
```

**Remarque** : `pause()` retourne toujours -1 (par design).

---

## 8. sleep()

```c
unsigned int sleep(unsigned int seconds);
```

### Explication
`sleep()` **endort le processus** pour un nombre de **secondes** spécifié.

Retourne le nombre de secondes restantes si interrompu par un signal.

### Utilité dans Minitalk
- **Sur le serveur** : optionnel, permettant un petit délai après la fin d'un message
- **Sur le client** : optionnel, permettant d'attendre une confirmation du serveur

### Exemple
```c
printf("Envoi du message...\n");
send_message(pid, "Hello");
sleep(1);  // Attendre 1 seconde
printf("Message envoyé!\n");
```

**À noter** : `sleep()` fonctionne en **secondes**, c'est assez lent. Préfère `usleep()` pour plus de précision.

---

## 9. usleep()

```c
int usleep(useconds_t usec);
```

### Explication
`usleep()` **endort le processus** pour un nombre de **microsecondes** spécifié (1 seconde = 1 000 000 microsecondes).

C'est la version **haute précision** de `sleep()`.

### Utilité dans Minitalk
**TRÈS IMPORTANT** : on l'utilisera côté **client** pour ajouter un petit délai entre chaque signal envoyé au serveur.

Pourquoi ? Parce que si on envoie les signaux trop vite, le serveur n'aura pas le temps de les traiter et les perdra.

**Délai typique** : 100-500 microsecondes entre chaque signal.

### Exemple
```c
for (int bit = 0; bit < 8; bit++) {
    if (character & (1 << bit))
        kill(server_pid, SIGUSR2);  // Bit 1
    else
        kill(server_pid, SIGUSR1);  // Bit 0
    
    usleep(100);  // Attendre 100 microsecondes
}
```

### Calcul du temps
- 100 caractères × 8 bits = 800 signaux
- 800 signaux × 100 microsecondes = 80 000 microsecondes = **0.08 secondes**
- Largement sous la limite de 1 seconde du sujet ✅

---

## 10. exit()

```c
void exit(int status);
```

### Explication
`exit()` **termine immédiatement le processus** et retourne un code de statut au système.

- **Status 0** : terminaison réussie
- **Status non-zéro** : erreur/échec

### Utilité dans Minitalk
On l'utilisera côté **client** pour terminer proprement après avoir envoyé le message entier.

### Exemple
```c
int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <PID> <message>\n", argv[0]);
        exit(1);  // Erreur
    }
    
    // ... envoi du message ...
    
    exit(0);  // Succès
}
```

---

## Résumé pour le projet

| Fonction | Côté | Utilité |
|----------|------|---------|
| `getpid()` | Serveur | Afficher son PID au démarrage |
| `signal()` ou `sigaction()` | Serveur | Configurer les handlers pour SIGUSR1/SIGUSR2 |
| `sigemptyset()` + `sigaddset()` | Serveur | Préparer l'ensemble de signaux (avec `sigaction()`) |
| `pause()` | Serveur | Attendre les signaux indéfiniment |
| `kill()` | Client | Envoyer les signaux au serveur |
| `usleep()` | Client | Ajouter des délais entre les signaux |
| `exit()` | Client | Terminer proprement après l'envoi |

---
