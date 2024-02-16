#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include "tda_combo.h"
#include "tda_pedidos.h"
#include "tda_lista.h"
#define MAX_SIZE 100
///-----------------------------------------PROTOTIPOS.-------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------CARGADORES----------------------------------------

int cargar_pedido(Pedido pedido1, Combo combo[], int vendedor_actual, lista_cursores *lista_pedidos, int dia_actual, int mes_actual, int anio_actual);

void precarga_automatica_de_combos(Combo combo_carga[]);

void precarga_pedidos (lista_cursores *l);


//-------------------------------------------------------------------------------------------



//-----------------------------------------MOSTRADORES----------------------------------------

void vendedor_del_mes(lista_cursores l);

void mostrar_combos(Combo combos[]);

void mostrar_datos_id(lista_cursores l);

void mostrar_pedidos_por_mes(lista_cursores l);

void mostrar_pedidos_nombre(lista_cursores l);

void mostrar_los_combos_sin_stock(Combo combos[]);

void mostrar_precio_y_stock_por_id_combo(Combo combos[]);

void mostrar_todos_los_pedidos_no_entregados(lista_cursores l);

void mostrar_pedidos(lista_cursores l);

void mostrar_logo();

//---------------------------------------------------------------------------------------------




//-----------------------------------------MODIFICADORES----------------------------------------

void modificar_la_forma_de_pago_de_un_pedido_segun_su_idpedido(lista_cursores *l);

void modificar_nombre_de_un_pedido_segun_su_idpedido(lista_cursores *l);

void modificar_el_estado_del_pedido_a_entregado_por_idpedido(lista_cursores *l);

void modificar_precio_y_stock_del_combo_segun_idcombo(Combo *combo);

void cambio_vendedor_activo(int *vendedor_actual);

void anular_pedido_por_idpedido(lista_cursores *l);


//----------------------------------------------------------------------------------------------

//-----------------------------------------ALMACENADORES----------------------------------------

void almacenar_datos_por_forma_de_pago(lista_cursores l);

//----------------------------------------------------------------------------------------------


//-----------------------------------------HERRAMIENTAS PARA FUCIONES----------------------------------------

char *generatePibeString(const char *archivoDeGuardado);

int buscar_id_pedido(lista_cursores *l);

int maximo(int a, int b, int c, int d);

void obtenerFechaActual(int *dia, int *mes, int *anio);

int obtenerNumeroEntero() ;
//------------------------------------------------------------------------------------------------------------

//-----------------------------------------RECURSIVAS----------------------------------------
///reset en el main antes de invocar
int contar_los_pedidos_realizados_por_un_vendedor(lista_cursores l,int vendedor_x,int contador,Pedido auxC); ///reset en el main antes de invocar
///reset en el main antes de invocar
void mostrar_los_pedidos_realizados_por_un_vendedor(lista_cursores l,int vendedor_x,Pedido aux);///reset en el main antes de invocar
///reset en el main antes de invocar

//------------------------------------------------------------------------------------------

///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


///----------------------------------------- MAIN.-----------------------------------------

int main()
{
    int dia = 0;
    int mes = 0;
    int anio = 0;
    int vendedor_actual;
    Combo combo_pedidos[10];
    int opcion;
    int opcion_pedidos;
    int opcion_combos;
    int opcion_vendedor;
    int opcion_a;
    int vendedor_buscar;
    int contador_vendedor;//Para recursiva.
    int contador_vendedor_b;//Para recursiva.

    //Variables de tipo lista e inicializar
    lista_cursores lista_pedidos;
    init_lista(&lista_pedidos);
    precarga_pedidos(&lista_pedidos);
    precarga_automatica_de_combos(combo_pedidos);
    Pedido pedido1;// Es un auxiliar para la carga
    Pedido aux;// Auxiliar para recursivas.
    //Inicializacion de variables
    initPedido(&pedido1);
    initPedido(&aux);
    vendedor_actual=1; //Por defecto es CJ.
    fflush(stdin);
    obtenerFechaActual(&dia, &mes, &anio);

    do
    {
        system("cls");
        printf("\n......::::MENU ""Groove Street Burguers""::::......\n");
        printf("\n 1. Cargar un pedido");
        printf("\n 2. Menu de Pedidos.");
        printf("\n 3. Menu de Combos.");
        printf("\n 4. Menu de Vendedores.");
        printf("\n 0. Salir.");
        printf("\n Ingrese la opcion deseada: ");
        opcion=obtenerNumeroEntero();

        switch (opcion)
        {
        case 1:
            if(!isFull(lista_pedidos))
            {
                opcion_a = cargar_pedido(pedido1,combo_pedidos,vendedor_actual,&lista_pedidos, dia, mes, anio);
                if (opcion_a == 1)
                {
                    printf ("\n Carga exitosa.");
                }
                else
                {
                    printf("\n Carga Cancelada");
                }
            }
            else
            {
                printf("\n ERROR NO HAY MAS ESPACIO EN LA LISTA");
                exit(0);
            }
            //mostrar_pedidos(lista_pedidos);
            system("PAUSE");
            system("cls");
            break;

        case 2:
            if (isEmpty(lista_pedidos) == 1)
            {
                printf("No hay pedidos Cargados, volvera al Menu.");
                system("PAUSE");
                break;
            }

            system("cls");
            printf("--------------------MENU Pedidos--------------------"); ///El busca no esta por que es una funcion herramienta.

            printf("\n 1.Mostrar datos de un pedido por ID.");

            printf("\n 2.Mostrar todos los pedidos de un mes.");

            printf("\n 3.Mostrar pedidos por nombre (paginados).");

            printf("\n 4.Mostrar pedidos realizados por un vendedor.");

            printf("\n 5.Contar pedidos realizados por un vendedor");

            printf("\n 6.Mostrar todos los pedidos no entregados.");

            printf("\n 7.Modificar estado de un pedido a entregado.");

            printf("\n 8.Modificar forma de pago de un pedido.");

            printf("\n 9.Modificar nombre de un pedido.");

            printf("\n 10.Almacenar datos de Pedidos por forma de Pago.");

            printf("\n 11.Anular un pedido.");

            printf("\n 0. Volver al Menu Principal.");

            printf("\n----------------------------------------------------");

            printf("\n");

            printf("\n Ingrese la opcion deseada: ");
            opcion_pedidos = obtenerNumeroEntero();

            switch (opcion_pedidos)
            {
            case 1:
                mostrar_datos_id(lista_pedidos);
                system("PAUSE");
                break;
            case 2:
                mostrar_pedidos_por_mes(lista_pedidos);
                system("PAUSE");
                break;
            case 3:
                mostrar_pedidos_nombre(lista_pedidos);
                system("PAUSE");
                break;
            case 4:
                vendedor_buscar = 0;
                initPedido(&aux);
                reset(&lista_pedidos);
                printf("\n Ingrese el vendedor:");
                printf("\n 1. CJ.");
                printf("\n 2. Big Smoke.");
                printf("\n 3. Sweet.");
                printf("\n 4. Ryder.");
                printf("\n ->  ");
                scanf("%d",&vendedor_buscar);
                while(vendedor_buscar < 1 || vendedor_buscar > 4)
                {
                    printf("Numero incorrecto.");
                    scanf("%d",&vendedor_buscar);
                }
                mostrar_los_pedidos_realizados_por_un_vendedor(lista_pedidos,vendedor_buscar, aux);
                system("PAUSE");
                break;
            case 5:
                vendedor_buscar = 0;
                contador_vendedor = 0;
                contador_vendedor_b = 0; ///A fin de evitar errores.
                initPedido(&aux);
                printf("\n Ingrese el vendedor:");
                printf("\n 1. CJ.");
                printf("\n 2. Big Smoke.");
                printf("\n 3. Sweet.");
                printf("\n 4. Ryder.");
                printf("\n ->  ");
                scanf("%d",&vendedor_buscar);
                while(vendedor_buscar < 1 || vendedor_buscar > 4)
                {
                    printf("\n Numero incorrecto.");
                    scanf("%d",&vendedor_buscar);
                }
                contador_vendedor = contar_los_pedidos_realizados_por_un_vendedor(lista_pedidos,vendedor_buscar,contador_vendedor_b,aux);
                printf("\n Los pedidos realizados por el vendedor, ");
                if (vendedor_buscar == 1)
                {
                    printf("CJ");
                }
                if (vendedor_buscar == 2)
                {
                    printf("Big Smoke ");
                }
                if (vendedor_buscar == 3)
                {
                    printf("Sweet");
                }
                if (vendedor_buscar == 4)
                {
                    printf("Ryder");
                }
                printf(" son: %d \n", contador_vendedor);
                system("PAUSE");
                break;
            case 6:
                mostrar_todos_los_pedidos_no_entregados(lista_pedidos);
                system("PAUSE");
                break;
            case 7:
                modificar_el_estado_del_pedido_a_entregado_por_idpedido(&lista_pedidos);
                printf("\n Opcion completada.");
                system ("PAUSE");
                printf("Sera devuelto al menu principal.");
                system("PAUSE");
                break;
            case 8:
                modificar_la_forma_de_pago_de_un_pedido_segun_su_idpedido(&lista_pedidos);
                system ("PAUSE");
                printf("Sera devuelto al menu principal.");
                system("PAUSE");
                break;
            case 9:
                modificar_nombre_de_un_pedido_segun_su_idpedido(&lista_pedidos);
                system("PAUSE");
                printf("Sera devuelto al menu principal.");
                system("PAUSE");
                break;
            case 10:
                almacenar_datos_por_forma_de_pago(lista_pedidos);
                break;
            case 11:
                anular_pedido_por_idpedido(&lista_pedidos);
                system ("PAUSE");
                printf("Sera devuelto al menu principal.");
                break;
            case 0:
                system("PAUSE");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
            }
            break;

        case 3:
            system("cls");

            printf("--------------------MENU Combos--------------------");

            printf("\n 1.Modificar precio y stock de combo.");

            printf("\n 2.Mostrar todos los combos.");

            printf("\n 3.Mostrar precio y stock de combo por ID.");

            printf("\n 4.Mostrar combos sin stock.");

            printf("\n 0. Volver al Menu Principal.");

            printf("\n-------------------------------------------------");

            printf("\n Ingrese la opcion deseada: ");
            opcion_combos = obtenerNumeroEntero();

            switch(opcion_combos)
            {
            case 1:
                modificar_precio_y_stock_del_combo_segun_idcombo(combo_pedidos);
                printf("\n");
                system("PAUSE");
                break;
            case 2:
                mostrar_combos(combo_pedidos);
                printf("\n");
                system("PAUSE");
                break;
            case 3:
                mostrar_precio_y_stock_por_id_combo(combo_pedidos);
                printf("\n");
                system("PAUSE");
                break;
            case 4:
                mostrar_los_combos_sin_stock(combo_pedidos);
                printf("\n");
                system("PAUSE");
                break;
            case 0:
                printf("\n");
                system("PAUSE");
                break;
            default:
                printf("\n Opción no válida. Intente de nuevo.");
            }
            break;

        case 4:
            printf("\n --------------------MENU VENDEDOR--------------------");

            printf("\n 1.Informar vendedor con mas pedidos en el mes");

            printf("\n 2.Cambiar vendedor activo.");

            printf("\n 3.Contar pedidos realizados por un vendedor");

            printf("\n 0.Volver al Menu Principal.");

            printf("\n------------------------------------------------------");

            printf("\n Ingrese la opcion deseada: ");
            opcion_vendedor=obtenerNumeroEntero();

            switch(opcion_vendedor)
            {
            case 1:
                vendedor_del_mes(lista_pedidos);
                printf("\n");
                system("PAUSE");
                break;
            case 2:
                cambio_vendedor_activo(&vendedor_actual);
                printf("\n");
                system("PAUSE");
                break;
            case 3:
                vendedor_buscar = 0;
                contador_vendedor = 0;
                contador_vendedor_b = 0; ///A fin de evitar errores.
                initPedido(&aux);
                printf("\n Ingrese el vendedor:");
                printf("\n 1. CJ.");
                printf("\n 2. Big Smoke.");
                printf("\n 3. Sweet.");
                printf("\n 4. Ryder.");
                printf("\n ->");
                scanf("%d",&vendedor_buscar);
                while(vendedor_buscar < 1 || vendedor_buscar > 4)
                {
                    printf("\n Numero incorrecto.");
                    scanf("%d",&vendedor_buscar);
                }
                contador_vendedor = contar_los_pedidos_realizados_por_un_vendedor(lista_pedidos,vendedor_buscar,contador_vendedor_b,aux);
                printf("\n Los pedidos realizados por el vendedor, ");
                if (vendedor_buscar == 1)
                {
                    printf("CJ");
                }
                if (vendedor_buscar == 2)
                {
                    printf("Big Smoke");
                }
                if (vendedor_buscar == 3)
                {
                    printf("Sweet");
                }
                if (vendedor_buscar == 4)
                {
                    printf("Ryder");
                }
                printf(" son: %d \n", contador_vendedor);
                printf("\n");
                system("PAUSE");
                break;
            case 0:
                printf("\n");
                system("PAUSE");
                break;
            default:
                printf("\n Opción no válida. Intente de nuevo.\n");
            }

        case 0:
            system("PAUSE");
            //mostrar_logo();
            printf("\n Ejecucion Finalizada.");
        }


    }

    while(opcion != 0);
    return 0;
}

