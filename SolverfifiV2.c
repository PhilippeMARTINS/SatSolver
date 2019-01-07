#include <stdlib.h>
#include <stdio.h>

struct maillon
{
	int valeur;
	struct maillon*next;
};
typedef struct maillon liste;

liste * creation_maillon(int n)
{
	liste*l;
	l=(liste*)malloc(sizeof(liste));
	l->next=NULL;
	l->valeur=n;
	return l;
}

void affichage_liste(liste * l)
{
	liste*a;
	for(a=l;a;a=a->next)
	{
		printf("%d",a->valeur);
		if (a->next) printf("->");
	}
	printf("\n");
}

liste*ajoute_queue ( liste *l , int val)
{
	liste *e = creation_maillon (val);
	e->next=0;
	if(!l) return e;
	liste*m;
	m=l;
	while(m->next)
	{
		m=m->next;
	}
	m->next=e;
	return l;
}

int nblignes(){
        FILE* fichier = NULL;
        fichier = fopen("test.txt", "r");
        int c;
        int nblignes = 0;
        while((c=fgetc(fichier)) != EOF)
        {
        if(c=='\n')
		nblignes++;
        }
        fclose(fichier);
        return nblignes;
}

void purge(void)
{
    int c;
    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
    }
}

int demander()
{
    int x;
               do
            {
                printf("\nVeuillez rentrez une valeur 0(x)/1(non x) ou 2(x ou non x) pour toute valeur pour cet colonne\n");
                scanf("%d",&x);
                if(x!=0 && x!=1 &&x!=2) printf("ERREUR!\n"); purge();
            }while(x!=0 && x!=1&&x!=2);
    return x;
}

int ou()
{
	int x;
               do
            {
                printf("\nVeuillez rentrez 0 si vous souhaitez que toutes les conditions soient verifiees (A et B) \n ou 1 si une seule condition suffit (A ou B)\n");
                scanf("%d",&x);
                if(x!=0 && x!=1) printf("ERREUR!\n"); purge();
            }while(x!=0 && x!=1);
    return x;
}

int choix()
{
	int x;
               do
            {
                printf("\nVeuillez rentrez:\n");
                printf("\n0 si vous souhaitez que toutes les conditions soient verifiees (A et B et C)\n");
                printf("\n1 si une seule condition suffit (A ou B ou C)\n");
                printf("\n2 si la 1ere ou la 2eme condition peut etre fausse (A ou B et C)\n");
                printf("\n3 si la 2eme ou la 3eme condition peut etre fausse (A et B ou C)\n");
                scanf("%d",&x);
                if(x!=0 && x!=1 && x!=2 && x!=3) printf("ERREUR!\n"); purge();
            }while(x!=0 && x!=1 && x!=2 && x!=3);
    return x;
}

int parcourir_liste(liste * l,int a,int b,int c,int mode, int d, int e)
{

    {

        if(l->valeur==a || a==2)
        {
        	if (mode==2 && d==1) {return 1;}
        	if (mode==3 && e==1) {return 1;}

            l=l->next;

            if (mode==3 && e==2)
            {
            	l=l->next;
                if(l->valeur==c|| c==2) {return 1;}
                else {return 0;}
			}

            if(l->valeur==b || b==2)
            {
            	if (mode==3 && e==3) {return 1;}

                l=l->next;
                if(l->valeur==c|| c==2) {return 1;}
                else {return 0;}
            }

            if (mode==3 && e==3)
            {
            	l=l->next;
                if(l->valeur==c|| c==2) {return 1;}
                else {return 0;}
			}

            else {return 0;}
        }

        if(l->valeur!=a && ((mode==2 && d==1) || (mode==3 && (e==1 || e==2))))
        {
        	l=l->next;
        	if(l->valeur==b || b==2)
            {
                l=l->next;
                if(l->valeur==c|| c==2) {return 1;}
                else {return 0;}
            }

            if(l->valeur!=b && mode==3 && e==1)
            {
                l=l->next;
                if(l->valeur==c|| c==2) {return 1;}
                else {return 0;}
            }
            else {return 0;}
		}

        else {return 0;}
    }
}


int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
    fichier = fopen("test.txt", "r");
    int mode;
    int cmpt = 0;
    int solver[3];
    int a=3,b=3,c=3,i=0,d=2,e=4;


    if (fichier != NULL)
    	{
            int taille=nblignes();
            liste *tab[taille];
            //fseek(fichier, 0, SEEK_SET);

            printf("Contenu du Fichier\n");
            printf("A  B  C\n");
            do
            {
                fscanf(fichier, "%d %d %d", &solver[0], &solver[1], &solver[2]);
                liste *s = creation_maillon(solver[0]);
                s = ajoute_queue (s, solver[1]);
                s = ajoute_queue (s, solver[2]);
                tab[cmpt]=s;
                liste *n = tab[cmpt];
                affichage_liste(n);
                cmpt++;
            }while(fgetc(fichier) != EOF);
            fclose(fichier);

            do
            {
                printf("\nVeuillez choisir le nombre de variables que vous voulez pour l'equation \ tapez 1, 2 ou 3 \n ");
                scanf("%d",&mode);
                if(mode!=1 && mode!=2 &&mode!=3) printf("ERREUR!\n"); purge();
            }while(mode!=1 && mode !=2 && mode!=3);

            if (mode==1) {e=0; d=0; a=demander(); b=2; c=2;}
            if (mode==2) {e=0; d=ou(); a=demander(); b=demander(); c=2;}
            if (mode==3) {e=choix(); d=0; a=demander(); b=demander();c=demander();}

            FILE* resultat = NULL;
            resultat = fopen("resultat.txt", "w");
            fprintf(resultat, "Voici le résultat\n");
            fprintf(resultat, "A  B  C  RES\n");
            for(i=0;i<taille+1;i++)
            {
                liste * l = tab[i];
                fprintf(resultat,"%d->",l->valeur);
                l=l->next;
                fprintf(resultat,"%d->",l->valeur);
                l=l->next;
                fprintf(resultat,"%d",l->valeur);
                int x=parcourir_liste(tab[i],a,b,c,mode,d,e);
                fprintf(resultat,"  %d\n",x);
            }
            printf("\nLe resultat a bien ete integre\n");
            fclose(resultat);

    	}
    	else
    	{
        	// On affiche un message d'erreur si on veut
        	printf("Impossible d'ouvrir le fichier test.txt");
    	}
    return 0;
}
