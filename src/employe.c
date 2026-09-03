#include <stdio.h>
#include <string.h>

#define MAX 100

// ===== STRUCTURE EMPLOYÉ =====
typedef struct {
    int id;
    char nom[30];
    char prenom[30];
    char dateNaissance[11]; // JJ/MM/AAAA
    int genre;              // 0=Homme, 1=Femme
    float salaireBrut;
    float ir;
    float salaireNet;
    int statutMatrimonial;  // 0=Celibataire, 1=Marie
    int niveauEtude;        // 1=DEUG, 2=Licence, 3=Master, 4=Doctorat
    int nombredenfant;
} Employe;

/* ======================================================
   CALCUL DE L’IR ET DU SALAIRE NET
   ====================================================== */
void calculIR(Employe *e) {
    if (e->salaireBrut <= 3000)
        e->ir = 0;
    else if (e->salaireBrut <= 6000)
        e->ir = e->salaireBrut * 0.10;
    else if (e->salaireBrut <= 10000)
        e->ir = e->salaireBrut * 0.20;
    else
        e->ir = e->salaireBrut * 0.30;

    e->salaireNet = e->salaireBrut - e->ir;
}

/* ============================
   AJOUTER UN EMPLOYÉ
   ============================ */
void ajouterEmploye(Employe *tab, int *n) {
    printf("ID : ");
    scanf("%d", &tab[*n].id);

    printf("Nom : ");
    scanf("%s", tab[*n].nom);

    printf("Prenom : ");
    scanf("%s", tab[*n].prenom);

    printf("Date de naissance (JJ/MM/AAAA) : ");
    scanf("%s", tab[*n].dateNaissance);

    printf("Salaire brut : ");
    scanf("%f", &tab[*n].salaireBrut);

    printf("Genre (0=Homme,1=Femme) : ");
    scanf("%d", &tab[*n].genre);

    printf("Niveau d'etude (1=DEUG,2=Licence,3=Master,4=Doctorat) : ");
    scanf("%d", &tab[*n].niveauEtude);

    printf("Statut matrimonial (0=Celibataire,1=Marie) : ");
    scanf("%d", &tab[*n].statutMatrimonial);

    printf("Nombre d'enfants : ");
    scanf("%d", &tab[*n].nombredenfant);

    calculIR(&tab[*n]);  // Calcul IR et salaire net

    (*n)++;
    printf("Employe ajoute avec succes.\n");
}

/* ============================
   AFFICHER LES EMPLOYÉS
   ============================ */
