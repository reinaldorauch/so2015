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
ARGS=""

separator() {
    echo "---------------------------------------------------------------------"
}

menu() {
    separator
    echo "Executador de comandos"
    separator
    echo "Digite uma das opções de ação:"
    echo "01. Listar determinado diretório" # DONE
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
    separator
    read OPTION
}

comando() {
    case "$OPTION" in
        "01" | "1" ) execListDir;;
    esac
}

aditionalArguments() {
    ARGS=""
    echo "Se quiser passar mais argumentos, digite-os agora:"
    read ARGS
}

execListDir() {
    separator
    echo "Escolhido listar conteúdo de determinado diretório."
    echo "Digite o diretório a ser listado. Deixe vazio para o atual:"
    read LSDIR

    aditionalArguments

    echo ""
    separator
    ls $ARGS $LSDIR
    separator
}



while [[ "$OPTION" -ne 11 ]]
do
    menu
    comando
done