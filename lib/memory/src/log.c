#include "../include/log.h"

// Estructura global para almacenar mensajes
static char **log_buffer = NULL; // Array de cadenas (buffer)
static size_t log_count = 0;     // Número de mensajes en el buffer
static size_t log_capacity = 0;  // Capacidad actual del buffer
static int log_fd = -1;          // Descriptor de archivo en lugar de FILE*

void init_log(const char *filename) {
  log_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (log_fd == -1) {
    const char *error_msg = "Failed to open log file\n";
    write(STDERR_FILENO, error_msg, strlen(error_msg));
    exit(EXIT_FAILURE);
  }

  // Inicializar el buffer
  log_capacity = 50;
  log_buffer = (char **)malloc(log_capacity * sizeof(char *));
  if (log_buffer == NULL) {
    const char *error_msg = "Failed to allocate log buffer\n";
    write(STDERR_FILENO, error_msg, strlen(error_msg));
    exit(EXIT_FAILURE);
  }
  log_count = 0;
}

char *get_current_time() {
  time_t now = time(NULL);
  char *timestamp = ctime(&now);
  timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline character
  return timestamp;
}

void log_message(const char *message) {
  if (log_buffer == NULL)
    return;

  char *time_str = get_current_time();
  // Crear el mensaje completo manualmente
  char temp_message[MAX_MESSAGE_LENGTH];
  size_t time_len = strlen(time_str);
  size_t msg_len = strlen(message);

  if (time_len + msg_len + 4 > MAX_MESSAGE_LENGTH)
    return; // Evita desbordamiento

  memcpy(temp_message, "[", 1);
  memcpy(temp_message + 1, time_str, time_len);
  memcpy(temp_message + 1 + time_len, "] ", 2);
  memcpy(temp_message + 3 + time_len, message, msg_len);
  temp_message[3 + time_len + msg_len] = '\0'; // Null-terminar

  // Guardar mensaje en el buffer
  if (log_count >= log_capacity) {
    log_capacity *= 2;
    char **new_buffer =
        (char **)realloc(log_buffer, log_capacity * sizeof(char *));
    if (new_buffer == NULL) {
      const char *error_msg = "Failed to expand log buffer\n";
      write(STDERR_FILENO, error_msg, strlen(error_msg));
      exit(EXIT_FAILURE);
    }
    log_buffer = new_buffer;
  }

  log_buffer[log_count] = (char *)malloc(strlen(temp_message) + 1);
  if (log_buffer[log_count] == NULL) {
    const char *error_msg = "Failed to store log message\n";
    write(STDERR_FILENO, error_msg, strlen(error_msg));
    exit(EXIT_FAILURE);
  }
  memcpy(log_buffer[log_count], temp_message, strlen(temp_message) + 1);
  log_count++;
}

void close_log() {
  if (log_fd != -1 && log_buffer != NULL) {
    for (size_t i = 0; i < log_count; i++) {
      if (log_buffer[i] != NULL) {
        size_t len = strlen(log_buffer[i]);
        write(log_fd, log_buffer[i], len);
        write(log_fd, "\n", 1);
        free(log_buffer[i]);
      }
    }
    close(log_fd);
    log_fd = -1;

    free(log_buffer);
    log_buffer = NULL;
    log_count = 0;
    log_capacity = 0;
  }
}
