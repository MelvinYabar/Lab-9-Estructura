# Reproductor de Música - Proyecto C++
Este proyecto implementa un sistema para gestionar una lista de reproducción a partir de un archivo CSV con información de canciones. Utiliza un árbol binario de búsqueda (BST) para almacenar las canciones en orden ascendente según su popularidad.

# Descripción
  El sistema permite leer un archivo CSV que contiene datos de canciones (como artista, título, popularidad, etc.) y almacenar estas canciones en un árbol binario de búsqueda. Se proporciona una interfaz de línea de comandos que permite al usuario:

  Ver todas las canciones disponibles en el archivo CSV.
  Ver las canciones almacenadas en la lista de reproducción ordenadas por popularidad.
  Cargar las canciones desde el archivo CSV y agregar las canciones a la lista de reproducción.
  Salir del programa.
  Estructuras de Datos
  Estructura Cancion
  Representa los datos de una canción, que incluyen información como:

artist_name: Nombre del artista.
track_name: Nombre de la canción.
track_id: Identificador único de la canción.
popularity: Popularidad de la canción.
year: Año de lanzamiento.
genre: Género de la canción.
danceability, energy, key, loudness, mode, speechiness, acousticness, instrumentalness, liveness, valence, tempo: Atributos de la canción medidos en distintas escalas.
duration_ms: Duración de la canción en milisegundos.
time_signature: Firma de tiempo de la canción.
Estructura NodoArbol
Representa un nodo en el árbol binario de búsqueda (BST), donde cada nodo contiene una canción y tiene punteros a sus nodos hijo izquierdo y derecho.

# Clase ArbolBinario
Implementa el árbol binario de búsqueda que permite:

# Insertar canciones en el árbol.
Mostrar las canciones en orden ascendente por popularidad utilizando un recorrido in-order.
Clase ListaReproduccion
Gestiona la lista de reproducción, cargando las canciones desde el archivo CSV y mostrándolas en la interfaz de usuario.

leerTodasLasCanciones(): Lee las canciones desde el archivo CSV.
mostrarTodasLasCanciones(): Muestra todas las canciones en el archivo CSV.
mostrarCanciones(): Muestra las canciones almacenadas en el árbol binario de búsqueda (ordenadas por popularidad).
Funcionamiento
El archivo spotify_data.csv debe estar en el mismo directorio que el programa y debe tener el siguiente formato:

diff
Copiar código
index,artist_name,track_name,track_id,popularity,year,genre,danceability,energy,key,loudness,mode,speechiness,acousticness,instrumentalness,liveness,valence,tempo,duration_ms,time_signature
Cuando el programa se ejecuta, muestra un menú con las siguientes opciones:

Opción 1: Mostrar todas las canciones del archivo CSV.
Opción 2: Mostrar la lista de reproducción (canciones ordenadas por popularidad).
Opción 3: Cargar canciones desde el archivo CSV a la lista de reproducción.
Opción 4: Salir del programa.
Ejemplo de salida
yaml
Copiar código
=== MENÚ PRINCIPAL ===
1. Mostrar todas las canciones del archivo
2. Mostrar lista de reproducción
3. Cargar canciones desde el archivo spotify_data.csv
4. Salir
Elija una opción: 1

=== TODAS LAS CANCIONES EN EL ARCHIVO ===
Artista: Artist 1, Título: Song A, Popularidad: 85, Año: 2020, Duración: 210000 ms
Artista: Artist 2, Título: Song B, Popularidad: 90, Año: 2021, Duración: 220000 ms
...

