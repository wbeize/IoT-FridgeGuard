#!/bin/bash

# URL do repositório remoto
REMOTE_URL=$1

if [ -z "$REMOTE_URL" ]; then
  echo "Uso: $0 <URL do repositório remoto>"
  exit 1
fi

# Verifica se estamos em um repositório Git
if [ ! -d ".git" ]; then
  echo "Erro: Este script deve ser executado em um repositório Git."
  exit 1
fi

# Verifica se estamos na branch 'develop'
CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)
if [ "$CURRENT_BRANCH" != "develop" ]; then
  echo "Erro: Este script deve ser executado na branch 'develop'."
  exit 1
fi

# Verifica se a branch 'develop' existe no repositório remoto
if git ls-remote --heads "$REMOTE_URL" develop | grep develop > /dev/null; then
  echo "A branch 'develop' existe no repositório remoto."
else
  echo "A branch 'develop' NÃO existe no repositório remoto."
  exit 1
fi
