#include "3togo_graph.h"
#include <MLV/MLV_all.h>

# define diviseur 1.5
# define longueur 800/diviseur 
# define largeur 1600/diviseur 
# define cote_commun 60/diviseur


int main(int argc, char const *argv[]){
	srand(time(NULL));
	MLV_create_window( "3 To GO", "3 To GO", largeur, longueur);
	jouerGraph();
	MLV_free_window();	
	return 0;
}


int allouerToken(int couleur,int forme, Liste *lst_tokens){
	*lst_tokens=(Token*)malloc(sizeof(Token));

	if ((*lst_tokens)!= NULL){
		(*lst_tokens)->couleur = couleur;
		(*lst_tokens)->forme = forme;
		(*lst_tokens)->suivant = *lst_tokens;
		(*lst_tokens)->suivant_couleur = *lst_tokens;
		(*lst_tokens)->precedent_couleur = *lst_tokens;
		(*lst_tokens)->suivant_forme = *lst_tokens;
		(*lst_tokens)->precedent_forme = *lst_tokens;

		return 1;
	}
	return 0;
}


void generer_aleat(Liste *token){
		int couleur ;
		int forme ;

		couleur = rand()%(4-0)+0;
		forme = rand()%(4-0)+0;
		allouerToken(couleur ,forme,&(*token)); 
}


int insererDebut(Liste token, Liste *lst_tokens){
	if((*lst_tokens) == NULL){
		*lst_tokens = token ;
		return 1 ; 
	}
	Liste temp = *lst_tokens ;
	
	Liste index = *lst_tokens ;
	while(index->suivant != temp){
		index = index -> suivant ;
	}

	index->suivant = token ;
	*lst_tokens = index ;
	*lst_tokens = temp ;
	
	token->suivant = *lst_tokens ;
	*lst_tokens = token ;

	return 1 ;
}

int insererFin(Liste token ,Liste * lst_tokens){
	if((*lst_tokens) == NULL){
		*lst_tokens = token ;
		return 1 ; 
	}
	Liste temp = *lst_tokens ;
	
	Liste index = *lst_tokens ;
	while(index->suivant != temp){
		index = index -> suivant ;
	}
	token ->suivant = temp;
	index ->suivant = token ;
	return 1 ;
}

void genererListeAttente(Liste *lst_tokens){
	int count=0;
	Liste token = NULL;
	while(count < 5){
		generer_aleat(&token);
		insererDebut(token,&(*lst_tokens));
		count +=1;
	}
}

void rechargerListeAttente(Liste *lst_tokens){
	Liste token = NULL;
	generer_aleat(&token);
	insererDebut(token,&(*lst_tokens));
}

void enleverDernierToken(Liste *lst){
	Liste index = *lst ;
	Liste tmp = *lst ;
	Liste tmp2 = index ;
	while (index->suivant != tmp){
		tmp2 = index ; 
		index = index->suivant ;
	}
	//ici je dois liberer la memoire 
	tmp2->suivant = *lst ;
}

Liste recupererDernierToken(Liste lst){
	Liste debut = lst;
	Liste index = lst;

	while(index->suivant != debut){
		index = index->suivant;
	}
	return index;
}


void libererListe(Liste *liste){
	Liste before = *liste;
	Liste tmp = *liste ;
	while (before->suivant != tmp ){//car le premier element sera null
		before = before->suivant ;
		free(*liste);
		*liste = before ;
	}
	free(*liste);
	(*liste) = NULL ;

}


void supprimerToken(Liste *lst1 , Liste lst2){
	Liste before = *lst1;
	while (before->suivant != lst2 ){
		before = (*lst1)->suivant ;
		free(*lst1);
		(*lst1) = NULL;
		(*lst1) = before;
	}
}


