from database import engine, Base

# Criar as tabelas no banco de dados
Base.metadata.create_all(bind=engine)

print("✅ Tabelas criadas com sucesso!")
