#ifndef TDA_PEDIDOS_H_INCLUDED
#define TDA_PEDIDOS_H_INCLUDED

typedef struct Fecha
{
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct Pedido
{
    char id_pedido[17];
    char nombre[100];
    int vendedor;
    int combo_pedido[10];
    int forma_pago;
    float subtotal;
    int consume_en_local;
    float total;
    struct Fecha fechaCompra;
    int entregado;
} Pedido;

void initFecha(struct Fecha* fecha)
{
    fecha->dia = 26;
    fecha->mes = 6;
    fecha->anio = 2011;
}

void initPedido(Pedido* pedido)
{
    int i;
    strcpy(pedido->id_pedido, "");
    strcpy(pedido->nombre, "");
    pedido->vendedor = 0;
    for (i = 0; i < 10; i++)
    {
        (*pedido).combo_pedido[i] = 0;
    }
    pedido->forma_pago = 0;
    pedido->subtotal = 0.0;
    pedido->consume_en_local = 0;
    pedido->total = 0.0;
    struct Fecha fecha = {0, 0, 0};
    pedido->fechaCompra = fecha;
    pedido->entregado = 0;
}

char* getIdPedido(Pedido pedido)
{
    char *aux=(char*)malloc(strlen(pedido.id_pedido)+1);
    if(aux==NULL)
    {
        printf("ERROR NO HAY MEMORIA SUFICIENTE EN LA MAQUINA");
        exit(1);
    }
    strcpy(aux,pedido.id_pedido);
    return aux;
}

void setIdPedido(Pedido* pedido, char id[])
{
    strcpy(pedido->id_pedido, id);
}

char* getNombre(Pedido pedido)
{
    char *aux=(char*)malloc(strlen(pedido.nombre)+1);
    if(aux==NULL)
    {
        printf("ERROR NO HAY MEMORIA SUFICIENTE");
        exit(1);
    }
    strcpy(aux,pedido.nombre);
    return aux;
}

void setNombre(Pedido* pedido, char* nombre)
{
    strcpy(pedido->nombre, nombre);
}

int getVendedor(Pedido pedido)
{
    return pedido.vendedor;
}

void setVendedor(Pedido* pedido, int vendedor)
{
    pedido->vendedor = vendedor;
}

int getComboPedido(Pedido pedido, int index)
{
    return pedido.combo_pedido[index];
}

void setComboPedido(Pedido* pedido, int index, int valor)
{
    pedido->combo_pedido[index] = valor;
}

int getFormaPago(Pedido pedido)
{
    return pedido.forma_pago;
}

void setFormaPago(Pedido* pedido, int forma_pago)
{
    pedido->forma_pago = forma_pago;
}

float getSubtotal(Pedido pedido)
{
    return pedido.subtotal;
}

void setSubtotal(Pedido* pedido, float subtotal)
{
    pedido->subtotal = subtotal;
}

int getConsumeEnLocal(Pedido pedido)
{
    return pedido.consume_en_local;
}

void setConsumeEnLocal(Pedido* pedido, int consume_en_local)
{
    pedido->consume_en_local = consume_en_local;
}

float getTotal(Pedido pedido)
{
    return pedido.total;
}

void setTotal(Pedido* pedido, float total)
{
    pedido->total = total;
}

struct Fecha getFechaCompra(Pedido pedido)
{
    return pedido.fechaCompra;
}

void setFechaCompra(Pedido* pedido, struct Fecha fecha)
{
    pedido->fechaCompra = fecha;
}

int getEntregado(Pedido pedido)
{
    return pedido.entregado;
}

void setEntregado(Pedido* pedido, int entregado)
{
    pedido->entregado = entregado;
}




void set_Fecha_anio(Fecha *fecha, int anio)
{

    (*fecha).anio = anio;
}

void set_Fecha_dia(Fecha *fecha, int dia)
{
    (*fecha).dia = dia;
}

void set_Fecha_mes(Fecha *fecha, int mes)
{
    (*fecha).mes = mes;
}




Fecha get_fecha(Pedido pedido)
{
    return pedido.fechaCompra;
}

int get_fecha_mes(Pedido pedido)
{
    return pedido.fechaCompra.mes;
}

#endif // TDA_PEDIDOS_H_INCLUDED