void detecterComboCouleur(Liste *lst){
	Liste pointeur1 = (*lst)->suivant;
	Liste pointeur2 ;
	Liste pointeur3 =*lst; 

	do{
		if ((pointeur1->suivant)->couleur == pointeur1->couleur && ((pointeur1->suivant)->suivant)->couleur == pointeur1->couleur 
			&& (pointeur1->suivant)->suivant != *lst && pointeur1->suivant != *lst){
				pointeur2 = (pointeur1->suivant)->suivant ;
				while ((pointeur2->suivant)->couleur  == pointeur1->couleur && pointeur2->suivant != *lst){
					pointeur2 = pointeur2->suivant ;
				}
				pointeur3->suivant = pointeur2->suivant ;
				supprimerToken(&pointeur1,pointeur2);
				while (pointeur3 != *lst){
					pointeur3 = pointeur3->suivant ;
			}
				*lst = pointeur3 ;
				pointeur1 = (*lst)->suivant ; 
		}	
	else{
		pointeur3 = pointeur1 ;
		pointeur1 = pointeur1->suivant ;
	}

	}while(pointeur1 != *lst);
}


void detecterComboCouleurDebut(Liste *lst){
	Liste pointeur1 = *lst;
	Liste pointeur2 = pointeur1->suivant;
	Liste pointeur3 = *lst ;
	Liste pointeur4 = *lst ;	
		if ((pointeur1->suivant)->couleur == pointeur1->couleur && ((pointeur1->suivant)->suivant)->couleur == pointeur1->couleur 
			&& (pointeur1->suivant)->suivant != *lst && pointeur1->suivant != *lst){
			pointeur2 = (pointeur1->suivant)->suivant ;
			while ((pointeur2->suivant)->couleur  == pointeur1->couleur && pointeur2->suivant != *lst){
					pointeur2 = pointeur2->suivant ;
				}
			
			while (pointeur3->suivant != (pointeur2->suivant)->suivant){
				pointeur3 = pointeur3->suivant ;
			}
			while (pointeur4->suivant != *lst){
				pointeur4 = pointeur4->suivant ;
			}
			pointeur4->suivant = pointeur3 ; 
			*lst = pointeur3 ;
			supprimerToken(&pointeur1,pointeur3->suivant);
		 }
		 else 
			return ;	
		
}


void detecterComboFormeDebut(Liste *lst){
	Liste pointeur1 = *lst;
	Liste pointeur2 = pointeur1->suivant;
	Liste pointeur3 = *lst ;
	Liste pointeur4 = *lst ;
		if ((pointeur1->suivant)->forme == pointeur1->forme && ((pointeur1->suivant)->suivant)->forme == pointeur1->forme 
			&& (pointeur1->suivant)->suivant != *lst && pointeur1->suivant != *lst){
			pointeur2 = (pointeur1->suivant)->suivant ;
			while ((pointeur2->suivant)->forme  == pointeur1->forme && pointeur2->suivant != *lst){
					pointeur2 = pointeur2->suivant ;
				}
			while (pointeur3->suivant != (pointeur2->suivant)->suivant){
				pointeur3 = pointeur3->suivant ;
			}
			while (pointeur4->suivant != *lst){
				pointeur4 = pointeur4->suivant ;
			}
			pointeur4->suivant = pointeur3 ; 
			*lst = pointeur3 ;
			supprimerToken(&pointeur1,pointeur3->suivant);
		 }
		 else 
			return ;	
		
}


void detecterComboForme(Liste *lst){
	Liste pointeur1 = (*lst)->suivant;
	Liste pointeur2 ;
	Liste pointeur3 =*lst; 


	do{
		if ((pointeur1->suivant)->forme == pointeur1->forme && ((pointeur1->suivant)->suivant)->forme == pointeur1->forme 
			&& (pointeur1->suivant)->suivant != *lst && pointeur1->suivant != *lst){
				pointeur2 = (pointeur1->suivant)->suivant ;
				while ((pointeur2->suivant)->forme  == pointeur1->forme && pointeur2->suivant != *lst){
					pointeur2 = pointeur2->suivant ;
				}
				pointeur3->suivant = pointeur2->suivant ;
				supprimerToken(&pointeur1,pointeur2);
				while (pointeur3 != *lst){
					pointeur3 = pointeur3->suivant ;
			}
				*lst = pointeur3 ;
				pointeur1 = (*lst)->suivant ; 
		}	
	else{
		pointeur3 = pointeur1 ;
		pointeur1 = pointeur1->suivant ;
	}

	}while(pointeur1 != *lst);
}


