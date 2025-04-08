/* Programa para comunicação do ESP32 com a plataforma WEGNOLOGY via protocolo MQTT
   neste projeto estão sendo empregados um display LCD 16x2 com comunicação na rede I2C
   que emvia mensagens de status da comunicação com wi-fi, com a plataforma MQTT e indica
   os valores de temperatura e humidade em tempo real.
   Além de enviar dados para o display, dados também são enviados na porta serial (BoudRate=115200),
   para permitir a visualização mais completa dos dados enviados e recebidos da plataforma 
   em serviços de manutenção e testes.
   Além de permitir o envio de dados, o programa permite o recebimento de informações da plataforma
   com a possibilidade deefetuar controle do equipamento monitorado e de periféricos de forma remota 
   e/ou autônoma.
*/

#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include<LiquidCrystal_I2C.h>
#include <Wire.h>

// Registra o nome da rede wifi que será usada e sua respectiva senha em variáveis
const char* ssid = "<Escrever nome da rede wi-fi>";
const char* password = "<Senha da rede>";

// Registra endereço do MQTT Broker que será utilizado na variável
char* mqtt_server = "broker.app.wnology.io";

//**************************celula 3 gravado no esp32***********************************************************************************************
const char* deviceID="<Escrever Id-Device>";
const char* accesskey="<Escrever accessKey>";
const char* secretkey="<Escrever secretKey>";
const char* state_topic="wnology/<Escreder Id-Device>/state"; //Registra configuração para envio de informações na variável
const char* command_topic="wnology/<Escrever Id-Device>/command";//Registra configuração para recebimento de dados na variável
//**********************************************************************************************************************************
const char* comando;// Armazena dados advindos da plataforma Wnology para o ESP32

#define AnalogPin 34 //Pino que recebe os dados analógicos 12 bits (0 a 5V  / 0 a 4096)
#define LigaMotor 33 //Pino para simular testar acionamento remoto

//Saídas para demonstrar status por indicação luminosa
#define saida1 25 // LED indica câmara Ligada
#define saida2 26 // LED indica câmara Desligada
#define saida3 27 //Define LED indica FALHA

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// Definição da saída conectada ao sensor DHT
#define DHTPIN 13 

// Define o tipo de sensor DHT usado
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)   

// Inicializa sensor DHT 
DHT dht(DHTPIN, DHTTYPE);

// Variáveis que armazenam estado do sensor
float temp,hum,oldtemp;//Variáveis para armazenam o valor da humidade como um número float
int intHum, old_intHum;//Variáveis para armazenam o valor da humidade como um número inteiro

//Variável para monitorar o estado da Câmara de resfriamento
int EstadoCamara = 0;

char json[170]; //Variável para compor e armazenar os dados que serão transmitidos

DynamicJsonDocument doc(1024);

LiquidCrystal_I2C lcd(0x27,16,2); //Função para determinar o endereço do display na rede I2C, o número de dígitos e o número de linhas

void setup() //SETUP ESP32
{
  lcd.begin(16,2); //configura dígitos do display LCD e o Número de linhas
  lcd.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight(); // Serve para ligar a luz do display
  lcd.clear(); // Serve para limpar a tela do display

  Serial.begin(115200); //Configura uma comunicação serial com boudRate de 115200 bps
 
  setup_wifi();
  client.setServer(mqtt_server, 1883); //Determina a porta de comunicação MQTT
  client.setCallback(callback);

  //Configura pinos de saída de dados
  pinMode(saida1, OUTPUT);
  pinMode(saida2, OUTPUT);
  pinMode(saida3, OUTPUT);
  pinMode(LigaMotor, OUTPUT);
  digitalWrite(saida2,HIGH);
  // Configurar o pino ADC como entrada (opcional)
  pinMode(AnalogPin, INPUT);

  dht.begin();//Inicializa sensor DHT
}

