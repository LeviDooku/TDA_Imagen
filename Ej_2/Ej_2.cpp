//Ej_2

/////////////////////////////
//Pedro Velasco Santana,   //
//2D - D2	               //
//Práctica 2, ejercicio 2. //
/////////////////////////////

/////////////////////////////
//         image.h         //
//   Declaración función   //
/////////////////////////////

/**
  * @brief Realiza un zoom x2 a una region de la imagen
  * @param origen Ruta donde se encuentra el archivo desde el que cargar la imagen.
  * @pre file_path debe ser una ruta válida que contenga un fichero . pgm
  * @param destino Ruta donde se va a guardar el archivo de la imagen resultante.
  * @param fila Especificacion de la fila de la esquina superior izquierda de la subimagen que se va a extraer.
  * @param col Especificacion de la columna de la esquina superior izquierda de la subimagen que se va a extraer.
  * @param lado Tamaño del lado del cuadrado.
  * @pre El cuadrado descrito debe estar completamente incluido en la imagen original.
  * @return Devuelve una imagen de tamaño 2*lado-1
  */

Image Zoom2X(char *origen, char *destino, int fila, int col, int lado) const;

///////////////////////////////
//         image.cpp         //
//   Implementación función  //
///////////////////////////////

Image Image::Zoom2X(char *origen, char *destino, int fila, int col, int lado) const {
    Image imagenOrigen;
    Image imagenFinal(2*lado-1, 2*lado-1);
    int iF=0, jF=0;
    if (!imagenOrigen.Load(origen)){
        cerr << "Error: La imagen no puedo leerse" << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return imagenOrigen;
    }

    iF=0, jF=0;
    for (int i=fila; i < fila+lado; i++){
        jF=0;
        for (int j=col; j < col+lado; j++){
            imagenFinal.set_pixel(iF, jF, (byte) imagenOrigen.get_pixel(i, j));
            jF+=2;
        }
        iF+=2;
    }

    iF=0, jF=1;
    for (int i = fila; i < fila+lado; i++){
        jF=1;
        for (int j = col; j < col+lado-1; j++){
            imagenFinal.set_pixel(iF, jF, (byte) roundf((float) (imagenOrigen.get_pixel(i, j)+imagenOrigen.get_pixel(i, j+1)) / 2));
            jF+=2;
        }
        iF+=2;
    }

    iF=1, jF=0;
    for (int i = fila; i < fila+lado-1; i++){
        jF=0;
        for (int j = col; j < col+lado-1; j++){
            if (jF%2==0)
                imagenFinal.set_pixel(iF, jF, (byte) roundf((float) (imagenOrigen.get_pixel(i, j)+imagenOrigen.get_pixel(i+1, j)) / 2));
            jF++;
            if (jF%2!=0) {
                imagenFinal.set_pixel(iF, jF, (byte) roundf(
                        (float) (imagenOrigen.get_pixel(i, j) + imagenOrigen.get_pixel(i+1, j) +
                                 imagenOrigen.get_pixel(i, j+1) + imagenOrigen.get_pixel(i+1, j+1)) / 4));
            }
            jF++;
        }
        imagenFinal.set_pixel(iF, jF, (byte) roundf((float) (imagenOrigen.get_pixel(i, col+lado-1)+imagenOrigen.get_pixel(i+1, col+lado-1)) / 2));
        iF+=2;
    }
    return imagenFinal;
}

/////////////////////////////
//      zoom.cpp           //
//      Función main       //
/////////////////////////////

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <image.h>
#include <math.h>

using namespace std;

int main (int argc, char *argv[]){
    char *origen, *destino;
    int fila, col, lado;
    Image image;

    if (argc != 6){
        cerr << "Error: Numero de parametros incorrecto.\n";
        cerr << "Uso: zoom <FicheroImagenOriginal><FicheroImagenDestino><filaEsquinaSupIzq><columnaEsquinaSupIzq><lado>\n";
        exit(1);
    }

    origen = argv[1];
    destino = argv[2];
    fila = atoi(argv[3]),
    col = atoi(argv[4]),
    lado = atoi(argv[5]);

    if (!image.Load(origen)){
        cerr << "Error: La imagen no puedo leerse" << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    Image new_imagen;
    cout << origen << " " << destino << " " << fila << " " << col << " " << lado << " " << endl;
    new_imagen = new_imagen.Zoom2X(origen, destino, fila, col, lado);

    if (new_imagen.Save(destino))
        cout << "Se ha guardado la imagen en " << destino << endl;
    else{
        cerr << "Error: La imagen no pudo guardarse." << endl;
        cerr << "terminando la ejecucion del programa." << endl;
        return 1;
    }
}









