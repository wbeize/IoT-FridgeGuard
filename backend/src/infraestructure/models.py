from sqlalchemy import Column, Integer, String, Float, Boolean, ForeignKey, DateTime, Text
from sqlalchemy.orm import relationship
from database import Base
from datetime import datetime


class Equipamento(Base):
    __tablename__ = 'equipamentos'

    id = Column(Integer, primary_key=True, index=True)
    nome = Column(String, nullable=False)
    descricao = Column(Text)
    localizacao = Column(String)

    sensores = relationship("Sensor", back_populates="equipamento")
    alertas = relationship("Alerta", back_populates="equipamento")


class Sensor(Base):
    __tablename__ = 'sensores'

    id = Column(Integer, primary_key=True, index=True)
    tipo = Column(String, nullable=False)
    modelo = Column(String)
    equipamento_id = Column(Integer, ForeignKey('equipamentos.id'))

    equipamento = relationship("Equipamento", back_populates="sensores")
    leituras = relationship("Leitura", back_populates="sensor")


class Leitura(Base):
    __tablename__ = 'leituras'

    id = Column(Integer, primary_key=True, index=True)
    sensor_id = Column(Integer, ForeignKey('sensores.id'))
    temperatura = Column(Float, nullable=False)
    umidade = Column(Float, nullable=False)
    data_hora = Column(DateTime, default=datetime.utcnow)

    sensor = relationship("Sensor", back_populates="leituras")


class Alerta(Base):
    __tablename__ = 'alertas'

    id = Column(Integer, primary_key=True, index=True)
    equipamento_id = Column(Integer, ForeignKey('equipamentos.id'))
    mensagem = Column(String(255))
    data_hora = Column(DateTime, default=datetime.utcnow)
    resolvido = Column(Boolean, default=False)

    equipamento = relationship("Equipamento", back_populates="alertas")
