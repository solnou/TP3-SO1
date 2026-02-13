#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <unity.h>
#include "../include/memory.h"

#define NUM_BLOCKS 10

void setUp(void)
{
    // Set up code if needed
}

void tearDown(void)
{
    // Tear down code if needed
}

float calcular_fragmentacion(void) {
    size_t total_asignada = 0;
    size_t total_libre = 0;
    size_t cantidad_bloques_libres = 0;
    size_t calidad = 0;

    // Llamamos a la función para obtener los datos de memoria
    memory_usage(&total_asignada, &total_libre, &cantidad_bloques_libres, &calidad);

    // Si no hay memoria libre, no hay fragmentación
    if (total_libre == 0) {
        return 0.0;
    }

    // Cálculo de la calidad y la fragmentación
    double calidad_porcentaje = sqrt((double)calidad) / (double)total_libre;
    double fragmentacion = (1 - (calidad_porcentaje * calidad_porcentaje)) * 100;

    return fragmentacion;
}

// Función para medir el tiempo de asignación
double medir_tiempo_asignacion(int method, size_t num_allocs) {
    clock_t start, end;
    malloc_control(method); // Configurar el método de asignación

    start = clock();
    for (int i = 0; i < num_allocs; i++) {
        void *ptr = malloc(1024); // Asignar bloques más grandes
        free(ptr); // Liberar inmediatamente
    }
    end = clock();

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void test_fragmentacion_first_fit(void) {
    malloc_control(0); // Usar First Fit
    void *ptrs[NUM_BLOCKS];

    // Asignamos bloques de memoria con tamaños diferentes
    for (int i = 0; i < NUM_BLOCKS; i++) {
        ptrs[i] = malloc((i + 1) * 64); // Asignar bloques de diferentes tamaños
    }

    // Liberamos bloques de manera no secuencial para crear fragmentación
    free(ptrs[1]); // Liberamos bloques pequeños
    free(ptrs[3]);
    free(ptrs[5]);

    // Calcular la fragmentación
    float fragmentacion = calcular_fragmentacion();
    printf("Fragmentación First Fit: %.2f%%\n", fragmentacion);

    // Verificar que haya fragmentación
    TEST_ASSERT(fragmentacion > 0.0); // Verifica que haya fragmentación
}

// Prueba de fragmentación Best Fit
void test_fragmentacion_best_fit(void) {
    malloc_control(1); // Usar Best Fit
    void *ptrs[NUM_BLOCKS];

    // Asignamos bloques de memoria con tamaños diferentes
    for (int i = 0; i < NUM_BLOCKS; i++) {
        ptrs[i] = malloc((i + 1) * 64); // Asignar bloques de diferentes tamaños
    }

    // Liberamos bloques de manera no secuencial para crear fragmentación
    free(ptrs[2]); // Liberamos bloques intermedios
    free(ptrs[4]);
    free(ptrs[6]);

    // Calcular la fragmentación
    float fragmentacion = calcular_fragmentacion();
    printf("Fragmentación Best Fit: %.2f%%\n", fragmentacion);

    // Verificar que haya fragmentación
    TEST_ASSERT(fragmentacion > 0.0); // Verifica que haya fragmentación
}

// Prueba de fragmentación Worst Fit
void test_fragmentacion_worst_fit(void) {
    malloc_control(2); // Usar Worst Fit
    void *ptrs[NUM_BLOCKS];

    // Asignamos bloques de memoria con tamaños diferentes
    for (int i = 0; i < NUM_BLOCKS; i++) {
        ptrs[i] = malloc((i + 1) * 64); // Asignar bloques de diferentes tamaños
    }

    // Liberamos bloques de manera no secuencial para crear fragmentación
    free(ptrs[0]); // Liberamos bloques grandes
    free(ptrs[3]);
    free(ptrs[7]);

    // Calcular la fragmentación
    float fragmentacion = calcular_fragmentacion();
    printf("Fragmentación Worst Fit: %.2f%%\n", fragmentacion);

    // Verificar que haya fragmentación
    TEST_ASSERT(fragmentacion > 0.0); // Verifica que haya fragmentación
}

// Prueba de velocidad First Fit
void test_velocidad_first_fit(void) {
    double tiempo = medir_tiempo_asignacion(0, 10000); // Aumentamos el número de asignaciones
    printf("Tiempo First Fit para 10000 asignaciones: %.4f segundos\n", tiempo);
    TEST_ASSERT(tiempo < 1.0); // Esperamos que no tarde más de 1 segundo
}

// Prueba de velocidad Best Fit
void test_velocidad_best_fit(void) {
    double tiempo = medir_tiempo_asignacion(1, 10000); // Aumentamos el número de asignaciones
    printf("Tiempo Best Fit para 10000 asignaciones: %.4f segundos\n", tiempo);
    TEST_ASSERT(tiempo < 1.0); // Esperamos que no tarde más de 1 segundo
}

// Prueba de velocidad Worst Fit
void test_velocidad_worst_fit(void) {
    double tiempo = medir_tiempo_asignacion(2, 10000); // Aumentamos el número de asignaciones
    printf("Tiempo Worst Fit para 10000 asignaciones: %.4f segundos\n", tiempo);
    TEST_ASSERT(tiempo < 1.0); // Esperamos que no tarde más de 1 segundo
}

// Función principal para ejecutar las pruebas
int main(void) {
    UNITY_BEGIN();
    
    // Ejecutamos las pruebas de fragmentación
    RUN_TEST(test_fragmentacion_first_fit);
    RUN_TEST(test_fragmentacion_best_fit);
    RUN_TEST(test_fragmentacion_worst_fit);

    // Ejecutamos las pruebas de velocidad
    RUN_TEST(test_velocidad_first_fit);
    RUN_TEST(test_velocidad_best_fit);
    RUN_TEST(test_velocidad_worst_fit);
    
    return UNITY_END();
}

