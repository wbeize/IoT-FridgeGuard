import psycopg2
import csv
from datetime import datetime

# Configure os parâmetros de conexão com o seu banco de dados
conn = psycopg2.connect(
    database='seu_database',
    user='seu_usuario',
    password='sua_senha',
    host='localhost',
    port='5432'
)

cur = conn.cursor()

# Cria a tabela se não existir
cur.execute("""
    CREATE TABLE IF NOT EXISTS iot_friedgeguard (
        sensor VARCHAR(50),
        sensor_id VARCHAR(50),
        timestamp TIMESTAMP,
        temp_int REAL,
        umid_int REAL,
        umid_ext REAL,
        temp_ext REAL,
        localizacao VARCHAR(255),
        camara INTEGER,
        analog INTEGER
    );
""")
conn.commit()

# Função para converter a string de data/hora
def parse_timestamp(ts_str):
    return datetime.strptime(ts_str, "%d/%m/%Y %H:%M:%S")

# Abre e lê o arquivo CSV e insere os dados na tabela
with open('backend/src/infraestructure/iot-friedgeguard.csv', newline='', encoding='utf-8') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        cur.execute("""
            INSERT INTO iot_friedgeguard (sensor, sensor_id, timestamp, temp_int, umid_int, umid_ext, temp_ext, localizacao, camara, analog)
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s);
        """, (
            row['sensor'],
            row['sensor_id'],
            parse_timestamp(row['timestamp']),
            float(row['temp_int']),
            float(row['umid_int']),
            float(row['umid_ext']),
            float(row['temp_ext']),
            row['localizacao'],
            int(row['camara']),
            int(row['analog'])
        ))
conn.commit()

cur.close()
conn.close()