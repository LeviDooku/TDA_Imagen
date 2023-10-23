//Ej_3

/////////////////////////////
//Pedro Velasco Santana,   //
//2D - D2                  //
//Práctica 2, ejercicio 3. //
/////////////////////////////

/////////////////////////////
//         image.h         //
//   Declaración función   //
/////////////////////////////

/**
  * @brief Genera un icono como reducción de una imagen
  * @param factor Factor de reducción de la imagen original con respecto al icono
  * @pre factor > 0
  * @return La imagen iconizada
  * @post
  *   - La imagen no se modifica
  *   - La imagen resultante tendrá tamaño int(filas/factor) X int(columnas/factor). Descartando los decimales de la división
  */
    
Image Subsample(int factor) const;

///////////////////////////////
//         image.cpp         //
//   Implementación función  //
///////////////////////////////

Image Image::Subsample(int factor) const{

    if(factor <= 0){
        cerr << "Error: el parámetro debe ser > 0." << endl;
    }

        int cols = this->get_cols();
        int rows = this->get_rows();

        int rCols = cols/factor;
        int rRows = rows/factor;

        Image subsample(rRows, rCols);

        for(int i = 0; i < rRows; i++){
            for(int j = 0; j < rCols; j++){
                int sumBloque = 0;

                for(int x = i * factor; x < (i + 1) * factor; x++){
                    for(int y = j * factor; y < (j + 1) * factor; y++)
                        sumBloque += this->get_pixel(x, y);
                }

            int media = sumBloque/(factor * factor);
            subsample.set_pixel(i, j, media);

            }

        }
    return subsample;
}

/////////////////////////////
//      icono.cpp          //
//      Función main       //
/////////////////////////////

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){
 
  char *origen, *destino; // nombres de los ficheros
  Image imagen, icono;

  // Comprobar validez de la llamada
  if (argc != 4){
    cerr << "Error: Numero incorrecto de parametros.\n";
    cerr << "Uso: subimagen <fich_orig> <fich_rdo> <factor>\n";
    exit (1);
  }

  // Obtener argumentos
  origen  = argv[1];
  destino = argv[2];
  int factor = atoi(argv[3]);

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

  icono = imagen.Subsample(factor);

  // Guardar la imagen resultado en el fichero
  if (icono.Save(destino))
    cout  << "La imagen se guardo en " << destino << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  return 0;
}