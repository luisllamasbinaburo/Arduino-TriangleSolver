# Librería Arduino LibName
La librería TrianguleSolver implementa los cálculos necesarios para resolver cualquier tipo de triángulo de forma sencilla en un procesador como Arduino.

Está pensada para ayudar en la resolución de cinemática de robots y otros tipos de mecanismos articulados en los que, en muchos casos, es necesario resolver los ángulos o longitudes repetidamente.

Más información https://www.luisllamas.es/libreria-arduino-triangulesolver/

## Instrucciones de uso

La clase TriangleSolver contiene las variables que definen el triángulo que queremos resolver. Estas variables son tres longitudes de lado, (A, B, C) y los tres ángulos opuestos a cada lado (Alpha, Beta y Gamma) medidos en radianes.

Para resolver el triángulo es necesario asignar tres cualesquiera de variables del triángulo. A continuación, el resto se calculan mediante el método Solve. Las variables calculadas son las que tengan un valor de 0.0.

En la mayoría de los casos, tres variables permiten determinar el triángulo. No obstante hay dos casos especiales. En el caso de proporcionar los tres ángulos, el sistema admite infinitas soluciones, por lo que no puede resolverse.

Otro caso especial es el caso de proporcionar un ángulo, el lado opuesto y un lado adyacente. En este caso, el sistema admite dos soluciones, una forzando que todos los ángulos sean agudos, y otra permitiendo un ángulo mayor de 90º. Para elegir entre ambos casos la función 'Solve' admite un parámetro opcional 'IsObtuse'.

Para que la librería sea lo más ligera posible, el cálculo no realiza comprobación ni checkeo de errores. Será el programa que llame el que tenga que encargarse de que los parámetros sean correctos y, en su caso, de que la solución es válida.

Adicionalmente la librería proporciona las funciones UpdateN (siendo N las distintas variables del triángulo). Estas funciones simplemente asignan el valor proporcionado como parámetro a la función correspondiente, y ponen a cero el ángulo (o lado) opuesto, y los dos ángulos adyacentes. El propósito de estas funciones es permitir realizar cálculos de mecanismos rápidamente.

### Constructor
La clase TriangleSolver se instancia a través de su construtor, que no tiene ningún parámetro.
```c++
TriangleSolver triang;
```

### Uso de LibName
```c++
//Realiza el cálculo de las varibles que faltan en el triangulo
bool Solve(bool preferObtuse = false);

//Variables del triángulo
float& A = sides[0];
float& B = sides[1];
float& C = sides[2];
float& Alpha = angles[0];
float& Beta = angles[1];
float& Gamma = angles[2];

//Actualizar variables del triángulo
void UpdateA(float a) const
void UpdateB(float b) const
void UpdateC(float c) const
void UpdateAlpha(float alpha)
void UpdateBeta(float beta)
void UpdateGamma(float gamma)
```

## Ejemplos
La librería TriangleSolver incluye los siguientes ejemplos para ilustrar su uso.

* TriangleSolver: Ejemplo que muestra el uso de algunas de las funciones de conversión.
```c++
TriangleSolver triang;

void debug()
{
	Serial.println(triang.A, 4);
	Serial.println(triang.B, 4);
	Serial.println(triang.C, 4);
	Serial.println(degrees(triang.Alpha), 4);
	Serial.println(degrees(triang.Beta)), 4;
	Serial.println(degrees(triang.Gamma), 4);
}

void setup() {
	Serial.begin(115200);
	
	triang.A = 50; 
	triang.C = 25.39;
	triang.Gamma = radians(30);
	triang.Solve(true);
	debug();

}

void loop() 
{
	// do nothing
	delay(1000);
}
```
