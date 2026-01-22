# Juego de Sopa de Letras en C

Proyecto desarrollado en **lenguaje C**.

El programa implementa un juego de sopa de letras por consola, utilizando palabras leídas desde archivos de texto y aplicando conceptos fundamentales del lenguaje C.

---

## Tecnologías y conceptos utilizados

- Lenguaje C  
- Manejo de archivos de texto  
- Memoria dinámica (`malloc`, `free`)  
- Matrices  
- Estructuras  
- Punteros  
- Programación estructurada  

---

## Funcionalidades

- Lectura de palabras desde archivos de texto  
- Generación y manejo del tablero de la sopa de letras  
- Búsqueda y validación de palabras ocultando las correctas.  
- Liberación correcta de memoria dinámica  

---

## Ejecución del programa

- El proyecto fue desarrollado utilizando el IDE Code::Blocks. Tienes dos formas de ejecutarlo: 

#### Opción 1: Usando Code::Blocks

- Abrir el archivo Sopa_de_Letras.cbp.  
- Hacer clic en el botón Build and Run.
- El programa cargará automáticamente los archivos Palabras.txt y Pistas.txt incluidos en la carpeta.

#### Opción 2: Mediante terminal (GCC)

- Para compilarlo manualmente se deben incluir todos los archivos fuente:

```bash
gcc main.c Funciones.c -o sopa_de_letras
./sopa_de_letras