# Codigo 
```  #include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> // Para std::sort
using namespace std;

// Estructura para representar una canción
struct Cancion {
    string artist_name;
    string track_name;
    string track_id;
    int popularity;
    int year;
    string genre;
    float danceability;
    float energy;
    int key;
    float loudness;
    int mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int duration_ms;
    int time_signature;
};

// Nodo del Árbol Binario
struct NodoArbol {
    Cancion cancion;
    NodoArbol* izquierda;
    NodoArbol* derecha;

    NodoArbol(const Cancion& c)
        : cancion(c), izquierda(nullptr), derecha(nullptr) {}
};

// Clase del Árbol Binario de Búsqueda
class ArbolBinario {
private:
    NodoArbol* raiz;

    // Función auxiliar para insertar un nodo
    NodoArbol* insertarNodo(NodoArbol* nodo, const Cancion& cancion) {
        if (nodo == nullptr) {
            return new NodoArbol(cancion);
        }

        if (cancion.popularity < nodo->cancion.popularity) {
            nodo->izquierda = insertarNodo(nodo->izquierda, cancion);
        } else {
            nodo->derecha = insertarNodo(nodo->derecha, cancion);
        }

        return nodo;
    }

    // Recorrido in-order para mostrar canciones
    void mostrarInOrden(NodoArbol* nodo) const {
        if (nodo == nullptr) return;

        mostrarInOrden(nodo->izquierda);
        cout << "Artista: " << nodo->cancion.artist_name
             << ", Título: " << nodo->cancion.track_name
             << ", Popularidad: " << nodo->cancion.popularity
             << ", Año: " << nodo->cancion.year
             << ", Duración: " << nodo->cancion.duration_ms << " ms\n";
        mostrarInOrden(nodo->derecha);
    }

public:
    ArbolBinario() : raiz(nullptr) {}

    // Inserta una canción en el árbol
    void insertar(const Cancion& cancion) {
        raiz = insertarNodo(raiz, cancion);
    }

    // Muestra las canciones en orden ascendente por popularidad
    void mostrarCanciones() const {
        if (raiz == nullptr) {
            cout << "La lista de reproducción está vacía.\n";
        } else {
            mostrarInOrden(raiz);
        }
    }
};

// Clase para gestionar la lista de reproducción y lectura desde CSV
class ListaReproduccion {
private:
    ArbolBinario arbol;

public:
    // Lee canciones desde el archivo CSV
    vector<Cancion> leerTodasLasCanciones() const {
        ifstream file("spotify_data.csv");
        vector<Cancion> canciones;

        if (!file.is_open()) {
            cerr << "Error al abrir el archivo spotify_data.csv.\n";
            return canciones;
        }

        string linea;
        getline(file, linea); // Leer y descartar la cabecera

        while (getline(file, linea)) {
            stringstream ss(linea);
            string token;
            Cancion cancion;

            getline(ss, token, ','); // índice (ignorar)
            getline(ss, cancion.artist_name, ',');
            getline(ss, cancion.track_name, ',');
            getline(ss, cancion.track_id, ',');
            ss >> cancion.popularity; ss.ignore();
            ss >> cancion.year; ss.ignore();
            getline(ss, cancion.genre, ',');
            ss >> cancion.danceability; ss.ignore();
            ss >> cancion.energy; ss.ignore();
            ss >> cancion.key; ss.ignore();
            ss >> cancion.loudness; ss.ignore();
            ss >> cancion.mode; ss.ignore();
            ss >> cancion.speechiness; ss.ignore();
            ss >> cancion.acousticness; ss.ignore();
            ss >> cancion.instrumentalness; ss.ignore();
            ss >> cancion.liveness; ss.ignore();
            ss >> cancion.valence; ss.ignore();
            ss >> cancion.tempo; ss.ignore();
            ss >> cancion.duration_ms; ss.ignore();
            ss >> cancion.time_signature;

            canciones.push_back(cancion);
        }

        file.close();
        return canciones;
    }

    // Muestra todas las canciones del archivo CSV ordenadas por popularidad
    void mostrarTodasLasCanciones() const {
        vector<Cancion> canciones = leerTodasLasCanciones();

        if (canciones.empty()) {
            cout << "No se encontraron canciones en el archivo CSV.\n";
            return;
        }

        // Ordenar las canciones por popularidad en orden descendente
        sort(canciones.begin(), canciones.end(), [](const Cancion& a, const Cancion& b) {
            return a.popularity > b.popularity; // De mayor a menor popularidad
        });

        cout << "\n=== TODAS LAS CANCIONES EN EL ARCHIVO ===\n";
        for (const auto& cancion : canciones) {
            cout << "Artista: " << cancion.artist_name
                 << ", Título: " << cancion.track_name
                 << ", Track ID: " << cancion.track_id
                 << ", Popularidad: " << cancion.popularity
                 << ", Año: " << cancion.year
                 << ", Género: " << cancion.genre
                 << ", Duración: " << cancion.duration_ms << " ms\n";
        }
    }

    // Mostrar las canciones añadidas a la lista de reproducción
    void mostrarCanciones() const {
        arbol.mostrarCanciones();
    }

    // Mensaje de confirmación de carga
    void cargarCanciones() const {
        cout << "Todas las canciones se cargaron correctamente.\n";
    }
};

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n=== MENÚ PRINCIPAL ===\n";
    cout << "1. Mostrar todas las canciones del archivo\n";
    cout << "2. Mostrar lista de reproducción\n";
    cout << "3. Cargar canciones desde el archivo spotify_data.csv\n";
    cout << "4. Salir\n";
    cout << "Elija una opción: ";
}

// Función principal
int main() {
    ListaReproduccion lista;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
        case 1:
            lista.mostrarTodasLasCanciones();
            break;
        case 2:
            cout << "\nLista de reproducción:\n";
            lista.mostrarCanciones();
            break;
        case 3:
            lista.cargarCanciones(); // Solo muestra el mensaje de confirmación.
            break;
        case 4:
            cout << "Saliendo del programa. ¡Hasta luego!\n";
            break;
        default:
            cout << "Opción inválida. Por favor, intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}
```
# Informe de Actualización: Parte 2 - Final de Estructura
  Fecha: 26 de noviembre de 2024
  Autor: Carlos Cano

## Introducción
  En esta fase del proyecto, se ha mejorado la estructura del programa para gestionar una lista de reproducción de canciones en formato CSV. Se implementaron diversas funcionalidades clave, incluyendo la gestión de canciones (agregar y eliminar) y la persistencia de datos (guardado y carga de la lista de reproducción desde un archivo). A continuación se describen los cambios y las mejoras realizadas.

  1. Uso de unordered_map para acceso rápido
