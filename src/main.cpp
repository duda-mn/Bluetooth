// //-------------------- BLUETOOTH SLAVE ------------------------
// #include <Arduino.h>
// #include <BluetoothSerial.h>

// BluetoothSerial BT;
// //  14:33:5C:51:F7:3A
// void setup() {
//   Serial.begin(115200);
//   Serial.setTimeout(5000);

//   if (BT.begin("BtSlaveDu")){
//     Serial.println("Bluetooth iniciado com sucesso");
//     Serial.print("Endereco Bluetooth: ");
//     Serial.println(BT.getBtAddressString());
//   }else{
//     Serial.println("Erro ao iniciar Bluetooth");
//   }

// }

// void loop(){
//   if (BT.available()==true) //verifica se tem info no bt e mostra na serial
//   {
//     String msgRecebida = BT.readStringUntil('\n');
//     msgRecebida.trim();
//     Serial.printf("Mensagem recebida: %s", msgRecebida);
//   }

//   if (Serial.available())
//   {
//     String msgEnviar = Serial.readStringUntil('\n');
//     msgEnviar.trim();
//     BT.println(msgEnviar);
//   }

// }

// //-------------------- BLUETOOTH MASTER ------------------------
// #include <Arduino.h>
// #include <BluetoothSerial.h>

// #define Led 4

// BluetoothSerial BT;
// //  14:33:5C:51:F7:3A

// uint8_t endSlave[] = {0xf4,0x65,0x0b,0x55,0x4f,0x26};

// unsigned long tempoAnt = 0;
// unsigned long intervalo = 250;

// bool estadoL = false;
// bool piscando = false;

// void setup() {
//   Serial.begin(115200);
//   Serial.setTimeout(5000);

//   pinMode(Led, OUTPUT);

//   if (BT.begin("BtMasterDu", true)){
//     Serial.println("Bluetooth iniciado com sucesso");
//   }else{
//     Serial.println("Erro ao iniciar Bluetooth");
//   }

//   if (BT.connect(endSlave))
//   {
//     Serial.println("Conectado com sucesso");
//   }else{
//     Serial.println("Erro ao conectar");
//   }

// }

// void loop(){
//   unsigned long tempoAtual = millis();
//   if (BT.available()==true) //verifica se tem info no bt e mostra na serial
//   {
//     String msgRecebida = BT.readStringUntil('\n');
//     msgRecebida.trim();
//     Serial.printf("Mensagem recebida: %s", msgRecebida);

//     if (msgRecebida=="pisca")
//     {
//       piscando= true;
//     }
//     if (msgRecebida =="apaga"){
//       piscando= false;
//     }
//   }

//   if (piscando==true){
//     if (tempoAtual - tempoAnt >= intervalo){
//       if (estadoL==false){
//         estadoL= true;
//       }
//       else{
//         estadoL= false;
//       }
//       digitalWrite(Led, estadoL);

//       tempoAnt=tempoAtual;
//     }
//   }

//   else{
//     digitalWrite(Led, LOW);
//   }

//   if (Serial.available())//envia para o bt
//   {
//     String msgEnviar = Serial.readStringUntil('\n');
//     msgEnviar.trim();
//     BT.println(msgEnviar);
//   }

// }

// //-------------------- BLUETOOTH MASTER CORRETO ------------------------
// //
// #include <Arduino.h>
// #include <BluetoothSerial.h>

// #define Led 4

// BluetoothSerial BT;
// //  14:33:5C:51:F7:3A

// uint8_t endSlave[] = {0xf4,0x65,0x0b,0x55,0x4f,0x26};

// unsigned long tempoAnt = 0;
// unsigned long intervalo = 250;

// bool estadoL = false;
// bool piscando = false;

// void setup() {
//   Serial.begin(115200);
//   Serial.setTimeout(5000);

//   pinMode(Led, OUTPUT);