///----------------------------------------- FIN-MAIN.-----------------------------------------





///-----------------------------------------FUNCIONES.-----------------------------------------






//-----------------------------------------CARGADORES----------------------------------------

int cargar_pedido(Pedido pedido1, Combo combo[], int vendedor_actual, lista_cursores *lista_pedidos, int dia_actual, int mes_actual, int anio_actual)
{
    Fecha fecha_pedido;
    typedef struct
    {
        int id_combo;
        char descripcion[100];
        int stock;
        float precio_unitario;
        int cupon_descuento;
    } Combo1;
    int dia = dia_actual;
    int mes = mes_actual;
    int anio = anio_actual;
    int numero_combo;
    int salida = 0;
    int confirmacion = 0;
    int confirmacion_adicional;
    float subtotal = 0;
    float total = 0;
    int validacion_consume;
    int cupon;
    int medio_de_pago;
    char nombre_cliente[100];
    int entregado_compra;
    int i;
    Combo1 combo_aux[10];
    for(i = 0; i < 10; i++)
    {
        combo_aux[i].id_combo = 0;
        strcpy(combo_aux[i].descripcion, "");
        combo_aux[i].stock = 0;
        combo_aux[i].precio_unitario = 0.0;
        combo_aux[i].cupon_descuento = 0; // Inicializado a 0 por defecto
    }




    //for (i = 0; i < 10; i++)
    //{
    //    initCombo(&combo_aux[i]);
    //}

    do
    {
        do
        {
            mostrar_combos(combo);

            printf("\n Selecciona un combo (0-9): " );
            numero_combo=obtenerNumeroEntero();
            while (numero_combo < 0 || numero_combo > 9)
            {

                printf("\n Valor incorrecto. ");
                printf("\n Selecciona un combo (0-9): ");
                scanf("%d", &numero_combo);
            }

            printf("\n Ingresa la cantidad del combo seleccionado: ");
            scanf("%d", &combo_aux[numero_combo].stock);

            while (combo_aux[numero_combo].stock < 0)
            {
                printf("\n Valor incorrecto. La cantidad no puede ser negativa. ");
                printf("\n Ingresa nuevamente la cantidad del combo seleccionado: ");
                scanf("%d", &combo_aux[numero_combo].stock);
            }

            if(getStock(combo[numero_combo]) != 0)
            {
                while (combo_aux[numero_combo].stock > getStock(combo[numero_combo]) || combo_aux[numero_combo].stock < 0)
                {
                    printf("\n Cantidad es incorrecta.");
                    printf("\n La cantidad no puede ser mayor al stock disponible: CANT.:%d. ", getStock(combo[numero_combo]) );
                    printf("\n Ingresa la cantidad del combo seleccionado nuevamente: ");
                    scanf("%d", &combo_aux[numero_combo].stock);
                }



                printf("\n Desea agregar algo mas, modificar el pedido existente o cancelarlo?");
                printf("\n 1. Agregar.");
                printf("\n 2. Continuar.");
                printf("\n 0. Cancelar Pedido.");
                printf("\n -> ");
                scanf("%d", &confirmacion);
                while (confirmacion != 1 && confirmacion != 0 && confirmacion != 2)
                {
                    printf("\n Seleccion incorrecta, por favor, intente nuevamente.");
                    printf("\n 1. Agregar.");
                    printf("\n 2. Continuar.");
                    printf("\n 0. Cancelar Pedido.");
                    printf("\n -> ");
                    scanf("%d", &confirmacion);
                }
                if (confirmacion == 0)
                {
                    initPedido(&pedido1);
                    printf("\n Sera devuelto al menu principal.");
                    printf("\n");
                    system("PAUSE");
                    return 0;
                }
            }
            else
            {

                printf("\n El combo no se encuentra en stock (En la muestra de combos ya aparecia el stock disponible).");
                printf("\n 1. Pedir otro combo?");
                printf("\n 0. Cancelar Pedido.");
                printf("\n -> ");
                scanf("%d", &confirmacion);
                while (confirmacion != 1 && confirmacion != 0)
                {
                    printf("\n Seleccion incorrecta, por favor, intente nuevamente.");
                    printf("\n 1. Pedir otro combo?");
                    printf("\n 0. Cancelar Pedido.");
                    printf("\n -> ");
                    scanf("%d", &confirmacion);
                }
                if (confirmacion == 0)
                {
                    initPedido(&pedido1);
                    printf("\n Sera devuelto al menu principal.");
                    printf("\n");
                    system("PAUSE");
                    return 0;
                }

            }
            if(confirmacion==1)
            {
                printf("\n ADVERTENCIA si pide una misma variedad de combo, \n sera remplazada por la ultima  cantidad ingresada de tal combo.  ");
                system("PAUSE");
            }

        }

        while (confirmacion == 1);
        //
        //
        // Cálculo de Subtotal.
        for (i = 0; i < 10; i++)
        {
            fflush(stdin);
            subtotal = subtotal + getPrecioUnitario(combo[i]) * combo_aux[i].stock; // Subtotal = Precio * Cantidad.
        }
        //
        printf("\n Se realizara un Delivery o se Consumira en el local?");
        printf("\n 1. Consume en Local.");
        printf("\n 0. Delivery.");
        printf("\n -> ");
        scanf("%d", &validacion_consume);
        while (validacion_consume != 1 && validacion_consume != 0)
        {
            printf("\n Seleccion incorrecta, por favor, intente nuevamente.");
            printf("\n Se realizara un Delivery o se Consumira en el local?");
            printf("\n 1. Consume en Local.");
            printf("\n 0. Delivery.");
            printf("\n -> ");
            scanf("%d", &validacion_consume);
        }
        if (validacion_consume == 0)
        {
            total = 500; // Se asigna 500 por el delivery.

        }

        do
        {
            printf("\n El cliente tiene cupon?");
            printf("\n 1. Si / 0. No");
            printf("\n -> ");
            scanf("%d", &cupon);

            if (cupon == 1)
            {
                break; // Sal del bucle
            }
            else if (cupon == 0)
            {
                break; // Sal del bucle
            }
            else
            {
                printf("\n Seleccion incorrecta, por favor, intente nuevamente.");
            }
        }
        while (1);   // Bucle hasta que se ingrese 1 o 0

        // Cálculo de Total
        for (i = 0; i < 10; i++)
        {
            if (cupon == 1 && getCuponDescuento(combo[i]) == 1)
            {
                total = total + (getPrecioUnitario(combo[i]) - getPrecioUnitario(combo[i]) * 0.15) * combo_aux[i].stock; // Con descuento
            }
            else
            {
                total = total + getPrecioUnitario(combo[i]) * combo_aux[i].stock; // Sin descuento
            }
        }

        printf("\n El cliente confirma la compra?");
        printf("\n 1. Si / 0. No");
        printf("\n -> ");
        scanf("%d", &confirmacion_adicional);
        while (confirmacion_adicional != 1 && confirmacion_adicional != 0)
        {
            printf("\n Seleccion incorrecta, por favor, intente nuevamente.");
            printf("\n 1. SI -------- 0. NO.");
            printf("\n -> ");
            scanf("%d", &confirmacion_adicional);
        }
        if (confirmacion_adicional == 0)
        {
            printf("\n Compra cancelada.");
            printf("\n Sera redirigido al Menu.\n");
            system("PAUSE");
            salida = 1;
            return 0;
        }

        if (confirmacion_adicional == 1)
        {
            printf("\n Solicite el medio de pago.");
            printf("\n 1. Debito.");
            printf("\n 2. Credito.");
            printf("\n 3. QR.");
            printf("\n 4. Efectivo.");
            printf("\n -> ");
            scanf("%d", &medio_de_pago);

            while (medio_de_pago != 1 && medio_de_pago != 2 && medio_de_pago != 3 && medio_de_pago != 4)
            {
                printf("\n Seleccion incorrecta, por favor, intente nuevamente.");
                printf("\n Solicite el medio de pago.");
                printf("\n 1. Debit.");
                printf("\n 2. Credito.");
                printf("\n 3. QR.");
                printf("\n 4. Efectivo.");
                printf("\n -> ");
                scanf("%d", &medio_de_pago);
            }
        }
        printf("\n Solicite el nombre del cliente: ");
        printf("\n -> ");
        fflush(stdin);
        gets(nombre_cliente);///////////////////////////////////////HICE CAMBIO DE SCANF A GETS POR EL TEMA DE LOS ESPACIOS/////////////

        // Print de ticket (consulta)--------------------------------
        setIdPedido(&pedido1,generatePibeString("numero_de_id.txt"));
        printf("\n------------------------------------------------");
        printf("\n ID del Pedido: %s",getIdPedido(pedido1));
        printf("\n Fecha de Compra: %d/%d/%d", dia, mes, anio);
        //
        if (vendedor_actual == 1)
        {
            printf("\n Vendedor: CJ");
        }
        if (vendedor_actual == 2)
        {
            printf("\n Vendedor: Big Smoke");
        }
        if (vendedor_actual == 3)
        {
            printf("\n Vendedor: Sweet");
        }
        if (vendedor_actual == 4)
        {
            printf("\n Vendedor: Ryder");
        }
        //
        printf("\n Subtotal: %.2f\n", subtotal);
        //
        if (validacion_consume == 1)
        {
            printf("\n Consumo en Local: SI");
        }
        if (validacion_consume == 0)
        {
            printf("\n Consumo en Local: NO");
        }
        //
        printf("\n Total: %.2f\n", total);
        //
        if (medio_de_pago == 1)
        {
            printf("\n Opcion de pago: Debito.");
        }
        if (medio_de_pago == 2)
        {
            printf("\n Opcion de pago: Credito.\n");
        }
        if (medio_de_pago == 3)
        {
            printf("\n Opcion de pago: QR.\n");
        }
        if (medio_de_pago == 4)
        {
            printf("\n Opcion de pago: Efectivo.\n");
        }
        printf("\n Nombre: %s\n", nombre_cliente);
        printf("\n ------------------------------------------------");

        salida = 1;
    }

    while (salida != 1);
    setNombre(&pedido1, nombre_cliente);
    setVendedor(&pedido1, vendedor_actual);
    for (i = 0; i < 10; i++)
    {
        fflush(stdin);
        setComboPedido(&pedido1,i,combo_aux[i].stock);
        fflush(stdin);
        setStock(&combo[i],(getStock(combo[i]) - combo_aux[i].stock));
    }
    setFormaPago(&pedido1, medio_de_pago);
    setSubtotal(&pedido1, subtotal);
    setConsumeEnLocal(&pedido1, validacion_consume);
    setTotal(&pedido1, total);
    //set_Fecha(&pedido1, dia, mes, anio);
    set_Fecha_dia(&fecha_pedido,dia);
    set_Fecha_mes(&fecha_pedido,mes);
    set_Fecha_anio(&fecha_pedido,anio);
    //fecha_pedido.dia = dia;
    //fecha_pedido.mes = mes;
    //fecha_pedido.anio = anio;
    setFechaCompra(&pedido1, fecha_pedido);


    if( validacion_consume == 0 &&  confirmacion_adicional == 1) ///Si se consume en el local y se confirma la compra, figura entregado. (Entregado = 1, "booleano verdadero").
    {
        entregado_compra = 1;
        setEntregado(&pedido1, entregado_compra);
    }

    insert_nodo_a_la_lista(lista_pedidos, pedido1);
    return 1;
}