Una de las principales optimizaciones realizadas fue la introducción de un unordered_map llamado canciones_map. Este mapa permite acceder a las canciones de manera eficiente utilizando el track_id como clave. A diferencia de una lista, que requiere recorrer todos sus elementos para encontrar uno específico, el unordered_map permite acceder a cualquier canción directamente mediante su track_id en tiempo constante, mejorando así el rendimiento del programa al gestionar grandes cantidades de canciones.

Código:

unordered_map<string, Cancion> canciones_map;
2. Gestión de la Lista de Reproducción
a) Agregar Canciones a la Colección
Se implementó la función agregarAColeccion, que permite agregar canciones a la lista de reproducción utilizando su track_id. La función busca el track_id en el unordered_map y, si lo encuentra, agrega la canción a la lista de reproducción canciones_agregadas.

Código:

void agregarAColeccion(const string& track_id) {
    auto it = canciones_map.find(track_id);
    if (it != canciones_map.end()) {
        canciones_agregadas.push_back(it->second);
        cout << "Canción agregada a la lista de reproducción.\n";
        guardarListaReproduccionEnArchivo();  // Actualizar archivo
    } else {
        cout << "Track ID no encontrado.\n";
    }
}

# b) Eliminar Canciones de la Colección
La nueva funcionalidad de eliminación de canciones se implementó mediante la función eliminarDeColeccion, que permite eliminar canciones de la lista de reproducción por su track_id. Se realiza una búsqueda en la lista de canciones agregadas y, si se encuentra la canción, se elimina de la lista.

Código:

  void eliminarDeColeccion(const string& track_id) {
    auto it = find_if(canciones_agregadas.begin(), canciones_agregadas.end(),
                       [&track_id](const Cancion& cancion) { return cancion.track_id == track_id; });

    if (it != canciones_agregadas.end()) {
        canciones_agregadas.erase(it);
        cout << "Canción eliminada de la lista de reproducción.\n";
        guardarListaReproduccionEnArchivo();  // Actualizar archivo
    } else {
        cout << "No se encontró la canción con el Track ID: " << track_id << "\n";
    }
}
# 3. Persistencia de Datos
Se implementó la función guardarListaReproduccionEnArchivo, que guarda las canciones de la lista de reproducción en un archivo de texto llamado repo.txt. Esta funcionalidad asegura que la lista de reproducción se conserve incluso después de cerrar el programa. El archivo se sobrescribe cada vez que se realiza una modificación en la lista de canciones (agregar o eliminar canciones).

Código:

void guardarListaReproduccionEnArchivo() const {
    ofstream file("repo.txt", ios::trunc);  // Abrir el archivo en modo truncado para sobrescribirlo
    if (!file.is_open()) {
        cerr << "Error al guardar el archivo repo.txt.\n";
        return;
    }

    // Escribir las canciones en el archivo
    for (const auto& cancion : canciones_agregadas) {
        file << cancion.artist_name << "," << cancion.track_name << "," << cancion.track_id << ","
             << cancion.popularity << "," << cancion.year << "," << cancion.genre << ","
             << cancion.danceability << "," << cancion.energy << "," << cancion.key << ","
             << cancion.loudness << "," << cancion.mode << "," << cancion.speechiness << ","
             << cancion.acousticness << "," << cancion.instrumentalness << "," << cancion.liveness << ","
             << cancion.valence << "," << cancion.tempo << "," << cancion.duration_ms << ","
             << cancion.time_signature << "\n";
    }

    file.close();

Por otro lado, también se implementó la función cargarListaDeReproduccionDesdeArchivo, que permite cargar la lista de reproducción previamente guardada en repo.txt. Esto es útil para restaurar el estado de la lista de canciones al reiniciar el programa.

# 4. Interfaz de Usuario Mejorada
Se agregaron nuevas opciones en el menú interactivo del programa. Ahora el usuario puede elegir entre varias opciones, como cargar canciones desde un archivo, agregar o eliminar canciones de la lista de reproducción, mostrar la lista de reproducción actual, y guardar los cambios en un archivo.

Menú actualizado:

void mostrarMenu() {
    cout << "\n1. Cargar canciones desde archivo\n";
    cout << "2. Agregar canción a la lista de reproducción\n";
    cout << "3. Eliminar canción de la lista de reproducción\n";
    cout << "4. Mostrar lista de reproducción\n";
    cout << "5. Guardar lista de reproducción en archivo\n";
    cout << "6. Cargar lista de reproducción desde archivo\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opción: ";
}
  El usuario puede seleccionar las opciones con un número del 1 al 7, lo que permite una navegación intuitiva y fácil para gestionar las canciones.

# 5. Flujo del Programa
El flujo del programa sigue una estructura interactiva donde el usuario elige una opción del menú. Dependiendo de la opción seleccionada, el programa ejecutará una de las funciones previamente descritas, como cargar canciones, agregar o eliminar canciones de la lista, mostrar la lista de reproducción actual o guardar los cambios en un archivo.

El ciclo continuará hasta que el usuario seleccione la opción de salir del programa.