//   if (BT.begin("BtMasterDu", true)){
//     Serial.println("Bluetooth iniciado com sucesso");
//   }else{
//     Serial.println("Erro ao iniciar Bluetooth");
//   }

//   if (BT.connect(endSlave))
//   {
//     Serial.println("Conectado com sucesso");
//   }else{
//     Serial.println("Erro ao conectar");
//   }

// }

// void loop(){

//   if (BT.available()) //verifica se tem info no bt e mostra na serial
//   {
//     String msgRecebida = BT.readStringUntil('\n');
//     msgRecebida.trim();
//     Serial.printf("Mensagem recebida: %s", msgRecebida);

//     if (msgRecebida=="acende"){
//       piscando=false;
//       estadoL=true;
//     }
//     else if (msgRecebida =="apaga"){
//       piscando=false;
//       estadoL=false;
//     }
//     else if (msgRecebida=="pisca"){
//       piscando=true;
//     }
//     else{
//       Serial.println("Mensagem invalida");
//     }

//   }

//   if (piscando==true){
//     unsigned long tempoAtual = millis();

//     if (tempoAtual-tempoAnt>=intervalo){
//       estadoL=!estadoL;
//       tempoAnt=tempoAtual;
//     }
//   }

//   digitalWrite(Led,estadoL);

//   if (Serial.available())//envia para o bt
//   {
//     String msgEnviar = Serial.readStringUntil('\n');
//     msgEnviar.trim();
//     BT.println(msgEnviar);
//   }

// }

//-------------------- BLUETOOTH MASTER CORRETO ------------------------
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>

BluetoothSerial BT;
Bounce btn = Bounce();

#define botao 23
#define Led 2

//  14:33:5C:51:F7:3A

uint8_t endSlave[] = {0xF4, 0x65, 0x0B, 0x55, 0x4F, 0x26};

unsigned long tempoAntPisca = 0;
unsigned long intervalo = 3000;
unsigned long tempoPressionou = 0;

bool estadoL = false;
bool piscando = false;
bool pressionado = false;
bool estadoRemoto = false;

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(5000);

  pinMode(Led, OUTPUT);
  // pinMode(botao, INPUT_PULLUP);
  btn.attach(botao, INPUT_PULLUP);

  if (BT.begin("BtMasterDu", true))
  {
    Serial.println("Bluetooth iniciado com sucesso");
  }
  else
  {
    Serial.println("Erro ao iniciar Bluetooth");
  }

  if (BT.connect(endSlave))
  {
    Serial.println("Conectado com sucesso");
  }
  else
  {
    Serial.println("Erro ao conectar");
  }
}

void loop()
{
  btn.update();

  unsigned long agora = millis();
  if (BT.available()) // verifica se tem info no bt e mostra na serial
  {
    String msgRecebida = BT.readStringUntil('\n');
    msgRecebida.trim();
    Serial.printf("Mensagem recebida: %s", msgRecebida);
    Serial.println();
    
    if (msgRecebida == "L")
    {
      piscando = false;
      estadoL = true;
    }
    else if (msgRecebida == "D")
    {
      piscando = false;
      estadoL = false;
    }
    else if (msgRecebida == "P")
    {
      piscando = true;
    }
    else
    {
      Serial.println("Mensagem invalida");
    }
  }

  if (piscando){
    if (agora - tempoAntPisca >= intervalo){
    estadoL = !estadoL;
    tempoAntPisca = agora;
  }
}

  digitalWrite(Led, estadoL);

  // ENVIAR BLUETOOTH -----------------


  if (btn.fell())
  {
    tempoPressionou = agora;
    pressionado = !pressionado;
    BT.println(pressionado ? "L" : "D");
  }

  if (btn.read() == LOW && agora - tempoPressionou >= 3000)
  {
    BT.println("P");
    Serial.println("Enviado: P");
    // pressionado = true;
    tempoPressionou = agora;
  }
}