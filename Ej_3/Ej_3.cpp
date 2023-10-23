//Ej_3

/////////////////////////////
//Pedro Velasco Santana,   //
//2D - D2				   //
//Práctica 2, ejercicio 3. //
/////////////////////////////

/////////////////////////////
//		   image.h 		   //
//	 Declaración función   //
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