#include "3togo.h"

int main(int argc, char const *argv[]){
	printf("-----------------------------3 TO GO-----------------------------\n");
	srand(time(NULL));
	jouer();
	return 0;

}


//une fonction qui va prendre en parametre deux chiffre pour la couleur et la forme et enfin un pointeur pour garder l'adresse de la case mémoire allouer
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
	tmp2->suivant = *lst ;
}


void afficherToken(Liste list){
	Liste index = list ;
	Liste tmp = list ;
	Liste tmp2 = index ;

	do{
		if (tmp2->couleur == 0){
			if (tmp2->forme == 0)
				printf("O ");
			if (tmp2->forme == 1)
				printf("C ");
			if (tmp2->forme == 2)
				printf("T ");
			if (tmp2->forme == 3)
				printf("D ");
			printf("r-->");
		}
		if (tmp2->couleur == 1){
			if (tmp2->forme == 0)
				printf("O ");
			if (tmp2->forme == 1)
				printf("C ");
			if (tmp2->forme == 2)
				printf("T ");
			if (tmp2->forme == 3)
				printf("D ");
			printf("v-->");
		}
		if (tmp2->couleur == 2){
			if (tmp2->forme == 0)
				printf("O ");
			if (tmp2->forme == 1)
				printf("C ");
			if (tmp2->forme == 2)
				printf("T ");
			if (tmp2->forme == 3)
				printf("D ");
			printf("b-->");
		}
		if (tmp2->couleur == 3){
			if (tmp2->forme == 0)
				printf("O ");
			if (tmp2->forme == 1)
				printf("C ");
			if (tmp2->forme == 2)
				printf("T ");
			if (tmp2->forme == 3)
				printf("D ");
			printf("j-->");
		} 
		tmp2 = tmp2->suivant ;
	}while(tmp2 != tmp);
	printf(">");
	printf("\n");

}

//affichage de la liste des token a placer dans la liste des token pouvant etre combo
void afficherFileAttente(Liste lst){
	printf("Tokens à placer:\n");
	afficherToken(lst);
}

//fonction affichant les tokens pouvant disparaitre par combo
void afficherListeJeux(Liste lst){
	if (lst == NULL )
		printf(">\n");
	else {
		printf("Liste des tokens:\n");
		afficherToken(lst);
	}
}

void afficherMenuJeux(){
	printf("-------MENU-------\n");
	printf("Veuillez choisir un chiffre entre 1 et 3:\n");
	printf("1: Insertion en début de liste.\n");
	printf("2: INsertion en fin de liste.\n");
	printf("3: Quitter.\n");
}

int choixMenu(int *choix){

	do{
		afficherMenuJeux();
		scanf("%d",&(*choix));
	}while(*choix > 3 || *choix < 0);
	return *choix;
}

Liste recupererDernierToken(Liste lst){
	Liste debut = lst;
	Liste index = lst;

	while(index->suivant != debut){
		index = index->suivant;
	}
	return index;
}

//-------------------------------------------------------------------------------------------------------------------------


void libererListe(Liste *liste){
	Liste before = *liste;
	Liste tmp = *liste ;
	while (before->suivant != tmp ){//car le premier element sera null
		Token* t = before;
		free(t);
		before = before->suivant ;
	}
	free(before);
	(before) = NULL ;

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
//---------------------------------------------------comment





void afficherTest(Liste lst_tokens){
	// cette fonction pour bien voir le bon fonctionnement 
	Liste adr_temp = lst_tokens ;
	Liste index = lst_tokens ;

	printf("-%p/%p-,",index->suivant_couleur,index);
	index = index->suivant;
	while (index!= adr_temp ){
		printf("-%p/%p-,",index->suivant_couleur,index);
		index = index->suivant ;
	}
	printf("\n");
}







//----------------------------------------------------comment

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

//-------------------------------------------------------------------------------------------------------------------------
void allCombo(Liste *lst) {
	detecterComboCouleurDebut(&(*lst));
	detecterComboCouleur(&(*lst));
	detecterComboCouleurDebut(&(*lst));
	detecterComboFormeDebut(&(*lst));
	detecterComboForme(&(*lst));
	detecterComboFormeDebut(&(*lst));
}




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


	Liste index_prec_coul = *lst_token;
	Liste index_prec_form = *lst_token;

	//premier parcours pour le precedent forme
	do{
		index_prec_coul = index_prec_coul->suivant;
	}while(index_prec_coul->couleur != (*token)->couleur && index_prec_coul != *lst_token);
	(*token)->precedent_couleur = index_prec_coul;

	//deuxieme parcours pour le precedent forme
	do{
		index_prec_form = index_prec_form->suivant;
	}while(index_prec_form->couleur != (*token)->couleur && index_prec_form != *lst_token);
	(*token)->precedent_forme = index_prec_form;
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


void jouer(){
	Liste fil_attente = NULL;
	Liste jouer = NULL;
	Liste tmp ;
	//allouerToken(1,2,&jouer);
	Liste token_inserer = NULL;
	int choix = NULL;

	genererListeAttente(&fil_attente);

	do{
		afficherFileAttente(fil_attente);
		afficherListeJeux(jouer);
		if (jouer != NULL){
			TokenVoisin(&jouer);
		}
		choixMenu(&choix);
		switch(choix){
			case 1:
				token_inserer = recupererDernierToken(fil_attente);
				enleverDernierToken(&fil_attente);
				rechargerListeAttente(&fil_attente);
				if (jouer != NULL){
					insererDebut(token_inserer,&jouer);
					}
				else 
					allouerToken(token_inserer->couleur,token_inserer->forme,&jouer);
				break;
			case 2:
				token_inserer = recupererDernierToken(fil_attente);
				enleverDernierToken(&fil_attente);
				enleverDernierToken(&fil_attente);
				
				rechargerListeAttente(&fil_attente);
				if (jouer != NULL){
					insererFin(token_inserer,&jouer);
					}
				else 
					allouerToken(token_inserer->couleur,token_inserer->forme,&jouer);
				break;
			case 3:
				printf("Vous avez quitté.\n");
				afficherTest(jouer);
				libererListe(&fil_attente);

				if (jouer != NULL){
					libererListe(&jouer);
					TokenVoisin(&jouer);
				}
				break;
		}

		//il faut tester car dans le cas ou le joueur quitte les listes sont liberées donc il ne faut pas tester si il y a un combo
		if (fil_attente != NULL){
			allCombo(&jouer);
		}
	}while(choix != 3);
	//afficherTest(jouer);
}	




