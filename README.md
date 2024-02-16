<h1> Sistema de Gestión de Pedidos 🍔</h1>


<h2>Este es un sistema de gestión de pedidos desarrollado en C 🔧 . Permite realizar diversas operaciones relacionadas con la administración de pedidos, vendedores y combos.</h2>

 <h3> :hammer:Funcionalidades</h3>

El sistema ofrece las siguientes funcionalidades:

- **Cargar un pedido por teclado:** Permite cargar un pedido en la lista por teclado, respetando la posición de cada combo. Si la cantidad solicitada de un combo no está en stock, se informa la cantidad disponible. Se calcula el subtotal, costo de delivery y total al final de la carga del pedido.

- **Buscar un pedido por idpedido:** Función interna que permite buscar un pedido por su idpedido.

- **Mostrar los datos del pedido buscado:** Utiliza la función de búsqueda anterior para mostrar los datos del pedido buscado.

- **Mostrar todos los pedidos de un mes ordenados por fecha:** Muestra todos los pedidos de un mes, opcionalmente ordenados por fecha.

- **Mostrar los pedidos por nombre, paginando la muestra de los datos:** Permite mostrar los pedidos por nombre, con la opción de paginar la muestra de los datos.

- **Mostrar los pedidos realizados por un vendedor (función recursiva):** Muestra los pedidos realizados por un vendedor de manera recursiva, mostrando el total e idpedido.

- **Contar los pedidos realizados por un vendedor (función recursiva):** Cuenta los pedidos realizados por un vendedor de manera recursiva.

- **Modificar el estado del pedido a entregado por idpedido:** Permite modificar el estado de un pedido a entregado utilizando su idpedido.

- **Modificar la forma de pago de un pedido según su idpedido:** Permite modificar la forma de pago de un pedido utilizando su idpedido.

- **Modificar nombre de un pedido según su idpedido:** Permite modificar el nombre de un pedido utilizando su idpedido.

- **Anular un pedido por idpedido:** Anula un pedido utilizando su idpedido, copiando sus datos en un archivo antes de eliminarlo.

- **Almacenar en un archivo los datos de los pedidos pagados según una forma de pago:** Almacena en un archivo los datos de los pedidos pagados según una forma de pago pasada por parámetro, decodificando los campos codificados para que sean legibles desde un editor de texto.

- **Precarga de pedidos anteriores mediante un archivo entregado por la cátedra:** Permite realizar la precarga de pedidos anteriores utilizando un archivo entregado por el Negocio.

- **Mostrar todos los pedidos no entregados:** Muestra todos los pedidos que no han sido entregados.

- **Precarga automática de combos al iniciar el programa:** Realiza una precarga automática de los combos en el arreglo al iniciar el programa.

- **Modificar precio y stock del combo según idcombo:** Permite modificar el precio y el stock de un combo utilizando su idcombo.

- **Mostrar todos los combos:** Muestra todos los combos disponibles.

- **Mostrar precio y stock de un combo por idcombo:** Muestra el precio y el stock de un combo utilizando su idcombo.

- **Mostrar los combos sin stock:** Informa cuáles son los combos que no tienen stock disponible.

- **Informar el vendedor que realizó más pedidos en el mes:** Determina y muestra el vendedor que realizó más pedidos en el mes.

- **Cambiar el vendedor activo:** Permite cambiar el vendedor activo utilizando uno de los valores establecidos.
