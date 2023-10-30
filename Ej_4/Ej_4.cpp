//Ej_4

/////////////////////////////
//Pedro Velasco Santana,   //
//2D - D2	               //
//Práctica 2, ejercicio 4. //
/////////////////////////////

/////////////////////////////
//         image.h         //
//   Declaración función   //
/////////////////////////////

/**
  * @brief Modifica el contraste de una imagen.
  * @param in1 Umbral inferior de la imagen de entrada.
  * @param in2 Umbral superior de la imagen de entrada.
  * @param out1 Umbral inferior de la imagen de salida.
  * @param out2 Umbral superior de la imagen de salida.
  * @pre 0 <= ( in1, in2, out1, out2 ) <= 255
  * @pre in1 < in2
  * @pre out1 < out2
  * @post El objeto que llama a la funcion es modificado
  */

void AdjustContrast (byte in1, byte in2, byte out1, byte out2);

///////////////////////////////
//         image.cpp         //
//   Implementación función  //
///////////////////////////////

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2){
    byte valor;
    float min, max, a, b;
    for (int i=0; i<this->size(); i++) {
        valor = this->get_pixel(i);
        if (valor < in1) {
            min = 0;
            max = (float) out1;
            a = 0;
            b = (float) in1;
        } else if (valor > in2) {
            min = (float) out2;
            max = 255;
            a = (float) in2;
            b = 255;
        } else {
            min = (float) out1;
            max = (float) out2;
            a = (float) in1;
            b = (float) in2;
        }
        byte nValor = (byte) roundf((min + ((max - min) / (b - a) * ((float) valor - a))));
        this->set_pixel(i, nValor);
    }
}

/////////////////////////////
//      contraste.cpp      //
//      Función main       //
/////////////////////////////

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "<image.h>"

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino;
    byte in_1, in_2, out_1, out_2; // nombres de los ficheros
    Image image;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: contraste <img entrada> <img salida> <Umbral inf entrada> <Umbral sup entrada> <Umbral inf salida> <Umbral sup salida>\n";
        exit (1);
    }

    // Obtener argumentos
    origen = argv[1];
    destino = argv[2];
    in_1  = atoi(argv[3]);
    in_2 = atoi(argv[4]);
    out_1  = atoi(argv[5]);
    out_2 = atoi(argv[6]);


    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: La imagen no puedo leerse" << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de la imagen" << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // Contraste
    Image new_image;
    image.AdjustContrast(in_1, in_2, out_1, out_2);

    if (image.Save(destino))
        cout << "Se ha guardado la imagen en " << destino << endl;
    else{
        cerr << "Erro: La imagen no pudo guardarse." << endl;
        cerr << "terminando la ejecucion del programa." << endl;
        return 1;
    }
    return 0;
}