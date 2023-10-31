----------------- README -----------------------

Bienvenidos al sistema de Inmobiliaria Bubú!!!!

Nuestro sistema cuenta con muchas funciones a las cuales se accede a través del teclado, entre ellas:

1) Crea automáticamente un archivo binario ‘propiedades.dat’ el cual contiene todas sus propiedades.

Las propiedades tienen la siguiente estructura:

Propiedad {
    id
    fecha de ingreso
    zona
    ciudad o barrio
    dormitorios
    baños
    superficie total
    superficie cubierta
    precio
    moneda
    tipo de propiedad
    operacion
    fecha de salida
    activo o inactivo
}

2) Listar dat: 
		Emite por pantalla el contenido del archivo binario con sus respectivos títulos de columna, dándole la posibilidad de elegir
		entre diversos modos de presentación:
				a) Listar todos (altas y bajas)
				b) Listar sólo las propiedades activas.
				c) Listar sólo un tipo de propiedad ingresada por teclado.
				d) Listar las propiedades dentro de un rango de fecha de ingreso.
	
3) Alta: 
		Es el registro de nuevas propiedades al sistema, para ello se debe tener en cuenta que el número de id siempre será un número positivo, e
		indica la posición dónde se grabarán los datos en el archivo. Los campos de las filas intermedias que no fueron cargados quedarán en 0 (cero). 
		Considerar en el alta:
				Si con el número de id ingresado existe un registro de datos cargado, se pide un nuevo número de id. El programa no continúa hasta que la entrada sea correcta.
				Si el número de id ingresado es negativo, se emite un error y se vuelve a pedir otro valor. 
				En el caso de altas la propiedad se activa automáticamente, en el alta, este campo no se ingresa por teclado.
				En el caso de los campos: tipo de propiedad, operación y moneda, se le dará opciones para ingresar por teclado, en lugar de un campo para rellenar.
				En el caso de la fecha: 
					La fecha de salida o egreso de la propiedad no puede ser mayor que la actual
					La fecha de ingreso no puede ser menor al año 1900.
					
4) Buscar: permite buscar los datos de una propiedad con las siguientes sub-opciones:
				e) por id
				f) por tipo de operación y luego por tipo de propiedad
	
5) Baja lógica: 
				Da de baja una propiedad. Antes de dar la baja, el programa emite los datos y pide confirmación. 
				Luego, el campo activo de la propiedad se pone en cero, y la fecha de salida cambia a la fecha actual.

6) Modificar: permite modificar datos de una propiedad con las siguientes sub-opciones:
				g) Ciudad/Barrio o precio, el acceso al registro será por el número de id y antes de sobreescribir el registro
				en el archivo, el programa deberá preguntar: Está seguro que desea modificar los datos de …?. Y dar la opción al usuario por sí o por
				no.
				h) La fecha de salida. (no debe exceder la fecha actual). Con ésta operación también se registra la baja lógica.

10) Baja física: 
			Construye un nuevo archivo de texto ‘propiedades_bajas_<fecha>.xyz’ con la fecha actual, en el que se grabarán sólo los datos de las propiedades inactivas.
			Simultáneamente se eliminan dichas propiedades del archivo 'propiedades.dat'.
			
11) Listar xyz: 
			Imprime por pantalla el archivo de ‘propiedades_bajas_<fecha>.xyz’ construido en el paso anterior.

Dicho sistema se asegura de evitar errores en el ingreso de datos como ser el de caracteres erroneos, fechas que se excedan a la fecha actual y que los numeros con coma se registren como tal. Las propiedades que se pretenden, buscar o modificar realmente se encuentren dentro del archivo. Ademas, se busca que la propiedad que se pretende dar de baja sea correcta y sin fecha de salida.
