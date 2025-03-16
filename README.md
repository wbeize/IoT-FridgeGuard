# IoT-FridgeGuard

## 📌 Descrição do Projeto
**IoT-FridgeGuard** é um sistema de **monitoramento inteligente de equipamentos de refrigeração** baseado em **Internet das Coisas (IoT)**. O projeto foi desenvolvido no contexto do **Projeto Integrador 3 (PI-3) da UNIVESP**, com o objetivo de evitar perdas financeiras e garantir a **conservação adequada de alimentos** armazenados em câmaras frias. 

O sistema utiliza **sensores IoT (ESP32, sensores de temperatura e umidade)** para coletar dados em tempo real e uma plataforma web para visualização, alertas automatizados e análise preditiva para prevenção de falhas.

---

## 🎯 Objetivos
- Monitorar **temperatura e umidade** em tempo real em câmaras de refrigeração.
- Enviar **alertas automáticos** via API (WhatsApp, SMS, e-mail) em caso de falha no sistema de refrigeração.
- Armazenar dados históricos em **nuvem** para análise e auditoria.
- Utilizar **aprendizado de máquina** para prever falhas e otimizar o funcionamento dos equipamentos.
- Disponibilizar uma **interface web responsiva** para acompanhamento remoto.

---

## 🚀 Tecnologias Utilizadas
### **🔧 Hardware**
- **ESP32** – Microcontrolador para comunicação IoT.
- **Sensores de Temperatura e Umidade** (DHT22, DS18B20).

### **🖥️ Software & Ferramentas**
- **Linguagens:** Python (Backend), JavaScript (Frontend)
- **Framework Web:** Flask ou FastAPI (Backend), React.js (Frontend)
- **Banco de Dados:** PostgreSQL / Firebase
- **Plataforma IoT:** Wegnology
- **Cloud Computing:** AWS / Firebase
- **APIs de Notificação:** Twilio API / WhatsApp API / SMTP
- **Controle de Versão:** Git e GitHub
- **Integração Contínua:** GitHub Actions

---

## 📜 Estrutura do Projeto
```
IoT-FridgeGuard/
│── backend/             # Código-fonte do servidor e APIs
│   ├── app.py          # Servidor principal
│   ├── models.py       # Modelos do banco de dados
│   ├── routes.py       # Rotas da API
│   ├── services.py     # Lógica de negócios
│── frontend/            # Aplicação Web
│   ├── public/
│   ├── src/
│   │   ├── components/ # Componentes React
│   │   ├── pages/      # Páginas da aplicação
│── sensors/             # Código para ESP32
│── docs/                # Documentação do projeto
│── README.md            # Documentação principal
│── requirements.txt     # Dependências do backend
│── package.json         # Dependências do frontend
│── .gitignore           # Arquivos ignorados pelo Git
```

---

## 📦 Como Executar o Projeto
### **1️⃣ Pré-requisitos**
Antes de começar, instale as dependências necessárias:
- [Python 3.x](https://www.python.org/downloads/)
- [Node.js](https://nodejs.org/en/)
- [Docker](https://www.docker.com/) (opcional)

### **2️⃣ Clone o Repositório**
```sh
  git clone https://github.com/seu-usuario/IoT-FridgeGuard.git
  cd IoT-FridgeGuard
```

### **3️⃣ Configurar e Rodar o Backend**
```sh
cd backend
pip install -r requirements.txt
python app.py
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

---

## 📢 Contribuição
Se deseja contribuir com o projeto:
1. **Fork** o repositório.
2. Crie uma **branch** para sua funcionalidade (`git checkout -b minha-feature`).
3. Faça um **commit** das suas alterações (`git commit -m 'Adicionando nova feature'`).
4. Envie para o repositório (`git push origin minha-feature`).
5. Abra um **Pull Request**.

---

## 📜 Licença
Este projeto está sob a licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

📌 Desenvolvido no **Projeto Integrador em Computação III (PI-III) da UNIVESP** 🚀
