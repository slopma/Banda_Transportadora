#define start 26   
#define stop 27   
#define derecha 28  
#define izquierda 29 
#define s1 30       
#define s2 31       
#define s3 32       
#define s4 33       

bool running = false;  

void setup() {
  pinMode(start, INPUT);
  pinMode(stop, INPUT);
  pinMode(derecha, OUTPUT);
  pinMode(izquierda, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);

  digitalWrite(derecha, LOW);
  digitalWrite(izquierda, LOW);
}

void loop() {
  // Comenzar proceso al presionar START
  if (digitalRead(start) == HIGH && !running) {
    running = true;
    iniciarProceso();
  }
  
  // Detener proceso al presionar STOP
  if (digitalRead(stop) == HIGH && running) {
    detenerProceso();
    running = false;
  }
}

void iniciarProceso() {
  // Mover a la derecha hasta que llegue al sensor S1
  moverDerecha();
  while (digitalRead(s1) == LOW) {
    if (digitalRead(stop) == HIGH) {
      detenerProceso();
      return;
    }
  }
  detenerMotor();
  
  // Esperar 3 segundos
  delay(3000);

  // Mover a la izquierda hasta el sensor S4
  moverIzquierda();
  while (digitalRead(s4) == LOW) {
    if (digitalRead(stop) == HIGH) {
      detenerProceso();
      return;
    }
  }
  detenerMotor();
  
  // Transportar entre S4 y S2 tres veces
  for (int i = 0; i < 3; i++) {
    moverDerecha();
    while (digitalRead(s2) == LOW) {
      if (digitalRead(stop) == HIGH) {
        detenerProceso();
        return;
      }
    }
    detenerMotor();
    
    moverIzquierda();
    while (digitalRead(s4) == LOW) {
      if (digitalRead(stop) == HIGH) {
        detenerProceso();
        return;
      }
    }
    detenerMotor();
  }
  
  // Mover a la derecha hasta el sensor S3
  moverDerecha();
  while (digitalRead(s3) == LOW) {
    if (digitalRead(stop) == HIGH) {
      detenerProceso();
      return;
    }
  }
  detenerMotor();
  
  // Detener el proceso
  detenerProceso();
  running = false;
}

void moverDerecha() {
  digitalWrite(derecha, HIGH);
  digitalWrite(izquierda, LOW);
}

void moverIzquierda() {
  digitalWrite(derecha, LOW);
  digitalWrite(izquierda, HIGH);
}

void detenerMotor() {
  digitalWrite(derecha, LOW);
  digitalWrite(izquierda, LOW);
}

void detenerProceso() {
  detenerMotor();
  running = false;
}

