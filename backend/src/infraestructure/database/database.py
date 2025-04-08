import pandas as pd
from sqlalchemy import create_engine

# Cria a engine de conexão com o PostgreSQL
engine = create_engine('postgresql://seu_usuario:sua_senha@localhost:5432/seu_database')

# Lê o CSV e converte a coluna de timestamp
df = pd.read_csv('backend/src/infraestructure/iot-friedgeguard.csv',
                 parse_dates=['timestamp'],
                 dayfirst=True,
                 encoding='utf-8')

# Converte os tipos de dados para assegurar a compatibilidade
df['temp_int'] = df['temp_int'].astype(float)
df['umid_int'] = df['umid_int'].astype(float)
df['umid_ext'] = df['umid_ext'].astype(float)
df['temp_ext'] = df['temp_ext'].astype(float)
df['camara'] = df['camara'].astype(int)
df['analog'] = df['analog'].astype(int)

# Grava o DataFrame na tabela do banco de dados (substitui se já existir)
df.to_sql('iot_friedgeguard', engine, if_exists='replace', index=False)