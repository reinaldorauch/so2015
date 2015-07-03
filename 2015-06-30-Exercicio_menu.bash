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

#
# Escreve uma linha separadora
#
separator() {
    echo "---------------------------------------------------------------------"
}

#
# Escreve o menu do programa
#
menu() {
    separator
    echo "Executador de comandos"
    separator
    echo "Digite uma das opções de ação:"
    echo "01. Listar determinado diretório" # DONE
    echo "02. Copiar um determinado arquivo" # DONE @todo make the dest validation
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

#
# Decide o comando a ser executado
#
comando() {
    case "$OPTION" in
        "01" | "1" ) execListDir;;
        "02" | "2" ) execCopyFile;;
    esac
}

#
# Captura argumentos adicionais ao programa
#
aditionalArguments() {
    ARGS=""
    echo "Se quiser passar mais argumentos, digite-os agora:"
    read ARGS
}

#
# Executa o comando de listar o diretório atual ou um indicado pelo usuário
#
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

#
# Executa o comando de copiar um arquivo
#
execCopyFile() {
    separator
    echo "Escolhido copiar um arquivo."
    echo "Digite o path para o arquivo de origem:"
    read ORIG
    echo "Digite o path para a pasta de destino:"
    read DEST
    separator
    if [ -f "$ORIG" ]
    then
        cp "$ORIG" "$DEST"
        echo "Copied file with success"
    elif [ -e "$ORIG" ]
    then
        echo "Erro: o arquivo de origem não é um arquivo acessivos"
    elif [ -n -d "$DEST" ]
    then
        echo "Erro: o diretório de destino não é um diretório acessivo"
    fi
}

# Executa o programa enquando a opção escolhida não for 11 (saída do programa)
while [[ "$OPTION" -ne 11 ]]
do
    menu
    comando
done