void afficherEmployes(Employe *tab, int n) {
    int i;
    if (n == 0) {
        printf("Aucun employe.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        printf("ID: %d | %s %s\n", tab[i].id, tab[i].nom, tab[i].prenom);
        printf("Date de naissance: %s\n", tab[i].dateNaissance);
        printf("Salaire Brut: %.2f | IR: %.2f | Salaire Net: %.2f\n",
               tab[i].salaireBrut, tab[i].ir, tab[i].salaireNet);

        // Affichage sexe
        if(tab[i].genre == 0)
            printf("Sexe: Homme\n");
        else
            printf("Sexe: Femme\n");

        // Statut matrimonial
        if(tab[i].statutMatrimonial == 0)
            printf("Statut matrimonial: Celibataire\n");
        else
            printf("Statut matrimonial: Marie\n");

        // Nombre d'enfants
        printf("Nombre d'enfants: %d\n", tab[i].nombredenfant);

        // Niveau d'étude
        printf("Niveau d'etude: ");
        if (tab[i].niveauEtude == 1) printf("DEUG\n");
        else if (tab[i].niveauEtude == 2) printf("Licence\n");
        else if (tab[i].niveauEtude == 3) printf("Master\n");
        else if (tab[i].niveauEtude == 4) printf("Doctorat\n");
        else printf("Inconnu\n");

        printf("-------------------------------\n");
    }
}

/* ============================
   MODIFIER UN EMPLOYÉ
   ============================ */
void modifierEmploye(Employe *tab, int n) {
    int id, trouve=0;
    char rep;
    float nouveauSalaire;
    int nouveauStatut, nouveauNiveau, nouveauNbEnfants;
    printf("Donner l'ID de l'employe a modifier : ");
    scanf("%d", &id);

    for (int i=0; i<n; i++) {
        if (tab[i].id == id) {
            // Modifier salaire
            printf("Modifier le salaire brut ? (o=oui,n=non) : ");
            scanf(" %c", &rep);
            if(rep=='o'||rep=='O') {
                printf("Nouveau salaire brut : ");
                scanf("%f", &nouveauSalaire);
                tab[i].salaireBrut = nouveauSalaire;
                calculIR(&tab[i]);
            }

            // Modifier statut matrimonial
            printf("Modifier le statut matrimonial ? (o=oui,n=non) : ");
            scanf(" %c", &rep);
            if(rep=='o'||rep=='O') {
                printf("Nouveau statut matrimonial (0=Celibataire,1=Marie) : ");
                scanf("%d", &nouveauStatut);
                tab[i].statutMatrimonial = nouveauStatut;
            }

            // Modifier niveau d'étude
            printf("Modifier le niveau d'etude ? (o=oui,n=non) : ");
            scanf(" %c", &rep);
            if(rep=='o'||rep=='O') {
                printf("Nouveau niveau d'etude (1=DEUG,2=Licence,3=Master,4=Doctorat) : ");
                scanf("%d", &nouveauNiveau);
                tab[i].niveauEtude = nouveauNiveau;
            }

            // Modifier nombre d'enfants
            printf("Modifier le nombre d'enfants ? (o=oui,n=non) : ");
            scanf(" %c", &rep);
            if(rep=='o'||rep=='O') {
                printf("Nouveau nombre d'enfants : ");
                scanf("%d", &nouveauNbEnfants);
                tab[i].nombredenfant = nouveauNbEnfants;
            }

            printf("Employe modifie avec succes.\n");
            trouve = 1;
            return;
        }
    }

    if(!trouve)
        printf("Employe non trouve.\n");
}

/* ============================
   SUPPRIMER UN EMPLOYÉ
   ============================ */
void supprimerEmploye(Employe *tab, int *n) {
    int id;
    printf("Donner l'ID de l'employe a supprimer : ");
    scanf("%d", &id);

    for (int i=0; i<*n; i++) {
        if (tab[i].id == id) {
            for (int j=i; j<*n-1; j++)
                tab[j] = tab[j+1];
            (*n)--;
            printf("Employe supprime avec succes.\n");
            return;
        }
    }

    printf("Employe non trouve.\n");
}

/* ============================
   MASSE SALARIALE
   ============================ */
void massesalariale(Employe *tab, int n) {
    float total=0;
    for(int i=0;i<n;i++)
        total += tab[i].salaireBrut;
    printf("MASSE SALARIALE = %.2f\n", total);
}

/* ============================
   SALAIRE MOYEN
   ============================ */
void salaireMoyen(Employe *tab, int n) {
    if(n==0){ printf("Aucun employe.\n"); return; }
    float total=0;
    for(int i=0;i<n;i++) total += tab[i].salaireBrut;
    printf("Salaire moyen = %.2f\n", total/n);
}

/* ============================
   SAUVEGARDE DANS UN FICHIER
   ============================ */
void sauvegarderFichier(Employe *tab, int n) {
    FILE *f = fopen("employes.txt","w");
    if(!f){ printf("Erreur ouverture fichier.\n"); return; }

    fprintf(f,"%d\n", n);
    for(int i=0;i<n;i++){
        fprintf(f,"%d %s %s %s %.2f %.2f %.2f %d %d %d %d\n",
                tab[i].id, tab[i].nom, tab[i].prenom, tab[i].dateNaissance,
                tab[i].salaireBrut, tab[i].ir, tab[i].salaireNet,
                tab[i].genre, tab[i].niveauEtude,
                tab[i].statutMatrimonial, tab[i].nombredenfant);
    }

    fclose(f);
    printf("Sauvegarde reussie.\n");
}

/* ============================
   CHARGEMENT DEPUIS UN FICHIER
   ============================ */
void chargerFichier(Employe *tab, int *n) {
    FILE *f = fopen("employes.txt","r");
    if(!f){ printf("Fichier inexistant.\n"); return; }

    fscanf(f,"%d", n);
    for(int i=0;i<*n;i++){
        fscanf(f,"%d %s %s %s %f %f %f %d %d %d %d",
               &tab[i].id, tab[i].nom, tab[i].prenom, tab[i].dateNaissance,
               &tab[i].salaireBrut, &tab[i].ir, &tab[i].salaireNet,
               &tab[i].genre, &tab[i].niveauEtude,
               &tab[i].statutMatrimonial, &tab[i].nombredenfant);
    }

    fclose(f);
    printf("Chargement reussi.\n");
}

/* ============================
   PROGRAMME PRINCIPAL
   ============================ */
int main() {
    Employe tab[MAX];
    int n=0, choix;

    do{
        printf("\n--- MENU ---\n");
        printf("1. Ajouter un employe\n");
        printf("2. Afficher les employes\n");
        printf("3. Modifier un employe\n");
        printf("4. Supprimer un employe\n");
        printf("5. Masse salariale\n");
        printf("6. Salaire moyen\n");
        printf("7. Sauvegarder dans fichier\n");
        printf("8. Charger depuis fichier\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        if(choix==1) ajouterEmploye(tab,&n);
        else if(choix==2) afficherEmployes(tab,n);
        else if(choix==3) modifierEmploye(tab,n);
        else if(choix==4) supprimerEmploye(tab,&n);
        else if(choix==5) massesalariale(tab,n);
        else if(choix==6) salaireMoyen(tab,n);
        else if(choix==7) sauvegarderFichier(tab,n);
        else if(choix==8) chargerFichier(tab,&n);
        else if(choix==0) printf("Fin du programme.\n");
        else printf("Choix invalide.\n");

    }while(choix!=0);

    return 0;
}
