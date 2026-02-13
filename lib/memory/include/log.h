/**
 * @file log.h
 * @brief Log management library.
 *
 * Esta biblioteca define funciones para escribir mensajes de log en un archivo.
 */
#ifndef LOG_H
#define LOG_H

#include <fcntl.h> // Para open y flags de archivos
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Para write

#define MAX_MESSAGE_LENGTH 256

/**
 * @brief Inicializa el archivo de log.
 *
 * @param filename Nombre del archivo de log.
 */
void init_log(const char *filename);

/**
 * @brief Obtiene la hora actual en formato legible.
 *
 * @param buffer Buffer para almacenar la hora.
 * @param size Tamaño del buffer.
 */
char *get_current_time();

/**
 * @brief Escribe un mensaje de log en un archivo.
 *
 * @param message Mensaje a escribir en el log.
 */
void log_message(const char *message);

/**
 * @brief Cierra el archivo de log.
 */
void close_log();

#endif // LOG_H