void setup_wifi() //Configura acesso ao Wi-Fi local
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");
  
  Serial.println(ssid);
  lcd.setCursor(2, 1);
  lcd.print( ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(0, 7);
    lcd.print(".");

  }

  Serial.println("");
  Serial.println("WiFi connected");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi conectado");
  delay(1000);
  Serial.print("IP address: ");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(WiFi.localIP());
  
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  lcd.setCursor(0, 1);
  lcd.print(WiFi.macAddress());
  delay(1000);
}

void callback(char* topic, byte* message, unsigned int length) {  //Função quwe possibilita receber dados da wegnology no formato json, e atribuir o esperado à variáveis do programa
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp; //Varíável para compor e armazenar os dados recebidos da plataforma Wnology
 
  for (int i = 0; i < length; i++) //Armazena de forma sequencial os dados recebidos
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];//Compõe a mensagem recebida da plataforma caracter por caracter e armazena na variável messageTemp
  }
  Serial.println("Conteúdo: ");
  Serial.println(messageTemp); //Envia para o monitor serial os dados recebidos


  deserializeJson(doc,messageTemp); //divide os dados recebidos por endereços
  
  //Os dados recebidos e divididos serão associados à variáveis e/ou ponteitos no programa
  comando=doc["name"]; 
  Motor=doc["payload"]["liga"];
  //Motor=doc["payload"];
  Serial.print("Comando recebido:");
  Serial.println(comando);
  Serial.print("Pacote recebido:");
  //Serial.println(setMotor);
  Serial.println(Motor);

  //----------------------------------------------------INICIO: LOGICA DE ACIONAMENTO REMOTO ---------------------------------------------------------------------------------------
  if (String(topic) == command_topic) //verifica se dados foram enviado da plataforma
  {
    Serial.print("Changing output to ");
    /* Como acomunicação é bi-direcional este espaço está reservado para tratar dados
    recebidos da platafpoma dentro dentro do programa de forma a grarantir expansão dasfunções*/
      // EstadoCamara = 1;// Varíável de envio de dados de estado para a plataforma IoT
     
  }
      //-----------------------------------Fim da Logica de Acionamento Remoto ----------------------------------------------------------------------------------------------
}

