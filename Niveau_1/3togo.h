#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct token{
	int couleur;
	int forme;
	struct token* suivant;
	struct token* suivant_couleur;
	struct token* precedent_couleur;
	struct token* suivant_forme;
	struct token* precedent_forme;
}Token,*Liste;

//int allouerToken(int couleur,int forme, Liste* lst_tokens);
void generer_aleat(Liste *token);
int insererDebut(Liste token ,Liste *lst_tokens);
int insererFin(Liste token ,Liste * lst_tokens);
void genererListeAttente(Liste *lst_tokens);
void rechargerListeAttente(Liste *lst_tokens);
void enleverDernierToken(Liste *lst);
void afficherToken(Liste list);
void afficherFileAttente(Liste lst);
void afficherListeJeux(Liste lst);
void afficherMenuJeux();
int choixMenu(int *choix);
Liste recupererDernierToken(Liste lst);
void libererListe(Liste *liste);
void supprimerToken(Liste *lst1 , Liste lst2);
void detecterComboCouleur(Liste *lst);
void detecterComboCouleurDebut(Liste *lst);
void detecterComboFormeDebut(Liste *lst);
void detecterComboForme(Liste *lst);
void allCombo(Liste *list);
Liste allouerToken1(int couleur,int forme);
void determinerVoisin(Liste *token,Liste *lst_token);
void TokenVoisin(Liste *liste);
void jouer();
void afficherTest(Liste lst_tokens);

