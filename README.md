# Practica_POO

DESCRIPCIÓN
Aplicación de consola (C++) para gestionar Biblioteca Universitaria con: altas/bajas/edición de materiales, gestión de préstamos y devoluciones, búsquedas/ordenaciones, sanciones por retraso y un módulo de estadísticas. Modelado OO, jerarquía polimórfica, modularidad, STL, y gestión manual de memoria con punteros.


Variantes utilizadas
A1: sanciones de 0,10 € por día (máx. 15 €).
B1: tercer tipo de material: Ebook con licencia y fecha de expiración.
C3: bloqueo automático si la sanción acumulada supera 10 €.
D1: persistencia mediante CSV con comillas escapadas.
E1: búsqueda por autor y ordenación por título.
F3: exportación de préstamos activos a CSV.


COMPILACIÓN
El proyecto ha sido desarrollado y compilado con Microsoft Visual Studio utilizando el estándar C++17.
Visual Studio gestiona automáticamente el proceso de compilación y generación del ejecutable.


USO (Biblioteca)
El programa muestra un menú para:
Añadir Items; Añadir usuarios; Listar items; Registrar préstamos; Registrar Devoluciones; Guardar Datos; Buscar por Autor y listado ordenado por titulo; Exportar estadísticas de préstamos activos a CSV; Eliminar item; Editar item; Bloquear usuario; Desbloquear usuario 


FORMATO CSV
Los datos se guardan con coma como separador.
Los campos con comas o comillas se encierran entre " " y las comillas internas se duplican.

Ejemplos:
Book,"Titulo","Autor",,,
1,"Usuario",0,2.5
1,0,2025-01-02,2025-01-15,2025-01-20

Marcos Jimenez