void precarga_automatica_de_combos(Combo combo_carga[])
{
    FILE *fp3;
    int i;
    char speckless[4];

    int id_combo;
    char descripcion[100];
    int stock;
    float precio_unitario;
    int cupon_descuento;

    fp3 = fopen("menu.txt", "r");
    if (fp3 == NULL)
    {
        printf("\n ERROR FATAL!!!");
        printf("\n No se pudo realizar la precarga automatica de combos.");
        printf("\n");
        system("PAUSE");
        exit(1);
    }

    for (i = 0; i < 10; i++)
    {
        initCombo(&combo_carga[i]);
        fscanf (fp3,"%d\n", &id_combo);
        setIdCombo (&combo_carga[i], id_combo);
        fflush(stdin);
        fgets (descripcion, sizeof(descripcion), fp3);
        setDescripcion (&combo_carga[i],descripcion);
        fflush(stdin);
        fscanf (fp3,"%d\n", &stock);
        setStock (&combo_carga[i], stock);
        fflush(stdin);
        fscanf (fp3,"%f\n", &precio_unitario);
        setPrecioUnitario(&combo_carga[i], precio_unitario);
        fflush(stdin);
        fscanf (fp3,"%d\n", &cupon_descuento);
        setCuponDescuento(&combo_carga[i], cupon_descuento);
        fflush(stdin);
        fgets (speckless, sizeof(speckless), fp3);
    }

    fclose(fp3);
}