void allCombo(Liste *lst) {
	detecterComboCouleurDebut(&(*lst));
	detecterComboCouleur(&(*lst));
	detecterComboCouleurDebut(&(*lst));
	detecterComboFormeDebut(&(*lst));
	detecterComboForme(&(*lst));
	detecterComboFormeDebut(&(*lst));

}


void dessinerTriangle(coord triangle, int cote, int couleur){
	int lst_x[3] = {triangle.x,0,0};
	int lst_y[3] = {triangle.y+(cote/2),0,0};

	lst_x[1] = triangle.x + cote;
	lst_y[1] = triangle.y+(cote/2);

	lst_x[2] = triangle.x + (cote/2);
	lst_y[2] = triangle.y - cote/2;

	if(couleur == 0){
		MLV_draw_filled_polygon( lst_x, lst_y, 3, MLV_COLOR_RED);
	}
	if(couleur == 1){
		MLV_draw_filled_polygon( lst_x, lst_y, 3, MLV_COLOR_GREEN);
	}
	if(couleur == 2){
		MLV_draw_filled_polygon( lst_x, lst_y, 3, MLV_COLOR_BLUE);
	}
	if(couleur == 3){
		MLV_draw_filled_polygon( lst_x, lst_y, 3, MLV_COLOR_YELLOW);
	}	
}


void dessinerDiamant(coord diam,int cote,int couleur){
	int lst_x[4] = {diam.x,0,0,0};
	int lst_y[4] = {diam.y,0,diam.y,0};

	lst_x[1] = diam.x + (cote/2);
	lst_y[1] = diam.y + (cote/2);

	lst_x[2] = diam.x + cote;
	
	lst_x[3] = diam.x + (cote/2);
	lst_y[3] = diam.y - (cote/2);

	if(couleur == 0){
		MLV_draw_filled_polygon( lst_x, lst_y, 4, MLV_COLOR_RED);
	}
	if(couleur == 1){
		MLV_draw_filled_polygon( lst_x, lst_y, 4, MLV_COLOR_GREEN);
	}
	if(couleur == 2){
		MLV_draw_filled_polygon( lst_x, lst_y, 4, MLV_COLOR_BLUE);
	}
	if(couleur == 3){
		MLV_draw_filled_polygon( lst_x, lst_y, 4, MLV_COLOR_YELLOW);
	}	

}


//une fonction qui recoit en argument des coordonnées et un pointeur pointant vers un token
void dessinerToken(coord obj, Liste token, int cote){
	int c = token->couleur;//couleur
	int f =  token->forme;//forme

	//ROUGE
	if (c == 0){
		//CERCLE
		if (f == 0){
			MLV_draw_filled_circle( obj.x+(cote/2), obj.y,cote/2, MLV_COLOR_RED);
		}
		//CARRE
		if (f == 1){
			MLV_draw_filled_rectangle((obj.x),(obj.y)-(cote/2), cote,cote , MLV_COLOR_RED);
		}
		//TRIANGLE
		if (f == 2){
			dessinerTriangle(obj,cote,c);
		}
		//DIAMANT
		if (f == 3){
			dessinerDiamant(obj,cote,c);
		}
	}

	//VERT
	if (c == 1){
		//CERCLE
		if (f == 0){
			MLV_draw_filled_circle( obj.x+(cote/2), obj.y,cote/2, MLV_COLOR_GREEN);
		}
		//CARRE
		if (f == 1){
			MLV_draw_filled_rectangle((obj.x),(obj.y)-(cote/2), cote,cote , MLV_COLOR_GREEN);
		}
		//TRIANGLE
		if (f == 2){
			dessinerTriangle(obj,cote,c);
		}
		//DIAMANT
		if (f == 3){
			dessinerDiamant(obj,cote,c);
		}
	}

	//BLEU
	if (c == 2){
		//CERCLE
		if (f == 0){
			MLV_draw_filled_circle( obj.x+(cote/2), obj.y,cote/2, MLV_COLOR_BLUE);
		}
		//CARRE
		if (f == 1){
			MLV_draw_filled_rectangle((obj.x),(obj.y)-(cote/2), cote,cote , MLV_COLOR_BLUE);
		}
		//TRIANGLE
		if (f == 2){
			dessinerTriangle(obj,cote,c);
		}
		//DIAMANT
		if (f == 3){
			dessinerDiamant(obj,cote,c);
		}
	}

	//JAUNE
	if (c == 3){
		//CERCLE
		if (f == 0){
			MLV_draw_filled_circle( obj.x+(cote/2), obj.y,cote/2, MLV_COLOR_YELLOW);
		}
		//CARRE
		if (f == 1){
			MLV_draw_filled_rectangle((obj.x),(obj.y)-(cote/2), cote,cote , MLV_COLOR_YELLOW);
		}
		//TRIANGLE
		if (f == 2){
			dessinerTriangle(obj,cote,c);
		}
		//DIAMANT
		if (f == 3){
			dessinerDiamant(obj,cote,c);
		}
	}

}

