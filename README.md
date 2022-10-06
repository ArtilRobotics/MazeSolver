# MazeSolver
MazeSolver es un robot MicroMouse desarrollado por Artil Robotics. Firmware para micromouse de laberinto 16x16cm estándar de competencia internacional All Japan classic Micromouse Contest

![MazeSolver](https://github.com/ArtilRobotics/MazeSolver/blob/main/image/MazeSolver.png)

## Programación
Dentro de este apartado se desarrolló 2 tipos de programación
- Fuzzy
- Lógica

### Programación Fuzzy
Esta programación se basa en el desarrollo de reglas dependiendo de las variables de entradas y salida.
Las variables de entrada fueron:
- Sensor Infrarrojo Frontal Derecho 
- Sensor Infrarrojo Frontal Izquierdo
- Sensor Infrarrojo Lateral Derecho 
- Sensor Infrarrojo Lateral Izquierdo

Sus variables de salida:
- Velocidad del Motor Derecho
- Velocidad del Motor Izquierdo

Con la ayuda del software MATLAB y su herramienta Fuzzy Logic Desginer se desarrolló el controlador de la siguiente imagen:

![Pantalla Principal](https://github.com/ArtilRobotics/MazeSolver/blob/main/image/Pantalla%20Principal%20Fuzzy%20Logic%20Designer.png)

En esta imagen se puede observar las entradas al lado izquierda y al lado derecho las salidas. Cada uno de los recuadros represetan un conjunto. Dentro de estos conjuntos se encuentran los rangos de trabajo de las distintas variables.

Por ejemplo en la siguiente imagen de muestra el conjunto de entrada del Sensor Lateral Derecho. Dentro del cual se determina los subconjuntos, y el rango de trabajo, teniendo en cuenta que el rango de trabajo total del sensor es de 0 a 1023. Uno de los problemas que se presentó en esta parte fue que los sensores al ser logarítmicos, su incremento no era lineal por lo cual los los subconjuntos tienen rangos diferentes.

![Sensor Lateral Derecho](https://github.com/ArtilRobotics/MazeSolver/blob/main/image/Conjunto%20Sensor%20Lateral%20Derecho.png)

Este mismo proceso se realizó para los otros 3 sensores. Esto se puede revisar detalladamente en la carpeta [Matlab](https://github.com/ArtilRobotics/MazeSolver/tree/main/Matlab/Intento%2029) dentro del repositorio.

Para los conjuntos de salida, los 2 tendrás únicamente 2 subcojutos (Rápido y lento), ya que es innecesario añadir una velocidad media, eso solo causaría una mayor carga de procesos a la tarjeta.

![Velocidad Motor Derecho](https://github.com/ArtilRobotics/MazeSolver/blob/main/image/Velocidad%20Motor%20Derecho.png)

**Formulación de Reglas**

Primero se debe tener en cuenta que entre más subconjuntos se tengan, más reglas serán necesarias. La forma de funcionamiento de este robot está básado en la regla de la mano derecha, dentro de ellas, se encuentran reglas como:
- Si el sensor lateral derecho detecta un espacio libre independiente de que exista o no un espacio al frente, girará hacia la derecha
- Si el sensor lateral derecha y el izquierdo no detecta un espacio libre, y los sensores frontales tampoco detectan un espacio, el robot girará 180°

Todas estas reglas fueron ingresadas dentro de la herramienta de Matlab, como se indica en la siguiente imagen

![Reglas](https://github.com/ArtilRobotics/MazeSolver/blob/main/image/Reglas.png)

Como resultado de todas estas reglas, se obtiene una gráfica de control, con la que se puede analizar el comportamiento del robot dependiendo de la variación en las entradas.

![Grafica](https://github.com/ArtilRobotics/MazeSolver/blob/main/image/Gráfica%20Resultante%20Reglas.png)
