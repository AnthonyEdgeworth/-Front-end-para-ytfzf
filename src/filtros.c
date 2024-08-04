#include "filtros.h"

void filtros(Config *config, const gchar *ruta);

void filtros(Config *config, const gchar *ruta)
{

    short int seleccion_Filtro = 0;

    do
    {

        seleccion_Filtro = 0;

        printf("Menú de filtros\n");
        printf("[1]. Activar busqueda por videos\n");
        printf("[2]. Activar busqueda por listas de videos\n");
        printf("[0]. Salir\n");
        scanf("%hd", &seleccion_Filtro);
        getchar(); // Limpiar el buffer

        char respuesta_seleccion;

        switch (seleccion_Filtro)
        {
        case 1:

            while (respuesta_seleccion != 'S' && respuesta_seleccion != 'N')
            {
                printf("\nActivar busqueda por videos ([N]: No, [S]: Sí): ");
                scanf(" %c", &respuesta_seleccion);
                respuesta_seleccion = toupper(respuesta_seleccion);
                if (respuesta_seleccion != 'S' && respuesta_seleccion != 'N')
                {
                    printf("\nOpción inválida. Ingrese 'S' o 'N'.\n");
                }
            }

            if (respuesta_seleccion == 'N')
            {
                printf("Presione enter para continuar.");
                getchar();
                system("clear");
                seleccion_Filtro = 0;

                break;
            }
            config->cargarVideos = TRUE;
            config->cargarListas = FALSE;
            config->seleccionar_calidad = TRUE;
            guardar_configuracion(ruta, config);

            printf("Presione enter para continuar.");
            getchar();
            system("clear");
            seleccion_Filtro = 0;

            break;

        case 2:

            while (respuesta_seleccion != 'S' && respuesta_seleccion != 'N')
            {
                printf("\nActivar busqueda por listas de videos ([N]: No, [S]: Sí): ");
                scanf(" %c", &respuesta_seleccion);
                respuesta_seleccion = toupper(respuesta_seleccion);
                if (respuesta_seleccion != 'S' && respuesta_seleccion != 'N')
                {
                    printf("\nOpción inválida. Ingrese 'S' o 'N'.\n");
                }
            }

            if (respuesta_seleccion == 'N')
            {
                printf("Presione enter para continuar.");
                getchar();
                system("clear");
                seleccion_Filtro = 0;

                break;
            }
            config->cargarVideos = FALSE;
            config->cargarListas = TRUE;
            config->seleccionar_calidad = FALSE;
            seleccion_Filtro = 0;
            guardar_configuracion(ruta, config);

            break;

        case 0:
            system("clear");
            seleccion_Filtro = 0;

            ejecutar_menu();

            break;

        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
            system("clear");
            return;
        }

    } while (seleccion_Filtro != 0);

    return;
}