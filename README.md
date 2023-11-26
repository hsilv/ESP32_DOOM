# ESP32_DOOM
Este proyecto consiste en la implementación de un Ray Caster en un modelo de hardware distinto a una computadora, en este caso se optó por un ESP32. Si bien la emulación es básica, el rendimiento es razonable.

🎮[Enlace a vídeo](https://youtu.be/Rxajo1vz0Eo)

## Características
* Movimiento de jugador con hardware, en este caso un joystick análogo.
* Soporte para colores en paredes (en este caso, no fue posible aplicar texturas debido a limitaciones de hardware, más específico, de memoria RAM).
* Soporte para mapas relativamente grandes y variables en tamaño
* Choque en paredes.
* Mensaje de inicio
* Juego fluído hasta 32 fps
