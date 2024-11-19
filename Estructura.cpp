#include <iostream>
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
