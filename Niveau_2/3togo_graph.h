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

typedef struct coord{
	int x;
	int y;
}coord;

int allouerToken(int couleur,int forme, Liste* lst_tokens);
void generer_aleat(Liste *token);
int insererDebut(Liste token ,Liste *lst_tokens);
int insererFin(Liste token ,Liste * lst_tokens);
void genererListeAttente(Liste *lst_tokens);
void rechargerListeAttente(Liste *lst_tokens);
void enleverDernierToken(Liste *lst);
void afficherToken(Liste list);
Liste recupererDernierToken(Liste lst);
void libererListe(Liste *liste);
void supprimerToken(Liste *lst1 , Liste lst2);
void detecterComboCouleur(Liste *lst);
void detecterComboCouleurDebut(Liste *lst);
void detecterComboFormeDebut(Liste *lst);
void detecterComboForme(Liste *lst);
void allCombo(Liste *list);
void dessinerTriangle(coord triangle, int cote, int couleur);
void dessinerDiamant(coord diam,int cote,int couleur);
void dessinerToken(coord obj, Liste token,int cote);
void dessinerListeToken(coord pos,Liste lst_att);
void afficherTouche(void);
Liste clicToken(Liste lst_token,coord pos_lj,int x, double l, int nb_token,int *pos);
int clicJoueur(coord pos_lstj,int nb_token,int *x_clic);
int compterToken(Liste lst_tokens);
void determinerVoisin(Liste *token,Liste *lst_token);
void TokenVoisin(Liste *liste);
void decaleCouleur(Liste *token);
void decaleForme(Liste *token);
void decaleCouleurToken(Liste *token);
void decaleFormeToken(Liste *token);
void jouerGraph(void);