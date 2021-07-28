#include "Wire.h"
const int MPU_ADDR = 0x68; 
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables para acelerometro val
int16_t gyro_x, gyro_y, gyro_z; // variables para gyro data
int16_t temperature; // variables para temperatura data
//inicializacion de pines para el led
int led1 = 5;
int led2 = 6;
int led3 = 7;
int led4 = 8;
int led5 = 9;
int led6 = 10;
int led7 = 11;
int led8 = 12;
int led9 = 13;
//definicion de valores para el delay
#define demora 150
#define demora3 10 
#define demora2 500
#define strobo 100
#define strobo2 40
char tmp_str[7]; // vector temporal usado para conversion en la funcion
char* convert_int16_to_str(int16_t i) { // convierte int16 en cadena. Además, las cadenas resultantes tendrán la misma longitud en el monitor serie.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
//Se llama para inicializar variables, modos de pin, comenzar a usar bibliotecas, etc. La función setup () solo se ejecutará una vez, después de cada encendido o reinicio de la placa Arduino.
void setup() {
  Serial.begin(9600);
  Wire.begin(); //Llama a la libreria para empezar la transmision del modulo esclavo pero no retorna ningun valor
  Wire.beginTransmission(MPU_ADDR); // Inicia la transmision entre el arduino por los pines SDA Y SCL y el modulo(GY-521)
  Wire.write(0x6B); // PWR_MGMT_1 Registra los valores obtenidos por el canal 0x6B
  Wire.write(0); // Asigna a 0 la escritura (Activa el MPU-6050)
  Wire.endTransmission(true);//Finaliza una transmisión a un dispositivo esclavo que comenzó con beginTransmission() y transmite los bytes que se pusieron en cola por write ().
  //INICIALIZAMOS PINES DE SALIDA PARA CAMBIOS DE ESTADO EN LOS LEDS  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);//Empieza el intercambio de informacion por el canal 0x68 del MPU6050
  Wire.write(0x3B); // Comineza con el registro por el canal 0x3B
  Wire.endTransmission(false);//el parámetro indica que el Arduino enviará un reinicio. Como resultado, la conexión se mantiene activa.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // Requiere un total de 7 bits multiplicado por 2 que son 14 registros
  
  
  accelerometer_x = Wire.read()<<8 | Wire.read(); // Lectura de Registros: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  // IMPRIME LA INFROMACION
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));//Se pasan los valores obtenidos al convertidor hexa a decimal y se muestran en el panel serial
  Serial.println();
  //Validamos el valor para encender ya sea la intermitente izquierda, derecha o la luz de posicion
  //En donde si el valor del acelerometro en el eje X esta en un rango de -500 y 9500 se encienda la izquierda
  //O si esta entre un valor de 10600 y 20000 se encienda la derecha 
  //Si el valor no cumple ninguno de estos parametros  se enciende la luz de posicion
  if(accelerometer_x >= -500 && accelerometer_x <= 9500){
    izquierdo();
  }else if(accelerometer_x >= 10600 && accelerometer_x <= 20000){
    derecho();
  }
  carrera();
}

 void carrera(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led9, LOW);
 }
void derecho(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led9, LOW);
  delay(demora);
  digitalWrite(led7, HIGH);
  delay(demora);
  digitalWrite(led8, HIGH);
  digitalWrite(led7, LOW);
  delay(demora);
  digitalWrite(led9, HIGH);
  delay(demora);
}


void izquierdo(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led9, LOW);
  delay(demora);
  digitalWrite(led3, HIGH);
  delay(demora);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  delay(demora);
  digitalWrite(led1, HIGH);
  delay(demora);
}
void intermitentes(){
  digitalWrite(led1, HIGH);
  delay(demora);
  digitalWrite(led2, HIGH);
  digitalWrite(led1, LOW);
  delay(demora);
  digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW);
  delay(demora);
  digitalWrite(led4, HIGH);
  digitalWrite(led3, LOW);
  delay(demora);
  digitalWrite(led5, HIGH);
  digitalWrite(led4, LOW);
  delay(demora);
  digitalWrite(led6, HIGH);
  digitalWrite(led5, LOW);
  delay(demora);
  digitalWrite(led7, HIGH);
  digitalWrite(led6, LOW);
  delay(demora);
  digitalWrite(led8, HIGH);
  digitalWrite(led7, LOW);
  delay(demora);
  digitalWrite(led9, HIGH);
  digitalWrite(led8, LOW);
  delay(demora);
  digitalWrite(led9, LOW);
  delay(demora);
  
}

void ayuda(){
  digitalWrite(led1, HIGH);
  delay(demora3);
  digitalWrite(led2, HIGH);
  digitalWrite(led1, LOW);
  delay(demora3);
  digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW);
  delay(demora3);
  digitalWrite(led4, HIGH);
  digitalWrite(led3, LOW);
  delay(demora3);
  digitalWrite(led5, HIGH);
  digitalWrite(led4, LOW);
  delay(demora3);
  digitalWrite(led6, HIGH);
  digitalWrite(led5, LOW);
  delay(demora3);
  digitalWrite(led7, HIGH);
  digitalWrite(led6, LOW);
  delay(demora3);
  digitalWrite(led8, HIGH);
  digitalWrite(led7, LOW);
  delay(demora3);
  digitalWrite(led9, HIGH);
  digitalWrite(led8, LOW);
  delay(demora3);
  digitalWrite(led9, LOW);
  delay(demora3);
}
