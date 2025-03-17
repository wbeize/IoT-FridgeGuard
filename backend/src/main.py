from fastapi import FastAPI
from paho.mqtt import client as mqtt_client

app = FastAPI()

@app.get("/")
def read_root():
    return {"message": "API IoT-FridgeGuard rodando!"}

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
