#include <stdio.h>
#include <stdlib.h>
typedef struct Noeud
{
    int val;
    struct Noeud * gauche;
    struct Noeud * droit;
} T_Noeud;

typedef T_Noeud * T_Arbre;

T_Noeud *abr_creer_noeud(int valeur)
{
    T_Noeud* n=malloc(sizeof(T_Noeud));
    n->val=valeur;
    n->gauche=NULL;
    n->droit=NULL;
    return n;
}
void abr_afficher_noeud(T_Noeud* noeud)
{
    printf("Noeud --> %d\n",noeud->val);
    printf("      --> FG : ");
    if(noeud->gauche!=NULL)
        printf("%d",noeud->gauche->val);
    else
        printf("NULL");
    printf(" -- FD : ");
    if(noeud->droit!=NULL)
        printf("%d",noeud->droit->val);
    else
        printf("NULL");
    printf("\n");
}
void abr_prefixe(T_Arbre abr)
{
    if(abr!=NULL)
    {
        abr_afficher_noeud(abr);
        abr_prefixe(abr->gauche);
        abr_prefixe(abr->droit);
    }
}

T_Noeud* abr_pere(T_Noeud* noeud, T_Arbre *abr)
{
    T_Noeud* it = *abr;
    if(noeud==it)
        return NULL;
    while(it!=NULL && it->gauche!=noeud && it->droit!=noeud)
    {
        if(noeud->val<it->val)
            it=it->gauche;
        else
            it=it->droit;
    }
    return it;
}

void abr_inserer(int valeur,T_Arbre *abr)
{

    T_Noeud * z=abr_creer_noeud(valeur);
    T_Noeud * y=NULL;//pointer sur le noeud parent de x
    T_Noeud * x=*abr;//pour parcourir tous les noeuds
    while(x!=NULL)
    {
        y=x;
        if(z->val < x->val)
            x=x->gauche;
        else
            x=x->droit;
    }
    if(y==NULL)
        *abr=z;
    else
    {
        if(z->val < y->val )
            y->gauche=z;
        else
            y->droit=z;
    }
}

T_Noeud* abr_minimum(T_Arbre *abr)
{
    T_Noeud* it = *abr;
    while(it->gauche!=NULL)
        it=it->gauche;
    return it;
}

T_Noeud* abr_succusseur(T_Noeud* noeud, T_Arbre *abr)
{
    T_Noeud* it=noeud;
    if(noeud->droit!=NULL)
        return abr_minimum(&noeud->droit);
    T_Noeud* pere=abr_pere(noeud, abr);
    while(pere!=NULL && it==pere->droit)
    {
        it=pere;
        pere=abr_pere(pere, abr);
    }
    return pere;
}

T_Noeud* abr_rechercher(int valeur, T_Arbre *abr)
{
    T_Noeud* it = *abr;
    while(it!=NULL && valeur!=it->val)
    {
        if(valeur<it->val)
            it=it->gauche;
        else
            it=it->droit;
    }
    if(it==NULL)
    {
        printf("Noeud %d not found.\n",valeur);
        return 0;
    }
    else
    {
        return it;
    }
}

void abr_supprimer(int valeur,T_Arbre *abr)
{
    T_Noeud* z=abr_rechercher(valeur, abr);
    if(z==NULL)//z not found
        return 0;
    T_Noeud* pere=abr_pere(z,abr);
    T_Noeud* y=NULL;//successeur de z
    if(z->gauche==NULL && z->droit==NULL)//z n'a pas de fils
    {
        if(pere->gauche==z)
            pere->gauche=NULL;
        else
            pere->droit=NULL;
        free(z);
        return;
    }
    else if(z->gauche==NULL)//z n'a qu'un fils droit
    {
        if(pere->gauche==z)
            pere->gauche=z->droit;
        else
            pere->droit=z->droit;
        free(z);
        return;
    }
    else if(z->droit==NULL)//z n'a qu'un fils gauche
    {
        if(pere->gauche==z)
            pere->gauche=z->gauche;
        else
            pere->droit=z->gauche;
        free(z);
        return;
    }
    else//z possede 2 fils
    {
        y=abr_succusseur(z, abr);
        pere=abr_pere(y, abr);
        if(pere->gauche==y)
            pere->gauche=y->droit;
        else
            pere->droit=y->droit;
        z->val=y->val;
        free(y);
    }
}

void abr_clone(T_Arbre original, T_Arbre *clone, T_Noeud* parent)
{
    if(original==NULL)
    {
        printf("L'arbre original est vide.\n");
        return 0;
    }
    T_Noeud * t=abr_creer_noeud(original->val);//clone un noeud racine
    *clone=t;
    if(original->droit!=NULL)//clone sous arbre droit
    {
        T_Noeud * t1=abr_creer_noeud(original->droit->val);
        (*clone)->droit=t1;
        abr_clone(original->droit,&((*clone)->droit), original);
    }
    if(original->gauche!=NULL)//clone sous arbre gauche
    {
        T_Noeud * t2=abr_creer_noeud(original->gauche->val);
        (*clone)->gauche=t2;
        abr_clone(original->gauche,&((*clone)->gauche), original);
    }
}

int main()
{
    T_Arbre abr=NULL;
    T_Arbre abrclone=NULL;
    //abr_prefixe(abr);
    //T_Noeud* x=abr_pere(abr, &abr);
    //T_Arbre abr=NULL;
    abr_inserer(11,&abr);
    abr_inserer(2,&abr);
    abr_inserer(1,&abr);
    abr_inserer(6,&abr);
    abr_inserer(13,&abr);
    abr_inserer(12,&abr);
    abr_inserer(17,&abr);
    abr_inserer(15,&abr);
    abr_inserer(16,&abr);
    abr_inserer(19,&abr);
    abr_inserer(18,&abr);
    abr_prefixe(abr);
    //abr_rechercher(15,&abr);
    //abr_supprimer(13,&abr);
    printf("\n");
    abr_clone(abr, &abrclone, NULL);
    abr_prefixe(abrclone);
    return 0;
}