void reconnect() //Busca reconectar com a plataforma em caso de interrupção da comunicação
{
  
    if (!client.connect(deviceID,accesskey,secretkey)) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CONECTANDO MQTT ...");
      
    if (client.connect(deviceID,accesskey,secretkey)) 
    {
      Serial.println("connected");
      // Subscribe
      lcd.clear();
      lcd.setCursor(2, 1);
      lcd.print("CONECTADO");
      client.subscribe(command_topic);
    } 
    
    else 
    {
      Serial.print("failed, rc=");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CONECÇÃO FALHOU");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("NOVA TENTATIVA...");
      lcd.setCursor(1, 1);
      lcd.print("EM 3 SEGUNDOS...");
      // Wait 3 seconds before retrying
      delay(3000);
    }
  }
}
void loop() 
{
  if (!client.connected()) 
  {
    reconnect();
    
  }
  client.loop();
  client.subscribe(command_topic);

  //-------------------------------------------------------LOGICA DE ACIONAMENTO LOCAL------------------------------------------------------------------------------------------
  
  /* while(digitalRead(botaoLigado)==HIGH) //Efetua a leitura do botão Liga 
  { 
    //Espaço para uma eventual lógica de acionamento    
  }

           
  while(digitalRead(botaoDesliga) == HIGH)//Verifica se o botão desliga foi pressionado
  {
    //Espaço para eventual lógica de desligamento
  } 
  */
  //---------------------------------------Fim da Logica de Acionamento Local--------------------------------------------------------------------------------------------------
  
  //-----------------Gera atrazo para a próxima transmissão para não transmitir dados desnecessários--------------------------------
  long now = millis();
  if (now - lastMsg > 30000) {
    lastMsg = now;
   //---------------------------------------------------------------------------------------------------------------------------------

   client.loop(); // Mantém a conexão ativa e permite receber mensagens

    // Efetua a leitura da humidade relativa e armazena na variável hum
    hum = dht.readHumidity();
    // Efetua a leitura da temperatura e armazena na variável temp
    temp = dht.readTemperature();
    //O padrão de leitura de temperatura é em graus celsius
    // Para efetura a leitura em Fahrenheit: dht.readTemperature(true)

    intHum = (int) hum;//Operador de conversão cast, para converter de floast para inteiro

    //Atualiza o valor da temperatura e da humidade no display, apenas se houver mudança em algum deles
    //A lógica empregada evita a atualização do display sem que haja mudança na leitura do sensor
    if((temp != oldtemp) or (intHum != old_intHum))
    {
      lcd.clear();//Limpa os dados do display
      
      if(isnan(temp) || isnan(hum))
      {
        lcd.setCursor(0,0);//posiciona o cursor
        lcd.print("FALHA NO SENSOR");//Envia mensagem de Falha
                
        lcd.setCursor(0,1);
        lcd.print("ERRO NUMERO: 111");//Texto que antecede a informação no display
        
        //valores a serem enviados ao banco de dados em caos de falhas na leitura do sensor
        temp = 111;
        intHum = 111;
        hum = 111;      
      }

      else
      { 
        lcd.setCursor(0,0);//posiciona o cursor
        lcd.print("TEMPERAT. ");//Texto que antecede a informação no display
        lcd.setCursor(10,0);
        lcd.print(temp,1);//Envia um float(valor da temperatura) para o display com uma casa decimal
        lcd.setCursor(15,0);//Posiciona o cursor
        lcd.print("C");
        lcd.setCursor(2,1);
        lcd.print("UMIDADE");//Texto que antecede a informação no display
        lcd.setCursor(11,1);
        lcd.print(intHum);//Envia para o display o valor da humidade
        lcd.setCursor(13,1);
        lcd.print("%");          
      }
      
      delay(100);
      oldtemp=temp;//Atualiza o valor da leitura anterior
      old_intHum=intHum;//Atualiza o valor da leitura anterior

    }

    // Ler o valor analógico do pino 
    int analogValue = (analogRead(AnalogPin)*100)/4095;//Armazenar o valor analógico lido em %
  
    // Imprimir o valor lido no monitor serial
    Serial.print("Valor analógico lido no pino ");
    Serial.print(AnalogPin);
    Serial.print(": ");
    Serial.println(analogValue);

    // Converte os valoresdas variáveis para char array  de forma que possa ser lido no monitor serial
    char tempString[8];
    dtostrf(temp, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    
     
    char humString[8];
    dtostrf(hum, 1, 2, humString);
    Serial.print("Humidity: " );
    Serial.println(humString);
    

    char EstadoCamaraString[8];
    dtostrf(EstadoCamara, 1, 2, EstadoCamaraString);
    Serial.print("EstadoCamara: ");
    Serial.println(EstadoCamaraString);
    Serial.println(comando);
    
    Serial.println(Motor);


    
   //Composição da String que armazenará os dados de transmitidos
   //Os valores de humidade e temperatura externas, estão sendo enviados apenas para testar a transmissão até que um novo sensor seja instalado
    String cjson = "{\"data\": {\"Temp_Interna\": " + String(temp) + ",\"Temp_Externa\": " + String(temp) + ",\"Umidade_Interna\": " + String(hum) + ",\"Umidade_Externa\": " + String(hum) + ",\"Estado_Camara\": " + String(EstadoCamara) + ",\"Analog_State\": " + String(analogValue) + "} }";
    
    cjson.toCharArray(json,170); //Organiza os dados no formaro da transmissão
    client.publish(state_topic,json); //Publica os dados na plataforma wnology

    
  }
}