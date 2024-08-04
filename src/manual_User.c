#include <stdio.h>
#include "manual_User.h"

void mostrar_menu_manual();
void descargar_archivo_csv();
void cargar_archivo_csv();
void eliminar_datos_programa();
void opcion_filtros();

void mostrar_menu_manual()
{
    int opcion;
    do
    {
        system("clear");
        printf("--------------------------------------------------------------\n");
        printf("Selecciona una opción:\n");
        printf("1. Descargar el archivo canales.csv\n");
        printf("2. Cargar el archivo canales.csv al programa\n");
        printf("3. Eliminar los datos del programa\n");
        printf("4. Opción de filtros\n");
        printf("5. Salir\n");
        printf("--------------------------------------------------------------\n");
        printf("Introduce el número de la opción: ");
        scanf("%d", &opcion);
        getchar(); // Para capturar el salto de línea después de ingresar la opción

        system("clear");

        switch (opcion)
        {
        case 1:
            descargar_archivo_csv();
            break;
        case 2:
            cargar_archivo_csv();
            break;
        case 3:
            eliminar_datos_programa();
            break;
        case 4:
            opcion_filtros();
            break;
        case 5:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción no válida. Inténtalo de nuevo.\n");
        }

        if (opcion != 5)
        {
            printf("Presiona Enter para continuar.");
            getchar();
            system("clear");
        }

    } while (opcion != 5);
}

void descargar_archivo_csv()
{
    printf("--------------------------------------------------------------\n");
    printf("Para descargar el archivo canales.csv, sigue estos pasos:\n");
    printf("\n");
    printf("Desde YouTube:\n");
    printf("1. Inicia sesión en tu cuenta de YouTube.\n");
    printf("2. Haz clic en tu foto de perfil en la esquina superior derecha de la página web.\n");
    printf("3. Selecciona 'Tus datos en YouTube' en el menú desplegable.\n");
    printf("4. Haz clic en 'Más' en la tarjeta 'Tu panel de YouTube'.\n");
    printf("5. Selecciona 'Descargar datos de YouTube'.\n");
    printf("6. En 'Crear una nueva exportación', asegúrate de que 'YouTube y YouTube Music' esté seleccionado.\n");
    printf("7. Haz clic en 'Todos los datos de YouTube incluidos' y deselecciona todo excepto 'Suscripciones'.\n");
    printf("8. Haz clic en 'Siguiente paso'.\n");
    printf("9. Elige tu método preferido de entrega (Correo electrónico, Dropbox, etc.) y haz clic en 'Crear exportación'.\n");
    printf("   (Las instrucciones a partir de aquí asumen que seleccionaste correo electrónico).\n");
    printf("10. Revisa tu correo electrónico y descarga el archivo .zip proporcionado.\n");
    printf("11. Extrae el archivo .zip.\n");
    printf("12. El archivo que necesitas estará en Takeout/YouTube and YouTube Music/subscriptions/subscriptions.csv.\n");
    printf("\n");
    printf("Puedes descargar el archivo de suscripciones desde este enlace: https://takeout.google.com/settings/takeout/custom/youtube\n");
    printf("\n");
    printf("Referencia: Importación de suscripciones. (2024). Documentación de FreeTube. Recuperado el 3 de agosto de 2024, de https://docs.freetubeapp.io/usage/importing-subscriptions/\n");
    printf("--------------------------------------------------------------\n");
}

void cargar_archivo_csv()
{
    printf("--------------------------------------------------------------\n");
    printf("Para cargar el archivo canales.csv al programa:\n");
    printf("\n");
    printf("1. Copia el archivo subscriptions.csv a la ubicación donde se encuentra nuestro programa.\n");
    printf("2. Renombra el archivo a canales.csv.\n");
    printf("3. Ejecuta nuestro programa desde la terminal.\n");
    printf("4. Selecciona la opción 'Configuración' en el menú principal.\n");
    printf("5. Selecciona la opción 'Cargar canales.csv'.\n");
    printf("6. Introduce la ruta completa del archivo canales.csv cuando se te pida.\n");
    printf("   Ejemplo: \"/home/user/Documentos/canales.csv\".\n");
    printf("\n");
    printf("El programa cargará automáticamente el archivo canales.csv y procesará las suscripciones.\n");
    printf("Asegurate de que el archivo canales.csv tenga el siguiente formato:\n");
    printf("ID del canal,URL del canal,Título del canal ← Importante que tenga está cabecera (Puedes modificar el archivo canales.csv para que lo tenga)\n");
    printf("UC-8G0u7EDBSdiOrAi5eKXFA,http://www.youtube.com/channel/UC-8G0u7EDBSdiOrAi5eKXFA,Aru-Chan la boluda\n");
    printf("UC-B06UJxJ20HYv15lzrm9mA,http://www.youtube.com/channel/UC-B06UJxJ20HYv15lzrm9mA,dillongoo\n");
    printf("↑ Ejemplo de como debería estar tu archivo canales.csv");
    printf("--------------------------------------------------------------\n");

}

void eliminar_datos_programa()
{
    printf("--------------------------------------------------------------\n");
    printf("Para eliminar los datos del programa, sigue estos pasos:\n");
    printf("\n");
    printf("1. Abre una terminal.\n");
    printf("2. Ejecuta los siguientes comandos para eliminar las carpetas de configuración:\n");
    printf("   rm -r /home/user/.config/cli-youtube/\n");
    printf("   rm -r /home/user/.config/ytfzf/\n");
    printf("Nota: Asegúrate de reemplazar 'user' por tu nombre de usuario en tu computadora.\n");
    printf("\n");
    printf("Esto eliminará todos los datos del programa.\n");
    printf("--------------------------------------------------------------\n");

}

void opcion_filtros()
{
    printf("--------------------------------------------------------------\n");
    printf("Para la opción de filtros:\n");
    printf("Si eliges buscar por listas de reproducción (previamente seleccionada en filtros),\n");
    printf("se desactivará automáticamente la opción de seleccionar la calidad del video antes de reproducirlo.\n");
    printf("El comando ytfzf no acepta estos dos parámetros en conjunto.\n");
    printf("Para volver a tener la opción de seleccionar calidad antes de reproducir el video,\n");
    printf("vuelve a Configuración, Cambiar configuraciones, filtros y activa la búsqueda por videos.\n");
    printf("--------------------------------------------------------------\n");


}
