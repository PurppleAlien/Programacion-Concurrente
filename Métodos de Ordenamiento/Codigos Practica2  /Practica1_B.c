/*
Soria Rodriguez Juan Antonio
Matricula: 2203041232
Programa: Listas Simples Ligadas
*/

#include<stdio.h>
#include<stdlib.h>

struct nodo
{
    int info;
    struct nodo *sig;
};

typedef struct nodo Nodo;

Nodo *lista=NULL;

Nodo * creanodo(int);        //
void Menu();                  //
void EjecutarOpcion(int);     //
void despliega(Nodo *lista);  //
int consulta(Nodo *lista, int); //
int elimina(Nodo **lista, int); //
int busca(Nodo *lista, int);  //
int buscarec(Nodo *lista, int, int); //
void haznula(Nodo **lista);  //
void hnrec(Nodo **lista);
void insertaord(Nodo **lista, int);   //

/***********************************************************/
/// menu // 
int main(int agrs , char *argv[])
{
    Menu();
}
/***********************************************************/
void Menu()
{
    int opc;
    do{
        system("clear");
        printf("\n\n      **==MENU PRINCIPAL==**\n\n\n");
        printf("<<1>> Inserta Ordenado.  \n");
        printf("<<2>> Despliega. \n");
        printf("<<3>> Consulta. \n");
        printf("<<4>> Elimina. \n");
        printf("<<5>> Busca. \n");
        printf("<<6>> Busca rec. \n");
        printf("<<7>> Haz Nula. \n");
        printf("<<8>> Haz Nula Rec. \n");
        printf("<<9>> Salir del Programa \n\n\n\n\n");
        printf(" Teclee una opcion... \n\n");
        scanf("%d", &opc);

        if(opc !=9){
            EjecutarOpcion(opc);
        }

    }while(opc !=9);
} 
/***********************************************************/

void EjecutarOpcion(int opc){
    int elem,pos,rc;
    int i=0;
    system("clear");
    switch (opc){
        case 1:
        printf("Escribe el elemento para Insertar: \n");
        scanf("%d",&elem);
        insertaord(&lista,elem);
        break;

        case 2:
        despliega(lista);
        break;

        case 3:
        printf("Escribe la posicion que quieres consultar: \n");
        scanf("%d",&pos);
        rc=consulta(lista,pos);
        printf("El elemento en la posicion %d es : %d ",pos,rc);
        break;

        case 4:
        printf("Escribe el nombre del elemento que quieres eliminar: \n ");
        scanf("%d",&elem);
        rc=elimina(&lista,elem);
        if(rc==-1){
            printf("El elemento no existe");
        }
        break;

        case 5:
        printf("Escribe el elemento que quieres buscar:\n ");
        scanf("%d",&elem);
        rc=busca(lista,elem);
        if(rc==-1)
        printf("No existe el elemento");
        else
        printf("El elemento en la posicion %d se encuentra en la poscicion %d . . .  ",elem,rc);
        break;

        case 6: 
        printf("Escribe el elemento que quieres buscar:\n ");
        scanf("%d",&elem);
        rc=buscarec(lista,elem,i);
        if(rc==-1)
        printf("No existe el elemento");
        else
        printf("El elemento en la posicion %d se encuentra en la poscicion %d . . .  ",elem,rc);
        break;

        case 7:
        haznula(&lista);
        break;

        case 8:
        hnrec(&lista);
        break;

        case 9:
        break;
        default:
        printf("          !!!!! La opcion tecleada no es valisa!!!!!\n\n");
    }
    getchar();
    printf("\n\nPresione 'entrer' para continuar: . . . ");
    while (getchar()!= '\n')
    ;


}
/********************************************************/

