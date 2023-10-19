#include <stdio.h> //funciones i/o standard
#include <stdlib.h>//funciones de gestion de memoria
#include <string.h>//operaciones de cadena
#include <stdint.h>//datos con ancho fijo

#define MAX_TRANSACTIONS 100 //n° máx de transacciones a procesar

// Estructura para representar una transacción
struct Transaction {
    char timestamp[20];           // 19 caracteres + terminador nulo
    char vehicle_registration[9];  // 8 caracteres + terminador nulo
    char product;
    int32_t mililiters;
    uint16_t transaction_id;
};

/* Función de comparación para qsort (p/ ordenar transacciones por fecha)
   toma dos punteros const void * como args. Y los compara.
   Argumentos: const void *a
               const void *b
    Return: 0 si las cadenas son iguales
            <0 si trans_a<trans_b
            >0 si trans_b<trans_a
*/
int compararTransacciones(const void *a, const void *b) { //Son const void * para que la función sea genérica y se pueda usar con "qsort"
    struct Transaction *trans_a = (struct Transaction *)a;//crea un puntero de tipo "struct Transaction *"
    struct Transaction *trans_b = (struct Transaction *)b;//y se le asigna el valor del puntero a/b

    // Implementar la comparación de fechas acá de menor a mayor
    return strcmp(trans_a->timestamp, trans_b->timestamp);//se compara el tampo "timestamp"
}

/* Función para generar el log de transacciones de combustible
   Argunentos: const char *data -> puntero al inicio del buffer que contiene las transacciones redibidas
               char *log        -> puntero al inicio del buffer donde se genera el log de transacciones
               size_t transaction_count ->numero de transacciones en el buffer "data" que se pueden procesar

   Return:
*/
int log_transactions(const char *data, char *log, size_t transaction_count) {

    // Verificamos el número máximo de transacciones a procesar
    if (transaction_count > MAX_TRANSACTIONS) {
        return -1; // Se excede el límite
    }

    // Reservamos memoria para almacenar las transacciones
    struct Transaction transactions[MAX_TRANSACTIONS];
    memset(transactions, 0, sizeof(transactions)); //se inicializa transactions con ceros

    // Copiamos las transacciones desde el buffer de datos
    const char *ptr = data;
    for (size_t i = 0; i < transaction_count; i++) {//Procesa las transacciones en "data"
        memcpy(&transactions[i].timestamp, ptr, 20);//Copia a la estructura transaction desde
        ptr += 20;
                                         //ptr con "memcpy" y se suma el tamaño de la variable copiada
        memcpy(&transactions[i].vehicle_registration, ptr, 8);//Se repite el proceso
        ptr += 8;

        transactions[i].product = *ptr; //Al ser un caracter, se asigna directamente
        ptr++;

        char mililiters_str[5];        //variable donde se almacenara
        memcpy(mililiters_str, ptr, 4);//la cadena de mililitros
        mililiters_str[4]='\0';

        transactions[i].mililiters = atoi(mililiters_str);//convierte la cadena "mililiters_str" a
                                                          //a un valor entero
        ptr += 4; // Avanzar 5 caracteres para saltar la cadena de litros

        char transaction_id_str[3]; // Aumentamos el tamaño en 1 para el carácter nulo
        memcpy(transaction_id_str, ptr, 2);
        transaction_id_str[2] = '\0'; // Agregamos el carácter nulo

        transactions[i].transaction_id = atoi(transaction_id_str);
        ptr += 2;
    }

    /* Ordenamos las transacciones por fecha
       transactions               -> arreglo a ordenar
       transaction_count          -> número de elementos en el arreglo a ser ordenados
       sizeof(struct Transaction) -> tamaño de cada elemento del arreglo
       compararTransacciones      -> función que determina como ordenar los elementos

    */
    qsort(transactions, transaction_count, sizeof(struct Transaction), compararTransacciones);

    // Generamos el log
    char *log_ptr = log;//lleva el registro del lugar actual en el buffer de "log"
    for (size_t i = 0; i < transaction_count; i++) {//Se formatea cada transacción
        sprintf(log_ptr, "%s id: %05u, reg: %s, prod: %c, ltrs: %+07d\n", //Genera la cadena a mostrar
                transactions[i].timestamp, transactions[i].transaction_id,
                transactions[i].vehicle_registration, transactions[i].product,
                transactions[i].mililiters);

        log_ptr += strlen(log_ptr);//se avanza el puntero log_ptr hacia el final de la cadena
    }

    // Devolvemos la cantidad total de bytes escritos en el log
    return log_ptr - log; //resta el puntero "log" (inicio del búfer) al puntero "log_ptr" (último byte escrito en el bufer)
}

int main() {
    // Ejemplo de uso
    char data[] = "[06/02/22 00:16:03]\0XTT 5547A-10030[05/02/22 23:16:27]\0AXJ 3658G008015[05/02/22 23:45:33]\0YCC 9001G32313";
    char log_buffer[100]; // Debes elegir un tamaño adecuado
    size_t transaction_count = 3;
    int bytes_written = log_transactions(data, log_buffer, transaction_count);

    if (bytes_written >= 0) {
        printf("Log generado:\n%s", log_buffer);
        printf("Total de bytes escritos: %d\n", bytes_written);
    } else {
        printf("Se excede el límite de transacciones a procesar."); //En caso de que las transacciones sean mayores que el límite "MAX_TRANSATIONS
    }

    return 0;
}
