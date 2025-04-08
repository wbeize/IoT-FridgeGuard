# IoT-FridgeGuard

## 📌 Descrição do Projeto

**IoT-FridgeGuard** é um sistema de **monitoramento inteligente de equipamentos de refrigeração** baseado em **Internet das Coisas (IoT)** e projetado seguindo a **Arquitetura Hexagonal**. O projeto foi desenvolvido no contexto do **Projeto Integrador em Computação III (PI-3) da UNIVESP**, com o objetivo de evitar perdas financeiras e garantir a **conservação adequada de alimentos** armazenados em equipamentos de refrigeração.

A adoção da **Arquitetura Hexagonal** permite maior flexibilidade e desacoplamento entre as camadas de negócio e de infraestrutura. Isso possibilita que diferentes interfaces (sensores, APIs, banco de dados e interface web) interajam com o sistema de forma independente, promovendo escalabilidade e manutenção facilitada.

O sistema utiliza **sensores IoT (ESP32, sensores de temperatura e umidade)** para coletar dados em tempo real e uma plataforma web para visualização, alertas automatizados e análise preditiva para prevenção de falhas.

---

## 🎯 Objetivos

- Monitorar **temperatura e umidade** em tempo real em equipamentos de refrigeração.
- Enviar **alertas automáticos** via API (WhatsApp, SMS, e-mail) em caso de falha no sistema de refrigeração.
- Armazenar dados históricos em **nuvem** para análise e auditoria.
- Utilizar **aprendizado de máquina** para prever falhas e otimizar o funcionamento dos equipamentos.
- Disponibilizar uma **interface web responsiva** para acompanhamento remoto.
- Aplicar os princípios da **Arquitetura Hexagonal** para garantir modularidade, desacoplamento e escalabilidade do sistema.

---

## 🏗️ Arquitetura do Sistema

O **IoT-FridgeGuard** está sendo projetado seguindo o padrão de **Arquitetura Hexagonal (Ports & Adapters)**. Essa abordagem desacopla a lógica de negócios das dependências externas, permitindo maior flexibilidade na integração com novos dispositivos e serviços. 

### 🔹 **Camadas da Arquitetura Hexagonal**

1. **Camada de Domínio (Regras de Negócio)**: Contém as regras essenciais do sistema, como os cálculos de variação de temperatura e os critérios para disparo de alertas.
2. **Adaptadores de Entrada (Interfaces de Usuário e Sensores)**: Responsáveis por capturar os dados de temperatura e umidade dos sensores IoT e pelas interações do usuário via interface web.
3. **Adaptadores de Saída (Banco de Dados e APIs de Notificação)**: Gerenciam o armazenamento dos dados históricos na nuvem e a comunicação com serviços de alerta (WhatsApp, SMS, e-mail).

Essa abordagem permite que o sistema seja facilmente expandido e mantenha sua confiabilidade ao longo do tempo.

---

## 🚀 Tecnologias Utilizadas

### **🔧 Hardware**

- **ESP32** – Microcontrolador para comunicação IoT.
- **Sensores de Temperatura e Umidade** (DHT22).

### **🖥️ Software & Ferramentas**

- **Linguagens:** Python (Backend), JavaScript (Frontend)
- **Framework Web:** FastAPI (Backend), React.js (Frontend)
- **Banco de Dados:** PostgreSQL
- **Plataforma IoT:** Wegnology
- **Cloud Computing:** Azure App Service
- **Comunicação:** MQTT para Integração IoT
- **APIs de Notificação:** Twilio API / SMTP para envio de e-mails
- **Controle de Versão:** Git e GitHub
- **Integração Contínua:** GitHub Actions

---

