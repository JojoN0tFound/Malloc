# malloc
42 malloc project
This project is about implementing a dynamic memory allocation mechanism.


# Functions

*malloc*
--
``
void  *malloc(size_t size);
``
La fonction malloc() alloue "size" octets de mémoire et retourne un pointeur sur la mémoire allouée.
En cas d’erreur, malloc() retourne un pointeur NULL.

*realloc*
--
``
void  *realloc(void *ptr, size_t size);
``
La fonction realloc() essaye de modifier la taille de l’alloction pointée par "ptr" à "size" octets, et retourne "ptr". Si il n’y a pas assez de place à l’emplacement mémoire pointé par "ptr", realloc() crée une nouvelle allocation, y copie autant de données de l’ancienne allocation que possible dans la limite de la taille de la nouvelle allocation, libère l’ancienne allocation et retourne un pointeur sur cette nouvelle allocation.
En cas d’erreur, realloc() retourne un pointeur NULL.

*free*
--
``
void  free(void *ptr);
``
La fonction free() libère l’allocation de la mémoire pointée par "ptr". Si "ptr" vaut NULL, free() ne fait rien.

*calloc*
--
``
void  *calloc(size_t elementCount, size_t elementSize);
``
La fonction calloc() alloue "elementCount" de taille "elementSize" octets en initialisant tous les octets a 0.
En cas d’erreur, calloc() retourne un pointeur NULL.

# Run

*set up*
--
Vous pouvez soit exporter les variables:
- Pour linux
```
export LD_LIBRARY_PATH="."
export LD_PRELOAD=`pwd`/libft_malloc.so
```
- Pour Macos
```
export DYLD_LIBRARY_PATH="."
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
```
Soit lancer le script run.sh avec l'exec voulu en parametre.
``./run.sh <exec>``
