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


