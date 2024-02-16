#ifndef TDA_COMBO_H_INCLUDED
#define TDA_COMBO_H_INCLUDED

#include <string.h>

typedef struct Combo
{
    int id_combo;
    char descripcion[100];
    int stock;
    float precio_unitario;
    int cupon_descuento; // Cambiado a int para cup�n de descuento
} Combo;

void initCombo(Combo* combo)
{
    combo->id_combo = 0;
    strcpy(combo->descripcion, "");
    combo->stock = 0;
    combo->precio_unitario = 0.0;
    combo->cupon_descuento = 0; // Inicializado a 0 por defecto
}

int getIdCombo(Combo combo)
{
    return combo.id_combo;
}

void setIdCombo(Combo *combo, int id)
{
    combo->id_combo = id;
}

char* getDescripcion(Combo* combo)
{
    char *aux = (char*)malloc(strlen(combo->descripcion)+1);
    if(aux==NULL)
    {
    printf("ERROR NO HAY MEMORIA SUFICIENTE EN LA MAQUINA");
        exit(1);
    }
    strcpy(aux,combo->descripcion);
    return aux;
}

void setDescripcion(Combo* combo, char nuevaDescripcion[])
{
    strcpy(combo->descripcion, nuevaDescripcion);
}

int getStock(Combo combo)
{
    return combo.stock;
}

void setStock(Combo* combo, int nuevoStock)
{
    combo->stock = nuevoStock;
}

float getPrecioUnitario(Combo combo)
{
    return combo.precio_unitario;
}

void setPrecioUnitario(Combo* combo, float nuevoPrecio)
{
    combo->precio_unitario = nuevoPrecio;
}

int getCuponDescuento(Combo combo)
{
    return combo.cupon_descuento;
}

void setCuponDescuento(Combo* combo, int nuevoCupon)
{
    combo->cupon_descuento = nuevoCupon;
}


#endif // TDA_COMBO_H_INCLUDED