void precarga_pedidos(lista_cursores *l)
{
    int i, j;
    char speckless[20];
    char nombre_aux[100];
    char id_aux[17];
    int vendedor_aux = 0;
    int combo_pedido_aux[10];
    int forma_pago_aux = 0;
    float subtotal_aux = 0;
    int consume_en_local_aux = 0;
    float total_aux = 0;
    int entregado_aux = 0;
    int dia_aux = 0;
    int mes_aux = 0;
    int anio_aux = 0;

    int aux_para_carga_de_combos=0;



    Fecha fecha_aux;
    initFecha(&fecha_aux);
    FILE *file_pedidos;
    file_pedidos = fopen("carga_pedido.txt", "r");
    if (file_pedidos == NULL)
    {
        printf("\n ERROR FATAL!!!");
        printf("\n No se pudo realizar la precarga automatica de pedidos.");
        printf("\n");
        system("PAUSE");
        exit(1);
    }

    Pedido pedido_aux;
    initPedido(&pedido_aux);
    reset(l);

    for (i = 0; i <= 9; i++)
    {

        // Corregir el formato de lectura de nombre y ID

        fgets(nombre_aux, sizeof(nombre_aux), file_pedidos);
        nombre_aux[strcspn(nombre_aux, "\n")] = '\0';
        setNombre(&pedido_aux, nombre_aux);
        //printf("\n Nombre es: %s", nombre_aux);
        fflush(stdin);
        fgets (id_aux, sizeof(id_aux), file_pedidos);
        id_aux[strcspn(id_aux, "\n")] = '\0';
        setIdPedido(&pedido_aux,id_aux);
        //printf("\n ID es: %s", id_aux);
        fflush(stdin);
        fscanf(file_pedidos, "%d\n", &vendedor_aux);
        setVendedor(&pedido_aux, vendedor_aux);
        //printf("\n Vendedor es: %d", vendedor_aux);
        for (j = 0; j <= 9   ; j++)
        {
            fflush(stdin);
            fscanf(file_pedidos, "%d", &combo_pedido_aux[j]);

            aux_para_carga_de_combos=combo_pedido_aux[j];
            setComboPedido(&pedido_aux, j, aux_para_carga_de_combos);
        }

        fflush(stdin);
        fscanf(file_pedidos, "%d\n", &forma_pago_aux);
        setFormaPago(&pedido_aux,forma_pago_aux);
        //printf("\n Forma de Pago es: %d", forma_pago_aux);
        fflush(stdin);
        fscanf(file_pedidos, "%f\n", &subtotal_aux);
        setSubtotal(&pedido_aux,subtotal_aux);
        //printf("\n Subtotal es: %f", subtotal_aux);
        fflush(stdin);
        fscanf(file_pedidos, "%d\n", &consume_en_local_aux);
        setConsumeEnLocal(&pedido_aux, consume_en_local_aux);
        //printf("\n Consume en local es: %d", consume_en_local_aux);
        fflush(stdin);
        fscanf(file_pedidos, "%f\n", &total_aux);
        //printf("\n Total es: %f", total_aux);
        setTotal(&pedido_aux,total_aux);


        fflush(stdin);
        fscanf(file_pedidos, "%d\n",&dia_aux);

        fflush(stdin);
        fscanf(file_pedidos, "%d\n",&mes_aux);

        fflush(stdin);
        fscanf(file_pedidos, "%d\n",&anio_aux);
        ///set_Fecha(&pedido_aux, dia_aux, mes_aux, anio_aux);
        fecha_aux.dia = dia_aux;
        fecha_aux.mes = mes_aux;
        fecha_aux.anio = anio_aux;
        setFechaCompra(&pedido_aux,fecha_aux);

        fflush(stdin);
        fscanf(file_pedidos, "%d\n", &entregado_aux);
        setEntregado(&pedido_aux, entregado_aux);

        fflush(stdin);
        fgets(speckless, sizeof(speckless), file_pedidos);

        insert_nodo_a_la_lista(l, pedido_aux);
        forward_lista(l);
    }
    fclose(file_pedidos);  // Cerrar el archivo después de la lectura
}



//-----------------------------------------CARGADORES----------------------------------------






//-----------------------------------------MOSTRADORES----------------------------------------

void vendedor_del_mes(lista_cursores l)

{
    int x; //variable auxiliar.
    int mes;
    int contador_empleado_1 =0;
    int contador_empleado_2 =0;
    int contador_empleado_3 =0;
    int contador_empleado_4 =0;
    printf("\n Ingrese el numero de Mes: (1-12)");
    printf("\n -> ");
    scanf("%d", &mes);
    while(mes < 1 || mes > 12 )
    {
        printf("\n Mes incorrecto, intente nuevamente.");
        printf("\n Ingrese el numero de Mes: (1-12)");
        printf("\n -> ");
        scanf("%d", &mes);
    }
    Pedido aux;
    reset(&l);
    while (isOos(l)==1)
    {
        aux = copy_lista(l);
        if (mes == get_fecha_mes(aux))
        {
            if(getVendedor(aux)== 1)
            {
                contador_empleado_1++;
            }
            if(getVendedor(aux)== 2)
            {
                contador_empleado_2++;
            }
            if(getVendedor(aux) == 3)
            {
                contador_empleado_3++;
            }
            if(getVendedor(aux) == 4)
            {
                contador_empleado_4++;
            }

        }
        forward_lista(&l);
    }
    x = maximo(contador_empleado_1,contador_empleado_2,contador_empleado_3,contador_empleado_4);
    if(x == contador_empleado_1)
    {
        printf("\n El vendedor con mas ventas es el vendedor CJ!");
        x= 26062011;

    }
    if(x == contador_empleado_2)
    {
        printf("\n El vendedor con mas ventas es el vendedor Big Smoke!");
        x= 26062011;

    }
    if(x == contador_empleado_3)
    {
        printf("\n El vendedor con mas ventas es el vendedor Sweet!");
        x= 26062011;

    }
    if(x == contador_empleado_4)
    {
        printf("\n El vendedor con mas ventas es el vendedor Ryder!");
        x= 26062011;
    }
}

void mostrar_combos(Combo combos[])
{
    int i;
    for (i = 0; i <= 9; i++)
    {
        printf("\n");
        printf("\n --------------------------COMBO %d --------------------------", i);
        printf("\n ID Combo: %d", getIdCombo(combos[i]));
        printf("\n Descripcion: %s", getDescripcion(&combos[i]));
        printf("\n Stock: %d\n", getStock(combos[i]));
        printf("\n Precio Unitario: $%.2f", getPrecioUnitario(combos[i]));
        if (getCuponDescuento(combos[i]) == 0)
        {
            printf("\n Descuento disponible: NO");
        }
        else
        {
            printf("\n Descuento disponible: SI");
        }
        printf("\n -------------------------------------------------------------");
        printf("\n");

    }

}

