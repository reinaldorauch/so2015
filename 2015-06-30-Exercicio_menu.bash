#!/bin/bash
#
# Menu para um comando do shell script
#
# Comandos:
#
# ls
# cp
# mv
# renomear
# pwd
# alterar diretório atual
# mostrar conteúdo de um arquivo
# wc (palavras, letras, linhas)
# rm
# ps
# sair do programa
#

OPTION=0

menu() {
    echo "Executador de comandos"
    echo "Digite uma das opções de ação:"
    echo "01. Listar determinado diretório"
    echo "02. Copiar um determinado arquivo"
    echo "03. Mover um arquivo"
    echo "04. Renomear um arquivo"
    echo "05. Verificar diretório atual"
    echo "06. Alterar diretório atual"
    echo "07. Mostrar conteúdo de um arquivo"
    echo "08. Contar palavras, letras ou linhas"
    echo "09. Remover um arquivo"
    echo "10. Listar terminais abertos"
    echo "11. Sair do programa"
    read OPTION
}

comando() {
    case "$OPTION" in
        "01" | "1" ) execListDir;;
    esac
}

while [[ "$OPTION" -ne 11 ]]
do
    menu
    comando
done