void dessinerListeToken(coord pos, Liste lst){
	Liste index = lst;
	Liste debut = lst;

	if (lst != NULL){
		//une boucle parcourant la liste chainé de token et les dessine un par un 
		while(index->suivant != debut){
			dessinerToken(pos, index,cote_commun);
			pos.x += cote_commun+15/diviseur ;
			index = index->suivant;
		}
		dessinerToken(pos, index,cote_commun);//dessine le dernier token
	}
}


void afficherTouche(void){
	//les deux boites 
	MLV_draw_filled_rectangle(475/diviseur ,350/diviseur ,180/diviseur ,70/diviseur ,MLV_COLOR_CYAN);
	MLV_draw_filled_rectangle(950/diviseur ,350/diviseur ,180/diviseur ,70/diviseur ,MLV_COLOR_CYAN);

	//les fleches
	//de gauche:
	MLV_draw_line(505/diviseur ,385/diviseur ,625/diviseur ,385/diviseur ,MLV_COLOR_BLACK);//ligne
	MLV_draw_line(505/diviseur ,385/diviseur ,535/diviseur ,405/diviseur ,MLV_COLOR_BLACK);//bout de fleche du bas
	MLV_draw_line(505/diviseur ,385/diviseur ,535/diviseur ,365/diviseur ,MLV_COLOR_BLACK);//bout de fleche du haut
	//de droite:
	MLV_draw_line(985/diviseur ,385/diviseur ,1095/diviseur ,385/diviseur ,MLV_COLOR_BLACK);//ligne
	MLV_draw_line(1095/diviseur ,385/diviseur ,1065/diviseur ,405/diviseur ,MLV_COLOR_BLACK);//bout de fleche du bas
	MLV_draw_line(1095/diviseur ,385/diviseur ,1065/diviseur ,365/diviseur ,MLV_COLOR_BLACK);//bout de fleche du haut

	//bouton quitter
	MLV_draw_adapted_text_box(1527/diviseur-25,1,"QUITTER", 5/2 ,MLV_COLOR_RED,MLV_COLOR_BLACK,MLV_COLOR_RED,MLV_TEXT_CENTER);
}

Liste clicToken(Liste lst_token,coord pos_lj,int x, double l, int nb_token, int *pos){
	int pos_token = 1;
	int count = 0;
	int pas = 0;

	pas = l/nb_token;
	count = pas;

	while(count < l){
		if( x > count){
			count += pas;
			pos_token += 1;
		}
		if (x <= count){
			break;
		}
	}
	*pos = pos_token;
	printf("%d\n",pos_token );
	Liste index = lst_token;
	int n_token = 1;

	while(n_token != pos_token){
		index = index->suivant;
		n_token += 1;
	}
	return index;
}

//une fonction qui prend en argument le nombre de token de la liste jouer et la position  du debut du dessin attend un clic et va renvoyer un chiffre entre 0 et 2 qui donnera ensuite l'instruction a realiser
int clicJoueur(coord pos_lstj,int nb_token, int *x_clic){
	int x ,y ;
	int choix;

	do{
		MLV_wait_mouse(&x,&y);
		//quitter
		if((x > 1529/diviseur  && x<1600/diviseur ) && (y>0 && y < 24)){
			choix = 0;
		}
		//gauche donc inserer debut
		else if ((x > 475/diviseur  && x < 675/diviseur )&& (y > 350/diviseur  && y < 420/diviseur )){
		 	choix = 1;
		 }
		 //droite donc inserer fin
		else if ((x > 950/diviseur  && x < 1130/diviseur )&& (y > 350/diviseur  && y < 420/diviseur )){
		 	choix = 2;
		}
		else if(y > pos_lstj.y-(cote_commun/2) && y < pos_lstj.y+(cote_commun/2)){
			if(x > pos_lstj.x && x < pos_lstj.x+(cote_commun+15/diviseur)*(nb_token)){
				choix = 3;
				*x_clic = x;
			}else{choix = -1;}
		}
		else{
			choix = -1;
		}
	}while(choix < 0);

	return choix;
}


