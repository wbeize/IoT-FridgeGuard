import os
from dotenv import load_dotenv
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, declarative_base

# Garante que o .env seja carregado corretamente
env_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../.env"))
load_dotenv(dotenv_path=env_path)

# Recupera a URL do banco de dados
DATABASE_URL = os.getenv("DATABASE_URL")

if not DATABASE_URL:
    raise ValueError("Erro: A variável DATABASE_URL não foi encontrada no .env")

# Criando conexão com o banco
engine = create_engine(DATABASE_URL, pool_pre_ping=True)

# Criando sessão
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

# Criando a Base para os modelos
Base = declarative_base()
