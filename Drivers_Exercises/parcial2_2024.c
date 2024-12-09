/* Ejercicio parcial 2 2024
* Por un pin del adc ingresa una tension de rango dinamico -2v a 2v con una frecuencia maxima de 20khz
* obtenidos de un sensor de presion diferencial que mide variaciones de voltaje en funcioin de presion
* a lo largo de una tuberia GNL
* Se pide almacenar la seal cmpliendo nyquist en la posicion de memoria 0x2008e000 y con tamao 1kb
* Una vez ocuapdo el espacio vuelve a almacenar desde el comienzo (buffer circular)
* En funcion del promedio de todas las muestras obtenidas cada 100ms de la señal capturada, se debe tomar
* una decision sobre dos pines de salida GPIO que generan señales cuadradas de 3.3v en fase(Señales s1 y s2 
* usadas para ajustar dos valvulas de control de flujo qu eregula la presion del gas) con una frecuencia de 10kz
*   -Si el promedio se encuentra entre -2 y 0 la señal s1 se adelanta respecto a s2 en un angulo proporcional al valor promedio  (0 a 180)
*   -Si el promedio se encuentra entre 0 y 2 la señal s2 se adelanta respecto a s1 en un angulo proporcional al valor promedio  (0 a 180)
*/