## 📜 Estrutura do Projeto
```
IoT-FridgeGuard/                  # Raiz do projeto
│── backend/                      # Backend (FastAPI)
│   ├── venv/                     # Ambiente virtual do Python
│   │   ├── bin/                  # Contém os executáveis, incluindo "activate" para ativar o ambiente virtual.
│   │   ├── lib/                  # Contém os pacotes Python instalados no ambiente virtual.
│   │   ├── include/              # Contém headers de bibliotecas C caso seja necessário compilá-las.
│   │   ├── .gitignore            
│   │   ├── .Python               # Link simbólico para o binário do Python usado na criação do venv.
│   │   ├── pyenv.cfg             # Arquivo de configuração do ambiente virtual.
│   ├── src/                      # Código-fonte do backend
│   │   ├── infraestructure/      
│   │       ├──── database.py     # Conexão com PostgreSQL
│   │   ├── main.py               # Ponto de entrada do FastAPI
│   │   ├── models.py             # Modelos do SQLAlchemy
│   │   ├── routes.py             # Rotas do FastAPI
│   │   ├── services.py           # Lógica de negócio
│   │   ├── mqtt.py               # Conexão com MQTT (ESP32)
│   │   ├── mqtt_client.py        # Cliente MQTT para integração
│   ├── requirements.txt          # Lista de dependências do Python
│── frontend/                     # Frontend (React.js)
│   ├── src/                      # Código-fonte do frontend
│   ├── package.json              # Dependências do frontend
│   ├── next.config.js            # Configuração do Next.js
│── sensors/                      # Código para ESP32 (MicroPython/C)
│   ├── firmware/                 # Código-fonte do ESP32
│   ├── config/                   # Configurações do MQTT e sensores
│── .github/workflows/            # Pipeline CI/CD (GitHub Actions)
│   ├── ci-cd-pipeline.yaml       # Automação de deploy e testes
│── .gitignore                    # Arquivos ignorados pelo Git
│── README.md                     # Documentação do projeto
```

---

## 🚀 Deploy na Azure App Service

O backend será hospedado no **Azure App Service**, que permite deploys diretos via GitHub Actions sem necessidade de Docker. Para configurar o deploy:

1. Criar um **App Service** na Azure.
2. Escolher o **runtime Python 3.11**.
3. Configurar o **Azure Database for PostgreSQL**.
4. Conectar o **GitHub Actions** ao App Service para deploy contínuo.

---

## 📦 Como Executar o Projeto

### **1️⃣ Pré-requisitos**

Antes de começar, instale as dependências necessárias:
- [Python 3.x](https://www.python.org/downloads/)
- [Node.js](https://nodejs.org/en/)

### **2️⃣ Clone o Repositório**
```sh
  git clone https://github.com/wbeize/IoT-FridgeGuard.git
  cd IoT-FridgeGuard
```

### **3️⃣ Configurar e Rodar o Backend**
```sh
cd backend
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
uvicorn src.main:app --reload
```

### **4️⃣ Configurar e Rodar o Frontend**
```sh
cd frontend
npm install
npm start
```

### **5️⃣ Executar o Código no ESP32**
1. Instale a **IDE Arduino** ou **Micropython**.
2. Configure a conexão Wi-Fi no código do ESP32.
3. Faça o upload do código para o microcontrolador.

---

## 📊 Funcionalidades
✅ Monitoramento de temperatura e umidade em tempo real.  
✅ Alertas automáticos para falhas no sistema de refrigeração.  
✅ Histórico de dados para análise preditiva e auditoria.  
✅ Integração com APIs de notificação.  
✅ Interface intuitiva e responsiva para acompanhamento remoto.  
✅ Arquitetura Hexagonal para maior escalabilidade e manutenção simplificada.  

---

## 📢 Contribuição

O projeto segue boas práticas de **versionamento de código e integração contínua (CI/CD)**. Para contribuir:

1. **Sempre inicie na branch `develop`** (`git checkout develop`)
2. Crie uma **branch** para suas alterações (`git checkout -b feature/sua-branch`).
3. Faça as alterações e **envie os commits** para o repositório remoto:

   ````
   git add .
   git commit -m "descrição clara da mudança"
   git push origin feature/nova-funcionalidade
   ```

4. Abra um **Pull Request** para a branch `develop`
5. Após a revisão, as alterações serão promovidas para a `main` através do fluxo definido no CI/CD.

---

## 📜 Licença
Este projeto está sob a licença MIT - veja o arquivo [LICENSE](../../../copy-pi-3/LICENSE) para mais detalhes.

📌 Em desenvolvimento para o **Projeto Integrador em Computação III (PI-3) da UNIVESP**. 🚀
