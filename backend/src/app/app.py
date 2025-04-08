# backend/app.py
from flask import Flask, request, jsonify
from datetime import datetime
import psycopg2

app = Flask(__name__)

# Configuração da conexão com o banco
conn = psycopg2.connect(
    database='seu_database',
    user='seu_usuario',
    password='sua_senha',
    host='localhost',
    port='5432'
)
cur = conn.cursor()

def parse_timestamp(ts_str):
    return datetime.strptime(ts_str, "%d/%m/%Y %H:%M:%S")

@app.route('/iot', methods=['POST'])
def sensor_data():
    data = request.get_json()
    try:
        # Insere os dados recebidos na tabela
        cur.execute("""
            INSERT INTO iot_friedgeguard (sensor, sensor_id, timestamp, temp_int, umid_int, umid_ext, temp_ext, localizacao, camara, analog)
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s);
        """, (
            data.get('sensor'),
            data.get('sensor_id'),
            parse_timestamp(data.get('timestamp')),
            float(data.get('temp_int')),
            float(data.get('umid_int')),
            float(data.get('umid_ext')),
            float(data.get('temp_ext')),
            data.get('localizacao'),
            int(data.get('camara')),
            int(data.get('analog'))
        ))
        conn.commit()
        return jsonify({"status": "sucesso"}), 201
    except Exception as e:
        conn.rollback()
        return jsonify({"status": "erro", "mensagem": str(e)}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)