#ifndef TDA_LISTA_H_INCLUDED
#define TDA_LISTA_H_INCLUDED
struct nodo
{
    Pedido vipd;
    struct nodo *puntero_siquiente;
} ;
typedef struct nodo Tipo_nodo;

typedef struct
{
    Tipo_nodo *acc; /* acceso a la lista */
    Tipo_nodo *cur; /* cursor de la lista */
    Tipo_nodo *aux; /* cursor auxiliar */

} lista_cursores;
/*� init-
� isEmpty-
� isFull-
� reset-
� forward-
� isOos-
� copy-
� insert-
� suppress-
*/
///FORWARD
void forward_lista(lista_cursores *l)
{
    l->aux  = l->cur;
    l->cur  = l->cur->puntero_siquiente;
}

///RESET
void reset(lista_cursores *l)
{
    l->cur=l->acc;
    l->aux=l->acc;
}

///COPY
Pedido copy_lista(lista_cursores l)
{
    return l.cur->vipd;
}

///INIT

void init_lista(lista_cursores *l)
{
    l->acc=NULL;
    l->cur=NULL;
    l->aux=NULL;
}

///IS_EMPTY
int isEmpty(lista_cursores l)
{
    if(l.acc==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
///ISFULL
int isFull(lista_cursores l)
{
    Tipo_nodo *nodo_de_prueba;
    nodo_de_prueba=(Tipo_nodo*)malloc(sizeof(Tipo_nodo*));

    if  ( nodo_de_prueba  ==   NULL )
    {
        return 1;
    }
    else
    {
        free((void*)nodo_de_prueba);
        return 0;
    }
}

///ISOOS
int isOos(lista_cursores l)
{
    if(l.cur==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
///INSERT

void insert_nodo_a_la_lista(lista_cursores *l,Pedido d)
{
    Tipo_nodo *nodo_nuevo=(Tipo_nodo*)malloc(sizeof(Tipo_nodo));
    if((l->acc)==(l->cur)) //ya que cur y acc apuntan a null
    {
        l->acc=nodo_nuevo;//apunta a la direccion del nodo nuevo
        nodo_nuevo->puntero_siquiente=l->cur;//el puntero siguiente apunta a Null
        l->cur=l->acc;//el cursor apunta al nodo nuevo que ya apunto el acceso
        l->aux=l->acc;//el puntero auxiliar apunta al nuevo nodo
    }
    else
    {
        l->aux->puntero_siquiente=nodo_nuevo;//el puntero enlazador apunta al nuevo nodo
        nodo_nuevo->puntero_siquiente=l->cur;//aca abarcamos los dos casos si el cursor esta en la primera pocicion o si esta en cualquier otra piensaaa
        l->cur=nodo_nuevo;//cursor apunta al nuevo nodo
    };

    l->cur->vipd=d;
}

///SUPRESS
void supress_nodo(lista_cursores *l)
{
    l->aux->puntero_siquiente   =   l->cur->puntero_siquiente;//enlazamos los cursores para no perder datos
    free((void*)l->cur);
    l->cur  =   l->aux->puntero_siquiente;
}

#endif // TDA_LISTA_H_INCLUDED
