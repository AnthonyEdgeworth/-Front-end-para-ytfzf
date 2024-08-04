cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y versión
project(CLIYoutube VERSION 1.0)

# Estándares de C y C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Definición de los directorios de inclusión
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    /usr/include/libxml2
    /usr/include/gtk-3.0
    /usr/include/at-spi2-atk/2.0
    /usr/include/at-spi-2.0
    /usr/include/dbus-1.0
    /usr/lib/x86_64-linux-gnu/dbus-1.0/include
    /usr/include/gio-unix-2.0
    /usr/include/cairo
    /usr/include/libdrm
    /usr/include/pango-1.0
    /usr/include/harfbuzz
    /usr/include/fribidi
    /usr/include/atk-1.0
    /usr/include/pixman-1
    /usr/include/freetype2
    /usr/include/libpng16
    /usr/include/gdk-pixbuf-2.0
    /usr/include/libmount
    /usr/include/blkid
    /usr/include/uuid
    /usr/include/glib-2.0
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
)

# Definición de los directorios de enlace de bibliotecas
link_directories(
    /usr/lib/x86_64-linux-gnu
)

# Archivos fuente
set(SOURCES
    src/cargarParametros.c
    src/configuracion.c
    src/main.c
    src/menu.c
    src/menuconfiguracion.c
    src/suscripciones.c
    src/manual_User.c
    src/filtros.c
)

# Ejecutable
add_executable(CLIYoutube ${SOURCES})

# Establece el directorio de salida para el ejecutable
set_target_properties(CLIYoutube PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Enlace de bibliotecas
target_link_libraries(CLIYoutube
    pthread
    gtk-3
    gdk-3
    pangocairo-1.0
    pango-1.0
    atk-1.0
    cairo-gobject
    cairo
    gdk_pixbuf-2.0
    gio-2.0
    gobject-2.0
    glib-2.0
    curl
    xml2
)

# Flags adicionales para GCC
target_compile_options(CLIYoutube PRIVATE
    -Wall
    -O3
    -fdiagnostics-color=always
    -g
)
