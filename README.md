# MazeSolver
MazeSolver es un robot MicroMouse desarrollado por Artil Robotics. Firmware para micromouse de laberinto 16x16cm estándar de competencia internacional All Japan classic Micromouse Contest

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

Por ejemplo en la siguiente imagen de muestra el conjunto de una entrada.
