# Practica_POO
Aplicación de consola para gestionar Biblioteca Universitaria con: altas/bajas/edición de materiales, gestión de préstamos y devoluciones, búsquedas/ordenaciones, sanciones por retraso y un módulo de estadísticas. Modelado OO, jerarquía polimórfica, modularidad, STL, y gestión manual de memoria con punteros.


Descripción
Aplicación de consola en C++ que gestiona una biblioteca universitaria.
Permite añadir materiales, registrar préstamos y devoluciones, gestionar usuarios, calcular sanciones, realizar búsquedas, y guardar/cargar datos mediante ficheros CSV.

Variantes utilizadas
A1: sanciones de 0,10 € por día (máx. 15 €).
B1: tercer tipo de material: Ebook con licencia y fecha de expiración.
C3: bloqueo automático si la sanción acumulada supera 10 €.
D1: persistencia mediante CSV con comillas escapadas.
E1: búsqueda por autor y ordenación por título.
F3: exportación de préstamos activos a CSV.

Compilación
g++ -std=c++17 src/*.cpp -o biblioteca

Ejecución
./biblioteca
o
biblioteca.exe

Uso general
El programa muestra un menú para:

Añadir items y usuarios

Registrar préstamos y devoluciones

Guardar y cargar datos

Buscar por autor

Exportar préstamos activos

Editar o eliminar items

Bloquear o desbloquear usuarios

Formato CSV
Los datos se guardan con coma como separador.
Los campos con comas o comillas se encierran entre " " y las comillas internas se duplican.

Ejemplos:
Book,"Titulo","Autor",,,
1,"Usuario",0,2.5
1,0,2025-01-02,2025-01-15,2025-01-20

Autores
(Completar con los nombres y aportaciones del equipo)
