Test_Cintelink
Código propuesto para resolución de test provisto por Cintelink.

Este proyecto es un generador de log de transacciones de combustible en lenguaje C. Permite procesar datos de transacciones y generar un registro ordenado por fecha y hora. A continuación, se proporcionan detalles sobre cómo usar y personalizar el generador de log.

Para este caso se cargan las cadenas desde el código por cuestiones surgidas durante la realización del proyecto.

Cada transaccion proporcionada debe ser cargada en la cadena con el siguiente formato:
[dd/mm/yy hh:mm:ss]\0AAA 111A10030±DDDD
Donde cada transacción extra se deberá cargar directamente a continuación sin ningun carater intermedio entre transacciones.

La cadena provista de testeo es la siguiente:
[06/02/22 00:16:03]\0XTT 5547A-10030[05/02/22 23:16:27]\0AXJ 3658G008015[05/02/22 23:45:33]\0YCC 9001G32313
![imagen](https://github.com/Nehuix/Test_Cintelink/assets/87344666/83297a91-e4ed-427e-9945-5ec09d85dc8e)


Y la salida será:
![imagen](https://github.com/Nehuix/Test_Cintelink/assets/87344666/4d3ac204-52e1-4257-bc63-ac261a628c46)


Finalmente, pido disculpas por no cumplir la consigna en su totalidad y agradezco por la oportunidad de probar mis conocimientos.
