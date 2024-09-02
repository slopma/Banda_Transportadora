# Banda_Transportadora
Electrónica Digital - Taller 2  

- Code:
  
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
  if (digitalRead(start) == HIGH && !running) {
    running = true;
    iniciarProceso();
  }
  
  if (digitalRead(stop) == HIGH && running) {
    detenerProceso();
    running = false;
  }
}

void iniciarProceso() {
  moverDerecha();
  while (digitalRead(s1) == LOW) {
    if (digitalRead(stop) == HIGH) {
      detenerProceso();
      return;
    }
  }
  detenerMotor();
  
  delay(3000);

  moverIzquierda();
  while (digitalRead(s4) == LOW) {
    if (digitalRead(stop) == HIGH) {
      detenerProceso();
      return;
    }
  }
  detenerMotor();

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


  moverDerecha();
  while (digitalRead(s3) == LOW) {
    if (digitalRead(stop) == HIGH) {
      detenerProceso();
      return;
    }
  }
  detenerMotor();
  
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
