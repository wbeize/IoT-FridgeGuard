import uvicorn
from dotenv import load_dotenv
import os

# Carregar variáveis de ambiente
env_path = os.path.join(os.path.dirname(__file__), "../.env")  # Ajuste conforme necessário
load_dotenv(dotenv_path=env_path)

# Executar a aplicação FastAPI
if __name__ == "__main__":
    uvicorn.run("main:app", host="127.0.0.1", port=8000, reload=True)
