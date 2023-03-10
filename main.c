#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure du Maillon
typedef struct m
{
    // information stockée
    int n;
    char nom[100];

    // references vers les voisins
    struct m *droite;
    struct m *gauche;
} Maillon;

// Initialisation d'un Maillon
Maillon *initMaillon(int n, const char *nom)
{
    // allocation mémoire
    // temp est un pointeur temporaire
    Maillon *temp = malloc(sizeof(Maillon));

    // Initialisation
    strcpy(temp->nom, nom);
    temp->n = n;
    temp->droite = NULL;
    temp->gauche = NULL;

    // Renvoie l'adresse allouée
    // celle de temp avant de l'effacer
    return temp;
}

// Ajouter en tete de liste
// À simplifier après compris le principe.
void procAjoutEnTeteDeListe(Maillon **pointeurSurListe, int n, const char *nom)
{
    // Creation du nouveau Maillon
    // Initialise avec les valeurs de n, nom
    // et ses deux voisins à NULL
    Maillon *temp = initMaillon(n, nom);

    // Si la liste est vide le nouveau Maillon
    // devient la tête de la liste
    if (*pointeurSurListe == NULL)
    {
        *pointeurSurListe = temp;
    }
    // Si non
    else
    {
        // Mise à jour des voisins du nouveau Maillon
        temp->droite = *pointeurSurListe;
        // temp->gauche = NULL; // inutile car init Maillon initialise à NULL

        // Mise à jour des voisins de l'ancienne tête
        // son voisin à gauche (avant NULL) devient le nouveau Maillon
        (*pointeurSurListe)->gauche = temp;

        // Mise à jour de la nouvelle tête
        *pointeurSurListe = temp;
    }
}

// Même principe, mais cette fois, on retourne l'adresse de la nouvelle tête
// Peut etre simplifié : à faire.
Maillon *funcAjoutEnTeteDeListe(Maillon *liste, int n, const char *nom)
{
    Maillon *temp = initMaillon(n, nom);

    if (liste == NULL)
    {
        liste = temp;
    }
    else
    {
        // Mise à jour des vosins
        temp->droite = liste;
        liste->gauche = temp;

        // Mise à jour de la tete
        liste = temp;
    }

    return liste;
}

// Ajoute en fin de liste
void procAjoutEnFinDeListe(Maillon **pointeurSurListe, int n, const char *nom)
{
    // Definition des variables
    Maillon * tail = *pointeurSurListe;

    // Allocation d'un nouveau maillon
    Maillon * temp = initMaillon(n,nom);

    // Verification de la liste
    if(*pointeurSurListe == NULL){
        *pointeurSurListe = temp;
    }else{
        // cherche la fin
        while (tail->droite !=NULL){
            tail = tail->droite;
        }

        // on a trouvé la fin
        tail->droite = temp;
        temp->gauche = tail;
    }
}

// Faire la version "fonction" d'ajouter en fin de liste.
void functAjoutEnFinDeListe(Maillon **pointeurSurListe, int n, const char *nom)
{
}

// On pioche le premiere element de la liste,
// mais on le conserve en memoire
Maillon *piocheEnTeteDeListe(Maillon **liste)
{
    // Pointeur vers maillon à retirer.
    Maillon * temp = NULL;

    // Verifie si la liste est vide
    if (*liste != NULL){
        // on repere la tête de la liste
        temp = *liste;

        // on met à jour la tête
        *liste = temp->droite;
        (*liste)->gauche = NULL;

        // on isole le maillon
        temp->droite = NULL;
        temp->gauche = NULL;
    }

    // on renvoie l'élément isolé
    return temp;
}

// On enleve le derniere element de la liste
// mais on le conserve en memoire
Maillon *piocheEnFinDeListe(Maillon **liste)
{

}

// On enleve un maillon donnée s'il existe.
Maillon *piocheUnMaillon(Maillon **liste, const int n)
{

}

// Nombre d'élements
// identique à celui de la liste chaine
int nombreElementsRecurs(Maillon *liste)
{

    if (liste == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + nombreElementsRecurs(liste->droite);
    }
}

// Affichage

void afficheMaillon(Maillon *m)
{
    printf("Nom : %s, Maillon: %d \n", m->nom, m->n);
}

void afficherListeAvecWhile(Maillon *liste)
{

    if (liste == NULL)
    {
        printf("Liste vide \n");
    }
    else
    {
        printf("Nombre d'éléments %d \n\n", nombreElementsRecurs(liste));
        printf("HEAD \n");
        while (liste != NULL)
        {
            afficheMaillon(liste);
            liste = liste->droite;
        }
        printf("TAIL \n\n");
    }
}

// liberation de la liste avec un while
// meme principe que les listes simplement chainées.
void libererListe(Maillon **pointeurSurListe)
{
    Maillon *head = *pointeurSurListe;
    Maillon *temp = NULL;

    while (head != NULL)
    {
        temp = head->droite;
        free(head);
        head = temp;
    }

    *pointeurSurListe = NULL;
}

int main()
{
    printf("********* Liste doublement chaînée *********");
    Maillon *liste = NULL;

    // Ajout en tete de liste (HEAD)
    printf("\n********* Ajout en tete de liste ***********\n");
    procAjoutEnTeteDeListe(&liste, 3, "C");
    procAjoutEnTeteDeListe(&liste, 4, "D");
    liste = funcAjoutEnTeteDeListe(liste, 5, "E");
    afficherListeAvecWhile(liste);

    // Ajout en fin de liste (HEAD)
    printf("\n********* Ajout en tete de liste ***********\n");
    procAjoutEnFinDeListe(&liste, 1, "A");
    procAjoutEnFinDeListe(&liste, 2, "B");
    afficherListeAvecWhile(liste);
    // Piocher en tête
    printf("\n********* Piocher en tete de liste *********\n");
    Maillon *recup_tete = piocheEnTeteDeListe(&liste);
    afficherListeAvecWhile(liste);
    printf("Element pioché : ");
    afficheMaillon(recup_tete);
    free(recup_tete); // liberation du maillon recupere

    // Liberation de la liste
    printf("\n********* Liberation de liste **************\n");
    libererListe(&liste);
    afficherListeAvecWhile(liste);
}