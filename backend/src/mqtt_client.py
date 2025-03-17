import paho.mqtt.client as mqtt

BROKER = "localhost"
PORT = 1883
TOPIC = "fridgeguard/sensor"

def on_message(client, userdata, message):
    print(f"Mensagem recebida: {message.payload.decode()}")

client = mqtt.Client()
client.on_message = on_message
client.connect(BROKER, PORT)
client.subscribe(TOPIC)
client.loop_start()
