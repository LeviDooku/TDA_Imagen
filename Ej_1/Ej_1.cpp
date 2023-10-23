//Ej_1

/////////////////////////////
//Pedro Velasco Santana,   //
//2D - D2				           //
//Práctica 2, ejercicio 1. //
/////////////////////////////

/////////////////////////////
//		   image.h 		       //
//	 Declaración función   //
/////////////////////////////

/**
* @brief Genera una subimagen.
* @param row Fila inicial para recortar 
* @param ncol Columna inicial para recortar
* @param height Número de filas
* @param width Número de columnas
* @return Imagen con el recorte. 
* @post El objeto que llama a la función no se modifica.
**/
    
Image Crop(int nrow, int ncol, int height, int width) const;

///////////////////////////////
//		   image.cpp 	         //
//	 Implementación función  //
///////////////////////////////

Image Image::Crop(int nrow, int ncol, int height, int width) const{

    Image crop_image(height, width); //Crea un objeto Image que contendrá la imagen cropeada

    //Se recorre la nueva imagen en sus parámetros "height" y "width"
    //Con el método "get_pixel()" se obtienen los piexeles a setear en la foto cropeada

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            crop_image.set_pixel(i, j, get_pixel(nrow + i, ncol + j));
        }
    }

    return crop_image;
}

/////////////////////////////
//	    subimagen.cpp      //
//	    Función main       //
/////////////////////////////

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){
 
  char *origen, *destino; // nombres de los ficheros
  Image imagen, subimagen;

  // Comprobar validez de la llamada
  if (argc != 7){
    cerr << "Error: Numero incorrecto de parametros.\n";
    cerr << "Uso: subimagen <FichImagenOriginal> <FichImagenDestino> <fila> <col> <filas_sub> <cols_sub>\n";
    exit (1);
  }

  // Obtener argumentos
  origen  = argv[1];
  destino = argv[2];
  int fila = atoi(argv[3]);
  int col = atoi(argv[4]);
  int filas_sub = atoi(argv[5]);
  int cols_sub = atoi(argv[6]);

  // Mostramos argumentos
  cout << endl;
  cout << "Fichero origen: " << origen << endl;
  cout << "Fichero resultado: " << destino << endl;

  // Leer la imagen del fichero de entrada
  if (!imagen.Load(origen)){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  // Mostrar los parametros de la Imagen
  cout << endl;
  cout << "Dimensiones de " << origen << ":" << endl;
  cout << "   Imagen   = " << imagen.get_rows()  << " filas x " << imagen.get_cols() << " columnas " << endl;

  subimagen = imagen.Crop(fila, col, filas_sub, cols_sub);

  // Guardar la imagen resultado en el fichero
  if (subimagen.Save(destino))
    cout  << "La imagen se guardo en " << destino << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  return 0;
}