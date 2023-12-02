#include <VirtualWire.h>

#define RX_PIN 8  // Pino de recepção
#define TX_PIN 7  // Pino de transmissão

#define LED_PIN 13 // Pino do LED indicador para RX1

void setup() {
  Serial.begin(9600);
  vw_set_rx_pin(RX_PIN);
  vw_set_tx_pin(RX_PIN);
  vw_setup(1000); // Configuração da biblioteca VirtualWire
  vw_rx_start(); // Inicia a recepção
}

void loop() {

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    String mensagemRecebida = String((char*)buf).substring(0, buflen);

    int posicaoBarra = mensagemRecebida.indexOf('/');
    int posicao2 = mensagemRecebida.indexOf('@');
    
    if (posicaoBarra != -1) {
      String parte1 = mensagemRecebida.substring(0, posicaoBarra);
      String parte2 = mensagemRecebida.substring(posicaoBarra + 1, posicao2);
  Serial.print(mensagemRecebida);
      if (parte1 == "Receptor1") {
        Serial.print("Mensagem recebida: ");
        Serial.println(parte2);
        
        char mensagemEnviada[]= "Mensagem recebida com sucesso!";
        //Envie uma confirmação para o "Receptor2"
        enviarMensagem("Receptor2",mensagemEnviada);
        //Serial.println(mensagemEnviada);
      
      }
    } else {
      Serial.println("Caractere '/' não encontrado na mensagem.");
    }
  }
}

void enviarMensagem(const char endereco_destino[], const char mensagem[]) {
  char mensagem_com_endereco[VW_MAX_MESSAGE_LEN];
  strcpy(mensagem_com_endereco, endereco_destino);
  strcat(mensagem_com_endereco, mensagem);

  vw_send((uint8_t*)mensagem_com_endereco, strlen(mensagem_com_endereco));

  vw_wait_tx();
}
