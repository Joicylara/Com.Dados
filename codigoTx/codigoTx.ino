#include <VirtualWire.h>

#define TX_PIN 9  // Pino de transmissão
#define RX_PIN 6 // Pino de recepção
#define ENDERECO_RX1 "Receptor1/"  // Endereço do receptor 1
#define ENDERECO_RX2 "Receptor2/"  // Endereço do receptor 2

void setup() {
  Serial.begin(9600);
  vw_set_tx_pin(TX_PIN);
  vw_set_rx_pin(RX_PIN);
  vw_setup(1000); // Configuração da biblioteca VirtualWire
  vw_rx_start();  // Inicia o receptor
  
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //receberMensagens();
  
  // Mensagem para o receptor 1
  const char mensagem_rx1[] = "Ola, mundo!@";
  enviarMensagem(ENDERECO_RX1, mensagem_rx1);

 if(vw_wait_rx_max(20)){
  Serial.println("entrou");

  if (vw_get_message(buf, &buflen)) {
    String mensagemRecebida = String((char*)buf).substring(0, buflen);
    Serial.println(mensagemRecebida);
    int posicaoBarra = mensagemRecebida.indexOf('/');
    int posicao2 = mensagemRecebida.indexOf('@');
    
    if (posicaoBarra != -1) {
      String parte1 = mensagemRecebida.substring(0, posicaoBarra);
      String parte2 = mensagemRecebida.substring(posicaoBarra + 1, posicao2);

      if (parte1 == "Receptor1") {
        Serial.print("Mensagem recebida: ");
        Serial.println(parte2);
        
        char mensagemEnviada[]= "Mensagem recebida com sucesso!";
        // Envie uma confirmação para o "Receptor2"
        enviarMensagem("Receptor2",mensagemEnviada);
      
      }
    } else {
      Serial.println("Caractere '/' não encontrado na mensagem.");
    }
  }
 }
}

void enviarMensagem(const char endereco_destino[], const char mensagem[]) {
  char mensagem_com_endereco[VW_MAX_MESSAGE_LEN];
  strcpy(mensagem_com_endereco, endereco_destino);
  strcat(mensagem_com_endereco, mensagem);

  vw_send((uint8_t*)mensagem_com_endereco, strlen(mensagem_com_endereco));
  vw_wait_tx();

  Serial.print("Mensagem Enviada para ");
  Serial.print(endereco_destino);
  Serial.print(": ");
  Serial.println(mensagem);
}

/*void receberMensagens() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    String mensagemRecebida = String((char*)buf).substring(0, buflen);
    Serial.println(mensagemRecebida);
    int posicaoBarra = mensagemRecebida.indexOf('/');
    int posicao2 = mensagemRecebida.indexOf('@');
    
    if (posicaoBarra != -1) {
      String parte1 = mensagemRecebida.substring(0, posicaoBarra);
      String parte2 = mensagemRecebida.substring(posicaoBarra + 1, posicao2);

      if (parte1 == "Receptor1") {
        Serial.print("Mensagem recebida: ");
        Serial.println(parte2);
        
        char mensagemEnviada[]= "Mensagem recebida com sucesso!";
        // Envie uma confirmação para o "Receptor2"
        enviarMensagem("Receptor2",mensagemEnviada);
      
      }
    } else {
      Serial.println("Caractere '/' não encontrado na mensagem.");
    }
  }
}*/