void mostrar_datos_id(lista_cursores l)
{
    int x;
    int entregado;
    Pedido aux;
    x = buscar_id_pedido(&l);
    if (x == 1)
    {
        aux = copy_lista(l);
        // Mostrar los detalles del pedido
        printf("\n ID del Pedido: %s", getIdPedido(aux));
        printf("\n Nombre: %s", getNombre(aux));
        //-----------------------------------------------
        switch (getVendedor(aux))
        {
        case 1:
            printf("\n Vendedor: CJ.");
            break;
        case 2:
            printf("\n Vendedor: Big Smoke.");
            break;
        case 3:
            printf("\n Vendedor: Sweet.");
            break;
        case 4:
            printf("\n Vendedor: Ryder.");
            break;
        }
        //-----------------------------------------------
        switch (getFormaPago(aux))
        {
        case 1:
            printf("\n Forma de Pago: Debito.");
            break;
        case 2:
            printf("\n Forma de Pago: Credito.");
            break;
        case 3:
            printf("\n Forma de Pago: QR.");
            break;
        case 4:
            printf("\n Forma de Pago: Efectivo.");
            break;
        }
        printf("\n Subtotal: %.2f", getSubtotal(aux));
        //-----------------------------------------------
        if (getConsumeEnLocal(aux) == 1)
        {
            printf("\n Consumo en Local: SI.");
        }
        else
        {
            printf("\n Consume en el Local: NO.");
        }
        //-----------------------------------------------
        printf("\n Total: %.2f", getTotal(aux));
        // Fecha de Compra
        struct Fecha fecha = getFechaCompra(aux);
        printf("\n Fecha de Compra: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);
        // Entregado
        entregado = getEntregado(aux);
        //-----------------------------------------------
        if (entregado == 1)
        {
            printf ("\n Entregado: SI.");
            printf ("\n");
        }
        else
        {
            printf ("\n Entregado: NO.");
            printf ("\n");
        }
        //-----------------------------------------------
    }
    return;
}


void mostrar_pedidos_por_mes(lista_cursores l)
{
    int mes_aux;
    int x;
    int control;
    Pedido aux;
    int entregado;

    control = 0;
    x = 0;

    do
    {
        printf("\n Ingrese el mes (1-12):");
        printf("\n -> ");
        scanf("%d", &x);
        if (x >= 1 && x <= 12)
        {
            control = 151906;
        }
        else
        {
            printf("\n Mes no válido. Intente nuevamente.");
        }
    }
    while (control != 151906);

    reset(&l);

    while (isOos(l) == 1)
    {
        aux = copy_lista(l);
        mes_aux = get_fecha_mes(aux);
        //prueba.
        //printf ("\n X es -------------> %d", x);
        //printf ("\n Mes aux es: ------> %d", mes_aux);
        if (x == mes_aux)
        {
            printf("----------------------------------------\n");
            // Mostrar los detalles del pedido
            printf("ID del Pedido: %s\n", getIdPedido(aux));
            printf("Nombre: %s\n", getNombre(aux));

            // Vendedor----------------------------------------
            switch (getVendedor(aux))
            {
            case 1:
                printf("Vendedor: CJ\n");
                break;
            case 2:
                printf("Vendedor: Big Smoke\n");
                break;
            case 3:
                printf("Vendedor: Sweet\n");
                break;
            case 4:
                printf("Vendedor: Ryder\n");
                break;
            }
            // Forma de pago-----------------------------------
            switch (getFormaPago(aux))
            {
            case 1:
                printf("Opcion de pago: Debito\n");
                break;
            case 2:
                printf("Opcion de pago: Credito\n");
                break;
            case 3:
                printf("Opcion de pago: QR\n");
                break;
            case 4:
                printf("Opcion de pago: Efectivo\n");
                break;
            }

            printf("Subtotal: $%.2f\n", getSubtotal(aux));
            // Consumo en Local--------------------------------
            if (getConsumeEnLocal(aux) == 1)
            {
                printf("Consumo en Local: SI\n");
            }
            else
            {
                printf("Consumo en Local: NO\n");
            }

            printf("Total: $%.2f\n", getTotal(aux));
            // Fecha de Compra-----------------------------------------------------
            struct Fecha fecha = getFechaCompra(aux);
            printf("Fecha de Compra: %d/%d/%d\n", fecha.dia, fecha.mes, fecha.anio);
            // Entregado-----------------------------------------------------------
            entregado = getEntregado(aux);
            printf("Entregado: %s\n", (entregado == 1) ? "Si" : "No");
            printf("----------------------------------------\n");
            printf("\n");
            system("PAUSE");
        }
        forward_lista(&l);
    }
}



void mostrar_pedidos_nombre(lista_cursores l)
{
    char nombre_aux[100];
    char nombrex[100];
    Pedido aux;
    int entregado;
    int paginador = 1;
    printf("\n Ingrese el nombre del cliente:");
    printf("\n -> ");
    fflush(stdin);
    gets(nombrex);
    reset(&l);
    while (isOos(l) == 1)
    {
        aux = copy_lista(l);
        strcpy(nombre_aux, getNombre(aux));
        if (strcmp(nombrex, nombre_aux) == 0)
        {
            if (paginador %2 == 0)
            {

                printf("\n");
                printf("\n");
                printf("-----------------PAGINA %d-----------------\n", paginador);
                printf("\n");
                printf("\n");

                system("PAUSE");
            }
            printf("-----------------TICKET Nº %d-----------------\n", paginador);

            // Mostrar los detalles del pedido
            printf("ID del Pedido: %s\n", getIdPedido(aux));
            printf("Nombre: %s\n", getNombre(aux));
            //Vendedor-----------------------------------------
            switch (getVendedor(aux))
            {
            case 1:
                printf("Vendedor: CJ\n");
                break;
            case 2:
                printf("Vendedor: Big Smoke\n");
                break;
            case 3:
                printf("Vendedor: Sweet\n");
                break;
            case 4:
                printf("Vendedor: Ryder\n");
                break;
            }
            // Forma de pago ----------------------------------
            switch (getFormaPago(aux))
            {
            case 1:
                printf("Opcion de pago: Debito\n");
                break;
            case 2:
                printf("Opcion de pago: Crédito\n");
                break;
            case 3:
                printf("Opcion de pago: QR\n");
                break;
            case 4:
                printf("Opcion de pago: Efectivo\n");
                break;
            }
            printf("Subtotal: %.2f\n", getSubtotal(aux));
            //Consume en el Local--------------------------------------------------
            if (getConsumeEnLocal(aux) == 1)
            {
                printf("Consumo en Local: SI\n");
            }
            else
            {
                printf("Consumo en Local: NO\n");
            }
            printf("Total: %.2f\n", getTotal(aux));
            // Fecha de Compra
            struct Fecha fecha = getFechaCompra(aux);
            printf("Fecha de Compra: %d/%d/%d\n", fecha.dia, fecha.mes, fecha.anio);
            // Entregado
            entregado = getEntregado(aux);
            if (entregado == 1)
            {
                printf ("Entregado: SI \n");
            }
            else
            {
                printf ("Entregado: NO \n");
            }
            paginador++;
        }
        forward_lista(&l);
    }

}

void mostrar_los_combos_sin_stock(Combo combos[])
{
    int i;
    for (i = 0; i <= 9; i++)
    {
        if (getStock(combos[i]) == 0)
        {
            printf("\n");
            printf("ID Combo: %d\n", getIdCombo(combos[i]));
            printf("Descripcion: %s\n", getDescripcion(&combos[i]));
            printf("Stock: %d\n", getStock(combos[i]));
            printf("Precio Unitario: $%.2f\n", getPrecioUnitario(combos[i]));
            if (getCuponDescuento(combos[i]) == 0)
            {
                printf("Descuento disponible: NO \n");
            }
            else
            {
                printf("Descuento disponible: SI \n");
            }
        }
    }
}

void mostrar_precio_y_stock_por_id_combo(Combo combos[])
{
    int id_combo_search;
    printf("\n Ingrese ID:");
    printf("\n -> ");
    scanf("%d", &id_combo_search);
    while(id_combo_search < 0 || id_combo_search > 10 )
    {
        printf("\n ID fuera de rango, Intente nuevamente.");
        printf("\n Ingrese ID:");
        printf("\n -> ");
        scanf("%d", &id_combo_search);
    }
    printf("\n Precio del Combo con ID: (%d) -->", id_combo_search);
    printf("$%.2f", getPrecioUnitario(combos[id_combo_search]));
    printf("\n Stock del Combo con ID: (%d) -->", id_combo_search);
    printf("%d", getStock(combos[id_combo_search]));
}

void mostrar_todos_los_pedidos_no_entregados(lista_cursores l)
{
    Pedido aux;
    initPedido(&aux);
    int entregado;
    reset(&l);
    while (isOos(l) == 1)
    {
        aux = copy_lista(l);
        entregado = getEntregado(aux);
        if (entregado == 0)
        {
            printf("\n");
            // Mostrar los detalles del pedido
            printf("ID del Pedido: %s\n", getIdPedido(aux));
            printf("Nombre: %s\n", getNombre(aux));
            switch (getVendedor(aux))
            {
            case 1:
                printf("Vendedor: CJ\n");
                break;
            case 2:
                printf("Vendedor: Big Smoke\n");
                break;
            case 3:
                printf("Vendedor: Sweet\n");
                break;
            case 4:
                printf("Vendedor: Ryder\n");
                break;
            }
            // Forma de pago ----------------------------------
            switch (getFormaPago(aux))
            {
            case 1:
                printf("Opcion de pago: Debito\n");
                break;
            case 2:
                printf("Opcion de pago: Crédito\n");
                break;
            case 3:
                printf("Opcion de pago: QR\n");
                break;
            case 4:
                printf("Opcion de pago: Efectivo\n");
                break;
            }
            printf("Subtotal: %.2f\n", getSubtotal(aux));
            if (getConsumeEnLocal(aux) == 1)
            {
                printf("Consumo en Local: SI\n");
            }
            else
            {
                printf("Consumo en Local: NO\n");
            }
            printf("Total: %.2f\n", getTotal(aux));
            // Fecha de Compra
            struct Fecha fecha = getFechaCompra(aux);
            printf("Fecha de Compra: %d/%d/%d\n", fecha.dia, fecha.mes, fecha.anio);
            printf ("Entregado: NO \n");
            system("PAUSE");
        }
        forward_lista(&l);
    }


}

void mostrar_pedidos(lista_cursores l)
{
    int vendedor_actual;
    int medio_de_pago;
    int validacion_consume;
    int entregado;
    Pedido aux;
    initPedido(&aux);
    reset(&l);
    while(isOos(l)!= 0)
    {

        aux = copy_lista(l);
        // Mostrar los detalles del pedido
        printf("\n ------------------------------------");
        printf("\n ID del Pedido: %s", getIdPedido(aux));
        printf("\n Nombre: %s", getNombre(aux));
        vendedor_actual = getVendedor(aux);
        if (vendedor_actual == 1)
        {
            printf("\n Vendedor: CJ");
        }
        if (vendedor_actual == 2)
        {
            printf("\n Vendedor: Big Smoke");
        }
        if (vendedor_actual == 3)
        {
            printf("\n Vendedor: Sweet");
        }
        if (vendedor_actual == 4)
        {
            printf("\n Vendedor: Ryder");
        }
        medio_de_pago = getFormaPago(aux);
        if (medio_de_pago == 1)
        {
            printf("\n Opcion de pago: Debito.");
        }
        if (medio_de_pago == 2)
        {
            printf("\n Opcion de pago: Crédito.");
        }
        if (medio_de_pago == 3)
        {
            printf("\n Opcion de pago: QR.");
        }
        if (medio_de_pago == 4)
        {
            printf("\n Opcion de pago: Efectivo.");
        }
        printf("\n Subtotal: %.2f", getSubtotal(aux));
        validacion_consume = getConsumeEnLocal(aux);
        if (validacion_consume == 1)
        {
            printf("\n Consumo en Local: SI");
        }
        if (validacion_consume == 0)
        {
            printf("\n Consumo en Local: NO");
        }
        printf("\n Total: %.2f", getTotal(aux));
        // Fecha de Compra
        struct Fecha fecha = getFechaCompra(aux);
        printf("\n Fecha de Compra: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);
        // Entregado
        entregado = getEntregado(aux);
        if (entregado == 1)
        {
            printf ("\n Entregado: SI ");
        }
        else
        {
            printf ("\n Entregado: NO ");
        }
        printf("\n ------------------------------------");
        forward_lista(&l);
    }
}

//-----------------------------------------MOSTRADORES----------------------------------------






//-----------------------------------------MODIFICADORES----------------------------------------

void modificar_la_forma_de_pago_de_un_pedido_segun_su_idpedido(lista_cursores *l)
{
    int x;
    int nuevo_estado;
    Pedido pedido_aux;
    initPedido(&pedido_aux);
    x = buscar_id_pedido(l);
    if (x == 1)
    {
        pedido_aux=copy_lista(*l);///almacena la informacion del pedido antes de eliminar el nodo que tiene errores
        supress_nodo(l);///Se elimina el nodo
        printf("\n Seleccione el nuevo estado del la nueva forma de pago:");
        printf("\n 1. Debito.");
        printf("\n 2. Credito.");
        printf("\n 3. QR.");
        printf("\n 4. Efectivo.");
        printf("\n -> ");
        scanf("%d", &nuevo_estado);
        while(nuevo_estado != 1 && nuevo_estado != 2 && nuevo_estado != 3 && nuevo_estado != 4)
        {
            printf("\n Error de seleccion!");
            printf("\n Seleccione nuevamente el estado del la nueva forma de pago:");
            printf("\n 1. Debito.");
            printf("\n 2. Credito.");
            printf("\n 3. QR");
            printf("\n 4. Efectivo.");
            printf("\n -> ");
            scanf("%d", &nuevo_estado);
        }
        setFormaPago(&pedido_aux,nuevo_estado);///se setea forma de pago en el aux
        insert_nodo_a_la_lista(l,pedido_aux);
        printf("\n");
        system("PAUSE");
    }
}


void modificar_nombre_de_un_pedido_segun_su_idpedido(lista_cursores *l)
{
    char nuevo_nombre[100];
    int x;
    Pedido pedido_aux;
    initPedido(&pedido_aux);
    x = buscar_id_pedido(l);
    if (x == 1)
    {
        pedido_aux = copy_lista(*l);///almacena la informacion del pedido antes de eliminar el nodo que tiene errores.
        supress_nodo(l);///Se elimina el nodo
        printf("\n Ingrese el nuevo nombre para el pedido.");
        printf("\n -> ");
        fflush(stdin);
        gets(nuevo_nombre);
        setNombre(&pedido_aux,nuevo_nombre);///se settea forma de pago en el aux.
        insert_nodo_a_la_lista(l,pedido_aux);
        system("PAUSE");
    }
}

void modificar_el_estado_del_pedido_a_entregado_por_idpedido(lista_cursores *l)
{
    Pedido pedido_aux;
    int nuevo_estado;
    int x;
    // Pedido aux;
    initPedido(&pedido_aux);
    x = buscar_id_pedido(l);
    if (x == 1)
    {
        pedido_aux=copy_lista(*l);///almacena la informacion del pedido antes de eliminar el nodo que tiene errores
        if (getEntregado(pedido_aux) == 0)
        {
            supress_nodo(l);///Se elimina el nodo
            nuevo_estado=1;
            setEntregado(&pedido_aux,nuevo_estado);///se setea forma de pago en el aux
            insert_nodo_a_la_lista(l,pedido_aux);
        }
        else
        {
            printf("\n Error.");
            printf("\n No se puede modificar el pedido, porque ya esta entregado.");
        }
    }

}

void modificar_precio_y_stock_del_combo_segun_idcombo(Combo *combo)
{
    int id_combo_search;
    float nuevo_precio;
    int nuevo_stock;
    printf("\n Ingrese ID: (0-9)");
    printf("\n -> ");
    scanf("%d", &id_combo_search);
    while(id_combo_search < 0 || id_combo_search > 10 )
    {
        printf("\n ID fuera de rango. Intente nuevamente.");
        printf("\n Ingrese ID: (0-9)");
        printf("\n -> ");
        scanf("%d", &id_combo_search);
    }
    printf("\n Ingrese el nuevo precio:");
    scanf("%f", &nuevo_precio);
    while(nuevo_precio <= 0 )
    {
        printf("\n Error en el precio, no puede ingresar un precio inexistente o negativo.");
        printf("\n Ingrese el nuevo precio nuevamente:");
        printf("\n -> ");
        scanf("%f", &nuevo_precio);
    }
    printf("\n Ingrese la cantidad de Stock agregada:");
    printf("\n -> ");
    scanf("%d", &nuevo_stock);
    while(nuevo_stock <= 0 )
    {
        printf("\n Error de stock, no puede ingresar una cantidad inexistente o negativa.");
        printf("\n Ingrese la cantidad de Stock agregada nuevamente:");
        printf("\n -> ");
        scanf("%d", &nuevo_stock);
    }
    ///SETTERS.
    setPrecioUnitario(&combo[id_combo_search], nuevo_precio);
    setStock(&combo[id_combo_search], (nuevo_stock + getStock(combo[id_combo_search])));
}

void cambio_vendedor_activo(int *vendedor_actual)
{
    int vendedor_nuevo;
    printf("\n Ingrese su ID:");
    printf("\n -> ");
    scanf("%d", &vendedor_nuevo);
    while(vendedor_nuevo < 1 || vendedor_nuevo > 4 )
    {
        printf("\n ID fuera de rango.");
        printf("\n Ingrese su ID nuevamente:");
        printf("\n -> ");
        scanf("%d", &vendedor_nuevo);
    }
    *vendedor_actual = vendedor_nuevo; ///Esta funcion se inicializa en el inicio del programa y en el menu.
    printf("\n Vendedor modificado con exito.");
    printf("\n");
    printf("\n Bienvenido ");
    if (vendedor_nuevo == 1)
    {
        printf("CJ!!!");
    }
    if (vendedor_nuevo == 2)
    {
        printf("Big Smoke!!!");
    }
    if (vendedor_nuevo == 3)
    {
        printf("Sweet!!!");
    }
    if (vendedor_nuevo == 4)
    {
        printf("Ryder!!!");
    }
}

void anular_pedido_por_idpedido(lista_cursores *l)
{
    FILE *fp1;
    int x; //Variable de Control de BUSCARID
    int entregado;
    char nombre_mil[100];
    Pedido pedido_aux;
    initPedido(&pedido_aux);
    x = buscar_id_pedido(l);
    pedido_aux = copy_lista(*l);///almacena la informacion del pedido antes de eliminar el nodo que tiene errores
    strcpy(nombre_mil, getNombre(pedido_aux));
    supress_nodo(l);///Se elimina el nodo
    fp1 = fopen("anulados.txt", "a+");
    if (fp1==NULL)
    {
        printf ("ERROR FATAL.");
        printf("\n No se pudo abrir el archivo de pedidos anulados.");
        printf("\n");
        system("PAUSE");
        exit(1);
    }
    else
    {
        if (x == 1)
        {
            fprintf(fp1,"-----TICKET ANULADO-----\n");
            fprintf(fp1,"ID del Pedido: %s \n", getIdPedido(pedido_aux));
            fprintf(fp1,"Nombre: %s \n", nombre_mil);
            //-------------------------------------------------------------------------
            switch (getVendedor(pedido_aux))
            {
            case 1:
                fprintf(fp1,"Vendedor: CJ\n");
                break;
            case 2:
                fprintf(fp1,"Vendedor: Big Smoke\n");
                break;
            case 3:
                fprintf(fp1,"Vendedor: Sweet\n");
                break;
            case 4:
                fprintf(fp1,"Vendedor: Ryder\n");
                break;
            }
            //--------------------------------------------------------------------------
            fprintf(fp1,"Forma de Pago: %d\n", getFormaPago(pedido_aux));
            //--------------------------------------------------------------------------
            switch (getFormaPago(pedido_aux))
            {
            case 1:
                fprintf(fp1,"Opcion de pago: Debito\n");
                break;
            case 2:
                fprintf(fp1,"Opcion de pago: Crédito\n");
                break;
            case 3:
                fprintf(fp1,"Opcion de pago: QR\n");
                break;
            case 4:
                fprintf(fp1,"Opcion de pago: Efectivo\n");
                break;
            }
            fprintf(fp1,"Subtotal: %.2f\n", getSubtotal(pedido_aux));
            //--------------------------------------------------------------------------
            if (getConsumeEnLocal(pedido_aux) == 1)
            {
                fprintf (fp1,"Consumo en Local: SI \n");
            }
            else
            {
                fprintf (fp1,"Consumo en Local: NO \n");
            }
            //-------------------------------------------------
            fprintf(fp1,"Total: %.2f\n", getTotal(pedido_aux));
            // Fecha de Compra
            struct Fecha fecha = getFechaCompra(pedido_aux);
            fprintf(fp1,"Fecha de Compra: %d/%d/%d\n", fecha.dia, fecha.mes, fecha.anio);
            // Entregado
            entregado = getEntregado(pedido_aux);
            if (entregado == 1)
            {
                fprintf (fp1,"Entregado: SI \n");
            }
            else
            {
                fprintf (fp1,"Entregado: NO \n");
            }
            fprintf (fp1,"-----TICKET ANULADO-----\n");
        }
    }
    fclose(fp1);
}

//-----------------------------------------MODIFICADORES----------------------------------------


//-----------------------------------------ALMACENADORES----------------------------------------

void almacenar_datos_por_forma_de_pago(lista_cursores l)
{
    int forma_pago_x ;
    int entregado;
    FILE *fp2;
    Pedido pedido_aux;
    initPedido(&pedido_aux);
    reset(&l);
    fp2 = fopen("tickets por forma de pago.txt", "a+");
    if (fp2==NULL)
    {
        printf("\n ERROR FATAL.");
        printf("\n No se pudo abrir el archivo de pedidos almacenados por forma de pago.");
        system("PAUSE");
        exit(1);
    }
    printf("\n Ingrese la forma de pago a almacenar.");
    printf("\n 1. Debito");
    printf("\n 2. Credito");
    printf("\n 3. QR");
    printf("\n 4. Efectivo");
    printf("\n -> ");
    scanf("%d",&forma_pago_x);

    while(forma_pago_x>4||forma_pago_x<1)
    {
        printf("Valor incorrecto, ingrese la forma de pago nuevamente.");
        printf("\n 1. Debito");
        printf("\n 2. Credito");
        printf("\n 3. QR");
        printf("\n 4. Efectivo");
        printf("\n -> ");
        scanf("%d",&forma_pago_x);

    }
    while (isOos(l) == 1)
    {
        pedido_aux = copy_lista(l);
        if(forma_pago_x == getFormaPago(pedido_aux) && forma_pago_x == 1)
        {
            fprintf(fp2,"\n-----TICKET DEBITO-----");
            fprintf(fp2,"\nID del Pedido: %s", getIdPedido(pedido_aux));
            fprintf(fp2,"\nNombre: %s", getNombre(pedido_aux));
            switch (getVendedor(pedido_aux))
            {
            case 1:
                fprintf(fp2,"\nVendedor: CJ.");
                break;
            case 2:
                fprintf(fp2,"\nVendedor: Big Smoke.");
                break;
            case 3:
                fprintf(fp2,"\nVendedor: Sweet.");
                break;
            case 4:
                fprintf(fp2,"\nVendedor: Ryder.");
                break;
            }
            fprintf(fp2,"\nForma de Pago: DEBITO.");
            fprintf(fp2,"\nSubtotal: $ %.2f", getSubtotal(pedido_aux));
            //--------------------------------------------------------------------------
            if (getConsumeEnLocal(pedido_aux) == 1)
            {
                fprintf (fp2,"Consumo en Local: SI.");
            }
            else
            {
                fprintf (fp2,"Consumo en Local: NO.");
            }
            //-------------------------------------------------
            fprintf(fp2,"\n Total: $ %.2f", getTotal(pedido_aux));
            // Fecha de Compra
            struct Fecha fecha = getFechaCompra(pedido_aux);
            fprintf(fp2,"\n Fecha de Compra: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);
            // Entregado
            entregado = getEntregado(pedido_aux);
            if (entregado == 1)
            {
                fprintf (fp2,"\n Entregado: SI ");
            }
            else
            {
                fprintf (fp2,"\n Entregado: NO");
            }
            fprintf (fp2,"\n -----TICKET DEBITO-----");
            fprintf (fp2,"\n -------------------------");

        }
        if(forma_pago_x == getFormaPago(pedido_aux) && forma_pago_x == 2)
        {
            fprintf(fp2,"\n -----TICKET CREDITO-----");
            fprintf(fp2,"\n ID del Pedido: %s", getIdPedido(pedido_aux));
            fprintf(fp2,"\n Nombre: %s", getNombre(pedido_aux));
            switch (getVendedor(pedido_aux))
            {
            case 1:
                fprintf(fp2,"\nVendedor: CJ.");
                break;
            case 2:
                fprintf(fp2,"\nVendedor: Big Smoke.");
                break;
            case 3:
                fprintf(fp2,"\nVendedor: Sweet.");
                break;
            case 4:
                fprintf(fp2,"\nVendedor: Ryder.");
                break;
            }
            fprintf(fp2,"\n Forma de Pago: CREDITO");
            fprintf(fp2,"\n Subtotal: $ %.2f", getSubtotal(pedido_aux));
            //--------------------------------------------------------------------------
            if (getConsumeEnLocal(pedido_aux) == 1)
            {
                fprintf (fp2,"Consumo en Local: SI.");
            }
            else
            {
                fprintf (fp2,"Consumo en Local: NO.");
            }
            //-------------------------------------------------
            fprintf(fp2,"\n Total: $ %.2f", getTotal(pedido_aux));
            // Fecha de Compra
            struct Fecha fecha = getFechaCompra(pedido_aux);
            fprintf(fp2,"\n Fecha de Compra: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);
            // Entregado
            entregado = getEntregado(pedido_aux);
            if (entregado == 1)
            {
                fprintf (fp2,"\n Entregado: SI ");
            }
            else
            {
                fprintf (fp2,"\n Entregado: NO");
            }
            fprintf (fp2,"\n -----TICKET CREDITO-----");
            fprintf (fp2,"\n -------------------------");

        }

        if(forma_pago_x == getFormaPago(pedido_aux) && forma_pago_x == 3)
        {
            fprintf(fp2,"\n -----TICKET QR-----");
            fprintf(fp2,"\n ID del Pedido: %s", getIdPedido(pedido_aux));
            fprintf(fp2,"\n Nombre: %s", getNombre(pedido_aux));
            switch (getVendedor(pedido_aux))
            {
            case 1:
                fprintf(fp2,"\nVendedor: CJ.");
                break;
            case 2:
                fprintf(fp2,"\nVendedor: Big Smoke.");
                break;
            case 3:
                fprintf(fp2,"\nVendedor: Sweet.");
                break;
            case 4:
                fprintf(fp2,"\nVendedor: Ryder.");
                break;
            }
            fprintf(fp2,"\n Forma de Pago: QR");
            fprintf(fp2,"\n Subtotal: $ %.2f", getSubtotal(pedido_aux));
            //--------------------------------------------------------------------------
            if (getConsumeEnLocal(pedido_aux) == 1)
            {
                fprintf (fp2,"Consumo en Local: SI.");
            }
            else
            {
                fprintf (fp2,"Consumo en Local: NO.");
            }
            //-------------------------------------------------
            fprintf(fp2,"\n Total: $ %.2f", getTotal(pedido_aux));
            // Fecha de Compra
            struct Fecha fecha = getFechaCompra(pedido_aux);
            fprintf(fp2,"\n Fecha de Compra: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);
            // Entregado
            entregado = getEntregado(pedido_aux);
            if (entregado == 1)
            {
                fprintf (fp2,"\n Entregado: SI ");
            }
            else
            {
                fprintf (fp2,"\n Entregado: NO");
            }
            fprintf (fp2,"\n -----TICKET QR-----");
            fprintf (fp2,"\n -------------------------");
        }
        if(forma_pago_x == getFormaPago(pedido_aux) && forma_pago_x == 4)
        {
            fprintf(fp2,"\n -----TICKET EFECTIVO-----");
            fprintf(fp2,"\n ID del Pedido: %s", getIdPedido(pedido_aux));
            fprintf(fp2,"\n Nombre: %s", getNombre(pedido_aux));
            switch (getVendedor(pedido_aux))
            {
            case 1:
                fprintf(fp2,"\nVendedor: CJ.");
                break;
            case 2:
                fprintf(fp2,"\nVendedor: Big Smoke.");
                break;
            case 3:
                fprintf(fp2,"\nVendedor: Sweet.");
                break;
            case 4:
                fprintf(fp2,"\nVendedor: Ryder.");
                break;
            }
            fprintf(fp2,"\n Forma de Pago: EFECTIVO");
            fprintf(fp2,"\n Subtotal: $ %.2f", getSubtotal(pedido_aux));
            //--------------------------------------------------------------------------
            if (getConsumeEnLocal(pedido_aux) == 1)
            {
                fprintf (fp2,"Consumo en Local: SI.");
            }
            else
            {
                fprintf (fp2,"Consumo en Local: NO.");
            }
            //-------------------------------------------------
            fprintf(fp2,"\n Total: $ %.2f", getTotal(pedido_aux));
            // Fecha de Compra
            struct Fecha fecha = getFechaCompra(pedido_aux);
            fprintf(fp2,"\n Fecha de Compra: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);
            // Entregado
            entregado = getEntregado(pedido_aux);
            if (entregado == 1)
            {
                fprintf (fp2,"\n Entregado: SI ");
            }
            else
            {
                fprintf (fp2,"\n Entregado: NO");
            }
            fprintf (fp2,"\n-----TICKET EFECTIVO-----");
            fprintf (fp2,"\n-------------------------");
        }

        forward_lista(&l);
    }
    fclose(fp2);
    printf("Carga realizada con exito!!!");
    system("PAUSE");
}

//---------------------------------------------------------------------------------



///-----------------------------------------Herramientas para las funciones----------------------------------------

// Función que obtiene el último valor almacenado en el archivo, lo incrementa y crea la cadena "GrooveB-" + número.
char *generatePibeString(const char *archivoDeGuardado)
{
    int ultimoGuardado = 0;
    FILE *archivo = fopen(archivoDeGuardado, "r+");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo %s.\n", archivoDeGuardado);
        exit(1);
    }

    fscanf(archivo, "%d", &ultimoGuardado);

    ultimoGuardado++;

    fseek(archivo, 0, SEEK_SET);
    fprintf(archivo, "%d", ultimoGuardado);

    fclose(archivo);

    char guardadoStr[20]; // Suficientemente grande para almacenar números enteros
    sprintf(guardadoStr, "%d", ultimoGuardado);
    char *pibeString = (char *)malloc(strlen("PROG") + strlen(guardadoStr) + 1);

    if (pibeString == NULL)
    {
        printf("Error de asignacion de memoria.\n");
        exit(1);
    }

    strcpy(pibeString, "PROG");
    strcat(pibeString, guardadoStr);

    return pibeString;
}

// busca por id pedido
int buscar_id_pedido(lista_cursores *l)
{
    int charly;
    char id_comparar[17];
    char id_buscar[17];
    Pedido aux;
    initPedido(&aux);
    reset(l);
    printf("\n Ingrese un Id de pedido: ");
    printf("\n -> ");
    fflush(stdin);
    scanf("%s",id_buscar);
//  strcat(id_buscar,"\0");
    while (isOos(*l) == 1)
    {
        fflush(stdin);
        aux = copy_lista(*l);
        strcpy(id_comparar, getIdPedido(aux));
        charly = strcmp(id_buscar, id_comparar);
        if (charly == 0)
        {
            return 1;
        }
        forward_lista(l);
    }
    printf("\n ID INVALIDO O NO ENCONTRADO.");
    printf("\n");
    return 0;
}



int maximo(int a, int b, int c, int d) //Funcion auxiliar.
{
    int max = a;
    if (b > max)
    {
        max = b;
    }
    if (c > max)
    {
        max = c;
    }
    if (d > max)
    {
        max = d;
    }
    return max;
}

void obtenerFechaActual(int *dia, int *mes, int *anio) //Funcion auxiliar.
{
    // Obtener el tiempo actual en segundos desde el Epoch (1970-01-01 00:00:00 UTC).
    time_t tiempoActual;
    time(&tiempoActual);

    // Convertir el tiempo actual a una estructura de tiempo local.
    struct tm *infoLocal = localtime(&tiempoActual);

    // Obtener el día, mes y año actual.
    *dia = infoLocal->tm_mday;
    *mes = infoLocal->tm_mon + 1;  // tm_mon va de 0 a 11, así que sumamos 1.
    *anio = infoLocal->tm_year + 1900;  // tm_year cuenta los años desde 1900.
}

int obtenerNumeroEntero()
{
    int numero;
    char entrada[20];
    int conversionExitosa = 0;

    while (!conversionExitosa)
    {
        printf(" ");
        if (fgets(entrada, sizeof(entrada), stdin) != NULL)
        {
            // Intentar convertir la entrada a un entero
            if (sscanf(entrada, "%d", &numero) == 1)
            {
                conversionExitosa = 1;
            }
            else
            {
                printf("Entrada no valida.\n");
            }
        }
        else
        {
            printf("Error al leer la entrada.\n");
            exit(EXIT_FAILURE);
        }
    }

    return numero;
}

///-----------------------------------------Herramientas para las funciones----------------------------------------

///-----------------------------------------RECURSIVAS----------------------------------------

int contar_los_pedidos_realizados_por_un_vendedor(lista_cursores l,int vendedor_x,int contador,Pedido auxC)
{
    if(isOos(l) == 0)
    {
        return contador;
    }
    else
    {
        auxC = copy_lista(l);
        if(getVendedor(auxC)==vendedor_x)
        {
            contador++; //CONTADOR INCIALIZADO EN 0.
        }
        forward_lista(&l);
    }
    return contar_los_pedidos_realizados_por_un_vendedor(l, vendedor_x, contador, auxC);
}

void mostrar_los_pedidos_realizados_por_un_vendedor(lista_cursores l,int vendedor_x,Pedido aux)///reset en el main antes de invocar
{
    if(isOos(l)== 0)
    {
        return;
    }
    else
    {
        aux = copy_lista(l);
        if(getVendedor(aux) == vendedor_x)
        {
            printf("\n ID del Pedido: %s", getIdPedido(aux));
            printf("    --- Total: %.2f\n", getTotal(aux));
            system("PAUSE");
        }
        forward_lista(&l);
    }
    return mostrar_los_pedidos_realizados_por_un_vendedor(l, vendedor_x,aux);
}


///---------------------------------------------------------------------------------


