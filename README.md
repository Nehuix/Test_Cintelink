# Test_Cintelink
Código propuesto para resolución de test provisto por Cintelink.

Este proyecto es un generador de log de transacciones de combustible en lenguaje C. Permite procesar datos de transacciones y generar un registro ordenado por fecha y hora. A continuación, se proporcionan detalles sobre cómo usar y personalizar el generador de log.

Para este caso se cargan las cadenas desde el código por cuestiones surgidas durante la realización del proyecto.

Cada transaccion proporcionada debe ser cargada en la cadena con el siguiente formato:
[dd/mm/yy hh:mm:ss]\0AAA 111A10030±DDDD
Donde cada transacción extra se deberá cargar directamente a continuación sin ningun carater intermedio entre transacciones.

La cadena provista de testeo es la siguiente:
[06/02/22 00:16:03]\0XTT 5547A-10030[05/02/22 23:16:27]\0AXJ 3658G008015[05/02/22 23:45:33]\0YCC 9001G32313

Y la salida será:

Log generado:
[05/02/22 23:16:27] id: 00015, reg: AXJ 3658, prod: G, ltrs: +000080
[05/02/22 23:45:33] id: 00003, reg: YCC 9001, prod: G, ltrs: +003231
[06/02/22 00:16:03] id: 00030, reg: XTT 5547, prod: A, ltrs: -000100
Total de bytes escritos: 207

Finalmente, pido disculpas por no cumplir la consigna en su totalidad y agradezco por la oportunidad de probar mis conocimientos.
