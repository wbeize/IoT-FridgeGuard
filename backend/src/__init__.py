import os
from dotenv import load_dotenv

# Carregar variáveis de ambiente automaticamente
load_dotenv(os.path.abspath(os.path.join(os.path.dirname(__file__), "../.env")))