int compterToken(Liste lst_tokens){
	Liste debut = lst_tokens;
	Liste index = lst_tokens;
	int count = 1;
	if (lst_tokens == NULL){
		return 0;
	}

	while(index->suivant != debut){
		index = index->suivant;
		count+=1;
	}
	return count;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------*/

void determinerVoisin(Liste *token,Liste *lst_token){
	
	Liste index_suiv_coul = *token;
	Liste index_suiv_form = *token;
	//printf("%p\n",index_suiv_coul );
	//premier parcours pour le suivant couleur
	
	do{
		index_suiv_coul = index_suiv_coul->suivant;
	}while(index_suiv_coul->couleur != (*token)->couleur && index_suiv_coul != *token);
	(*token)->suivant_couleur = index_suiv_coul;//quand on trouve le token suivant

	//deuxieme parcours pour le suivant forme
	
	do{
		index_suiv_form = index_suiv_form->suivant;
	}while(index_suiv_form->forme != (*token)->forme && index_suiv_form != *token);
	(*token)->suivant_forme = index_suiv_form;

/*
	Liste index_prec_coul = *lst_token;
	Liste index_prec_form = *lst_token;
*/
	Liste index_prec_coul = *token;
	Liste index_prec_form = *token;

	printf("%p\n",index_prec_coul );
	//premier parcours pour le precedent forme
	(*token)->precedent_couleur = (*token);
	do{
		if (index_prec_coul->couleur == (*token)->couleur)
			(*token)->precedent_couleur = index_prec_coul;	
		index_prec_coul = index_prec_coul->suivant;
	}while( index_prec_coul != *token);

	//deuxieme parcours pour le precedent forme
	(*token)->precedent_forme = (*token);
	do{
		if(index_prec_form->forme == (*token)->forme) 
			(*token)->precedent_forme = index_prec_form;	
		index_prec_form = index_prec_form->suivant;
	}while(index_prec_form != *token);
}


void TokenVoisin(Liste *liste){
	Liste index = *liste ;
	Liste tmp = *liste ;
	do
	{
		determinerVoisin(&index,&(*liste));
		index = index->suivant ;
	} while (index != tmp);
}




void decaleCouleur(Liste *token){
	Liste tmp = *token ;
	int a = (*token)->forme ;
	do {
		if ((*token)->forme == a){
			decaleCouleurToken(&(*token));
		}
		(*token) = (*token)->suivant ;
	}while((*token) != tmp);
}

void decaleForme(Liste *token){
	Liste tmp = *token ;
	int a = (*token)->couleur ;
	do {
		if ((*token)->couleur == a){  
			decaleFormeToken(&(*token));
		}
		(*token) = (*token)->suivant ;
	}while((*token) != tmp);
}

void decaleCouleurToken(Liste *token){
	int a = 0 ;
	a = (*token)->couleur ;

	(*token)->couleur = ((*token)->precedent_forme)->couleur ;
	((*token)->precedent_forme)->couleur =  a;
}

void decaleFormeToken(Liste *token){
	int a = 0 ;

	a = (*token)->forme ;
	
	(*token)->forme = ((*token)->precedent_couleur)->forme ;
	((*token)->precedent_couleur)->forme =  a;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


void jouerGraph(void){
	Liste fil_attente = NULL;
	Liste lst_jouer = NULL;

	Liste token_inserer = NULL;

	int choix_joueur;
	//des variables qui vont servir pour calculer le score;
	int nb_token_debut = 0;
	int nb_token_fin = 0;
	int score = 0;
	char text_score[50];

	genererListeAttente(&fil_attente);
	coord pos_attente;
	pos_attente.x = 435/diviseur;
	pos_attente.y = 200/diviseur ;

	coord pos_jouer;
	pos_jouer.y = 600/diviseur ;

	//declaration de variable
	int temp = 0;
	char temp_text[50];
	int clic_x;
	Liste token_clic = NULL;
	int n_token;

	do{
		MLV_clear_window(MLV_COLOR_BLACK);//vide la fenetre
		dessinerListeToken(pos_attente,fil_attente);//affiche la file d'attente
		nb_token_debut = compterToken(lst_jouer);//on compte les token et on stock la valeur dans la variable
		pos_jouer.x = 770/diviseur -(30/diviseur *nb_token_debut);//on definit la position pour dessiner le premier token de la liste avec les token qui sont inserer
		dessinerListeToken(pos_jouer,lst_jouer);//on affiche la liste jouer 
		MLV_draw_rectangle(pos_attente.x+298/diviseur,pos_attente.y-(cote_commun/2),cote_commun+3,cote_commun+3,MLV_COLOR_WHITE);//dessine le carre blanc
		afficherTouche();//affiche les touches gauche droite quitter
		sprintf(text_score,"Score: %d",score);//convertit le score pour le print 
		MLV_draw_adapted_text_box(0,0,text_score,15/diviseur ,MLV_COLOR_RED,MLV_COLOR_PURPLE,MLV_COLOR_PINK,MLV_TEXT_CENTER);//affiche le score
		temp = MLV_get_time();//une fonction qui va recupere le temps depuis le lancement du jeux
		sprintf(temp_text,"Temps écoulés: %ds/120s",temp/1000 );//convertit le temps pour un char
		MLV_draw_adapted_text_box(1400/diviseur-55 ,750/diviseur-15 ,temp_text,20/diviseur ,MLV_COLOR_GREEN,MLV_COLOR_BLUE,MLV_COLOR_WHITE,MLV_TEXT_CENTER);//affiche le temps
		MLV_actualise_window();//actualise la fenentre avc tous les dessins
		
		if (lst_jouer != NULL){
			TokenVoisin(&lst_jouer);
		}

		choix_joueur = clicJoueur(pos_jouer,nb_token_debut,&clic_x);//attente du clic du joueur dans une des cases

		switch(choix_joueur){

			case 1:
				token_inserer = recupererDernierToken(fil_attente);
				enleverDernierToken(&fil_attente);
				rechargerListeAttente(&fil_attente);
				if (lst_jouer != NULL){
					insererDebut(token_inserer,&lst_jouer);	
				}
				else 
					allouerToken(token_inserer->couleur,token_inserer->forme,&lst_jouer);
				break;
			case 2:
				token_inserer = recupererDernierToken(fil_attente);
				enleverDernierToken(&fil_attente);
				rechargerListeAttente(&fil_attente);
				if (lst_jouer != NULL){
					insererFin(token_inserer,&lst_jouer);
				}
				else 
					allouerToken(token_inserer->couleur,token_inserer->forme,&lst_jouer);
				break;

			case 3:
				token_clic = clicToken(lst_jouer,pos_jouer,clic_x,pos_jouer.x+(cote_commun+15/diviseur)*(nb_token_debut+1),nb_token_debut,&n_token);
				printf("forme = %d et couleur = %d.\n",token_clic->forme,token_clic->couleur );
				//affichage choix decalage
				decaleCouleur(&token_clic);
				break;

			case 0:
				libererListe(&fil_attente);
				if(lst_jouer != NULL)
					libererListe(&lst_jouer);
				break;
		}
		if (fil_attente != NULL)
			allCombo(&lst_jouer);
		nb_token_fin = compterToken(lst_jouer);

		//on a compter le nombre de token avant et apres la detection des combo ainsi on aure le nombre de token ayant disparu et donc le score a rajouter
		if(nb_token_debut > nb_token_fin){
			score += (nb_token_debut - nb_token_fin)+1;
		}
		if ((temp/1000) > 120){
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_draw_adapted_text_box(800/diviseur,400/diviseur ,"TEMPS ECOULE !",15/diviseur ,MLV_COLOR_YELLOW,MLV_COLOR_GREEN,MLV_COLOR_WHITE,MLV_TEXT_CENTER);
			MLV_actualise_window();
			MLV_wait_seconds(3);
			break;
		}
	}while(choix_joueur != 0);

}

