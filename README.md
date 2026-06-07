# Laboratorio 1 Estructura de Datos II
**Ingeniero:** Ivan de Jesus Deras Tabora
-- **Estudiante:** Cesar Daniel Garcia Barahona / 22441107

Desarrollamos una aplicacion en C++ que gestiona registros de alumnos con campos de longitud variable, utilizando un índice primario simple cargado completamente en memoria.

## Como hacer la Compilacion

```cmd
mkdir build
cd build
cmake ..
cmake --build .
```

## Comandos de ejecucion

### Agregar un alumno
```cmd
.\build\Debug\lab1.exe agregar alumno1.json
```

### Buscar un alumno
```cmd
.\build\Debug\lab1.exe buscar <no_cuenta>
```

### Eliminar un alumno
```cmd
.\build\Debug\lab1.exe eliminar <no_cuenta>
```

### Actualizar un alumno
```cmd
.\build\Debug\lab1.exe actualizar alumno1.json
```

## Archivos JSON que se usaron

### alumno1.json
```json
{
    "no_cuenta": "22441101",
    "nombre": "Carlos Mejia",
    "telefono": "99991234",
    "edad": 22,
    "fecha": "20200115"
}
```

### alumno2.json
```json
{
    "no_cuenta": "22441102",
    "nombre": "Luis Fernando Aguilar",
    "telefono": "77773456",
    "edad": 20,
    "fecha": "20210820"
}
```

### alumno3.json
```json
{
    "no_cuenta": "22441103",
    "nombre": "Juan Miguel Soza",
    "telefono": "77773456",
    "edad": 19,
    "fecha": "20210820"
}
```

## Estrategia de Eliminacion

Se implementó el **Hard Delete (Eliminación Física)**.
Esta estrategia fue elegida por ser la más simple de implementar,
ya que no requiere manejar estados activos o inactivos en el índice,
reduciendo la complejidad del código.
Al eliminar un registro, este desaparece físicamente del archivo `alumnos.dat` y su entrada se elimina del índice primario en memoria,
garantizando que el archivo siempre refleje exactamente los registros activos. 
Esto también elimina la necesidad de un comando `clean-up`, ya que no quedan registros pendientes de eliminar,
y asegura que el índice en memoria nunca tenga entradas inactivas, lo que resulta en búsquedas más directas y eficientes.