void insertaord(Nodo **lista,int elem)
{
    Nodo *nuevo, *aux1, *aux2;
    aux1=*lista;
    aux2=*lista;
    nuevo=creanodo(elem);
    while (aux1!=NULL&&(aux1->info<elem)){
        aux2=aux1;
        aux1=aux1->sig;
    }
    if(*lista == NULL){
        *lista = nuevo;
    }else{
        nuevo->sig=aux1;
        if(aux1==*lista){
            *lista=nuevo;
        }else{
            aux2->sig=nuevo;
        }
    }
}
/***********************************************************/
Nodo * creanodo(int elem)
{
    Nodo *aux;
    aux=(struct nodo *)malloc(sizeof(struct nodo));
    aux->info=elem;
    aux->sig=NULL;
    return(aux);
}
/***********************************************************/
void despliega(Nodo *lista)
{
    if (lista!=NULL)
    {
        for (struct nodo *aux=lista;aux!=NULL;aux=aux->sig)
        {
            printf("[%d]->",aux->info);
        }
        printf("NULL"); 
    }
    else
    printf("\nLa lista esta vacia");
}
/***********************************************************/
int consulta(Nodo *lista,int pos)
{
    Nodo *aux;
    if (lista!=NULL)
    {
        aux=lista;
        int i=0;
        while((aux->sig!=NULL)&&(i<pos))
        {
            aux=aux->sig;
            i++;
        }
        if (i==pos)
        return(aux->info);
        else
        return(-1);
    }
    else
    return(-1);
}

/***********************************************************/

int elimina(Nodo **lista,int elem)
{
    Nodo *aux1, *aux2;
    aux1=*lista;
    aux2=*lista;
    //si el elemento a borrar se encuentra en la primera posicion
    if((aux2->sig==NULL)&&(aux2->info==elem))
    {
        printf("\nSe ha eliminado %d de la lista",aux2->info);
        getchar();
        *lista=aux2->sig;
        free(aux2);
        return 0;
    }
    if((aux2->sig!=NULL)&&(aux2->info==elem))
    {
        printf("\nSe ha eliminado %d de la lista",aux2->info);
        getchar();
        *lista=aux2->sig;
        free(aux2);
        return 0;
    }
    aux1=*lista;
    aux2=*lista;
    while(aux1->sig!=NULL)
    {
        if(aux1->info==elem)
        {
            printf("\nSe ha eliminado %d de la lista",aux1->info);
            getchar();
            aux2->sig=aux1->sig;
            free(aux1);
            return 0;
        }
        aux2=aux1;
        aux1=aux1->sig;
    }
    //si el elemnto a borrar se encuentra en la ultima poscicion
    if((aux1->sig==NULL)&&(aux1->info==elem))
    {
        printf("\nSe ha eliminado %d de la lista",aux1->info);
        getchar();
        aux2->sig=NULL;
        free(aux1);
        return 0;
    }
    return -1;
}
/***********************************************************/
int busca(Nodo *lista,int elem)
{
    Nodo *aux;
    if(lista!=NULL)
    {
        aux=lista;
        int i=0;
        while ((aux->sig!=NULL)&&(aux->info!=elem))
        {
            aux=aux->sig;
            i++;
        }
        if (aux->info==elem)
        return(i);
        else
        return (-1);
    }
    else
    return (-1);
}
/***********************************************************/

int buscarec(Nodo *lista,int elem,int i)
{
    int rc;
    Nodo *aux;
    aux=lista;
    if(aux->info==elem)
    return(i);
    else
    {
        if(lista!=NULL)
        {
            aux=aux->sig;
            i++;
            lista=aux;
            rc=buscarec(lista,elem,i);
            return (rc);
        }
        else
        return (-1);
    }
}
/***********************************************************/

void haznula(Nodo **lista)
{
    Nodo *aux;
    aux=*lista;
    while(*lista!=NULL)
    {
        *lista=aux->sig;
        free(aux);
        aux=*lista;
    }
    printf("\nLa lista se ha vaciado");
}

/***********************************************************/
void hnrec(Nodo **lista)
{
    Nodo *aux;
    aux=*lista;
    *lista=aux->sig;
    free(aux);
    if(*lista!=NULL)
    {
        hnrec(lista);
    }
    else
    printf("\nLa lista se ha vaciado");
}






