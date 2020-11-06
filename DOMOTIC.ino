#include <Servo.h> // libreria para los servo motores
//VARIABLES PROGRAMA GENERAL
int pin0 = 0,pin1 = 1, pin2 = 2, pin3 = 3; // conexión de las fotoresistencias
int valsi,valsd, valii, valid; //valores superiores e inferiores
int supmax, infmax, izqmax, dermax; //variables para inferiores y superiores máximos
int dif1, dif2; //variables para almacenar las diferencias entre el máximo superior e
//VARIABLES BOTÓN ENCENDIDO Y APAGADO
const int reset = 3; // Pin del botón de apagado/encendido
const int led = 13; // Pin del LED de apagado
int estado=0; //Variable que recibirá valores
//VARIABLES AUTOCALIBRACIÓN
int sensor1=0, sensor2=0, sensor3=0, sensor4=0;
int sensormin1=1023, sensormin2=1023, sensormin3=1023, sensormin4=1023;
int sensormax1=0, sensormax2=0, sensormax3=0, sensormax4=0;
Servo horizontal; // Servo horizontal
int servoh = 180; //Variable con valor de 180 definido para el servo horizontal
int servohLimitHigh = 180; //limite en posición derecha máxima
int servohLimitLow = 0; //limite para posición izquierda máxima
Servo vertical; // Servo vertical Servo
int servov = 45; //Variable con valor de 180 definido para el servo horizontal
int servovLimitHigh = 180; //limite en posicion superior
int servovLimitLow = 15; //limite para posicion inferior
void setup()
{
Serial.begin(9600); // Inicializa función para imprimir valores más adelante
horizontal.attach(9); //servo horizontal pin digital 9
vertical.attach(10); // servo vertical pin digital 10
while (millis() < 10000)
{
sensor1=analogRead(pin0);
sensor2=analogRead(pin1);
sensor3=analogRead(pin2);
sensor4=analogRead(pin3);
horizontal.attach(9); //servo horizontal pin digital 9
vertical.attach(10); // servo vertical pin digital 10
// CALIBRACIÓN DURANTE 5 SEGUNDOS
if (sensor1 > sensormax1) // Registrar valor máximo del sensor 1
{
sensormax1 = sensor1;
}
if (sensor1 < sensormin1) // Registrar valor minimo del sensor 1
{
sensormin1 = sensor1;
}

if (sensor2 > sensormax2) // Registrar valor máximo del sensor 2
{
sensormax2 = sensor2;
}
if (sensor2 < sensormin2) // Registrar valor minimo del sensor 2
{
sensormin2 = sensor2;
}
if (sensor3 > sensormax3) // Registrar valor máximo del sensor 3
{
sensormax3 = sensor3;
}
if (sensor3 < sensormin3) // Registrar valor minimo del sensor 3
{
sensormin3 = sensor3;
}
if (sensor4 > sensormax4) // Registrar valor máximo del sensor 4
{
sensormax4 = sensor4;
}
if (sensor4 < sensormin4) // Registrar valor minimo del sensor 4
{
sensormin4 = sensor4;
}
}
}
}
void loop()
{
valsi = analogRead(pin0); // lee el valor del fotorresistor (0-510)(superior izquierdo)
valsd = analogRead(pin1); // lee el valor del fotorresistor (511-1023)(superior derecho)
valii = analogRead(pin2); // lee el valor del fotorresistor (0-510)(inferior izquierdo)
valid = analogRead(pin3); // lee el valor del fotorresistor (511-1023)(inferior derecho)
supmax = (valsi + valsd) / 2; // valor superior maximo
infmax = (valii + valid) / 2; // valor inferior maximo
izqmax = (valsi + valii) / 2; // valor izquierdo máximo
dermax = (valsd + valid) / 2; // valor derecho máximo
dif1 = supmax - infmax; // diferencia entre superior e inferior
dif2 = izqmax - dermax; // diferencia entre izquierdo y derecho
Serial.print(supmax); // Imprime valor de supmax para determinar la tolerancia
Serial.print(" ");
estado=digitalRead(reset); // Lee el valor del botón de apagado
//CONTROL VERTICAL
if (estado==LOW)
{
if (-50 > dif1 || dif1 > 50) // revisa la diferencia para cambiar al ángulo vertical
{
if (supmax > infmax) // revisa la diferencia para cambiar al ángulo vertical
{
servov = ++servov; // Aumenta una unidad cada vez que se cumpla el ciclo
if (servov > servovLimitHigh)
{
servov = servovLimitHigh; // Establece un valor nuevo para servov
}
}
else if (supmax < infmax) // Si no se cumple lo anterior se ejecuta la siguiente sentencia
{
servov= --servov; // Disminuye una unidad cada vez que se cumpla el ciclo
if (servov < servovLimitLow)
{
servov = servovLimitLow; // Establece un valor nuevo para servov
}
}
vertical.write(servov); // Manda la señal al servo para ejecutar el movimiento
}
//CONTROL HORIZONTAL
if (-50 > dif2 || dif2 > 50) // revisa la diferencia para cambiar el ángulo horizontal
{
if (izqmax > dermax) // revisa la diferencia para cambiar el ángulo horizontal
{
servoh = --servoh; // Disminuye una unidad cada vez que se cumpla el ciclo
if (servoh < servohLimitLow)
{
servoh = servohLimitLow; // Establece un valor nuevo para servoh
}
}
else if (izqmax < dermax) // Si no se cumple lo anterior se ejecuta la siguiente sentencia
{
servoh = ++servoh; // Aumenta una unidad cada vez que se cumpla el ciclo
if (servoh > servohLimitHigh)
{
servoh = servohLimitHigh; // Establece un valor nuevo para servoh
}
}
horizontal.write(servoh); // Manda la señal al servo para ejecutar el movimiento
}
delay(50); // Tiempo de reacción del servo
}
Else // Si no se cumple la sentencia del botón de encendido, se ejecuta la siguiente
{
digitalWrite(led, HIGH); // Encender LED
}
}

