/*
 * Prueba de Conmutación Lenta para Medio Puente (1x IR2101 / IR2110)
 * Controla solo 2 MOSFETs (Una sola rama/fase)
 * 
 * Conexiones físicas hacia el IR2101:
 * - Pin 9 (Arduino) -> Entrada HIN (Pin 2) -> Controla MOSFET High-Side (LED Alta)
 * - Pin 5 (Arduino) -> Entrada LIN (Pin 3) -> Controla MOSFET Low-Side  (LED Baja)
 */

const int deadtime_us = 5; // Tiempo muerto de seguridad (5 microsegundos)

void setup() {
  // 1. Estados bajos iniciales por seguridad
  digitalWrite(9, LOW);
  digitalWrite(5, LOW);
  
  // 2. Configuración de pines de salida
  pinMode(9, OUTPUT); // HIN
  pinMode(5, OUTPUT); // LIN

}

void loop() {
  // --- FASE 1: Enciende MOSFET Superior (High-Side) ---
  digitalWrite(5, LOW);            // Apaga MOSFET Inferior
  delayMicroseconds(deadtime_us);  // Tiempo muerto de protección
  digitalWrite(9, HIGH);           // Enciende MOSFET Superior
  delay(1000);                     // 1 SEGUNDO (LED Alta ENCENDIDO | LED Baja APAGADO)

  // --- FASE DE SEGURIDAD ---
  digitalWrite(9, LOW);            // Apaga MOSFET Superior
  delayMicroseconds(deadtime_us);  // Tiempo muerto de protección

  // --- FASE 2: Enciende MOSFET Inferior (Low-Side) ---
  digitalWrite(5, HIGH);           // Enciende MOSFET Inferior
  delay(1000);                     // 1 SEGUNDO (LED Alta APAGADO | LED Baja ENCENDIDO)
}