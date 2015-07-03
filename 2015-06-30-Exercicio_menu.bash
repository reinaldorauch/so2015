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

# Variável global para a escolha do programa
OPTION=0
# Variável global para gudardar os argumentos extras definidos para o comando
# atual
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
    # DONE
    echo "01. Listar determinado diretório"
    # DONE @todo make the dest validation
    echo "02. Copiar um determinado arquivo"
    # DONE
    echo "03. Mover um arquivo"
    # DONE
    echo "04. Renomear um arquivo"
    # DONE
    echo "05. Verificar diretório atual"
    # DONE
    echo "06. Alterar diretório atual"
    # DONE
    echo "07. Mostrar conteúdo de um arquivo"
    # @todo Perguntar contar do que
    echo "08. Contar palavras, letras ou linhas"
    # DONE
    echo "09. Remover um arquivo"
    # DONE
    echo "10. Listar processos"
    # DONE
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
        "03" | "3" ) execMoveFile;;
        "04" | "4" ) execRenameFile;;
        "05" | "5" ) execShowCurrentDir;;
        "06" | "6" ) execChangeCurrentDir;;
        "07" | "7" ) execCatFile;;
        "08" | "8" ) execWordsLettersLines;;
        "09" | "9" ) execRmFile;;
        "10"       ) execListOpenTTY;;
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
    separator
}

#
# Executa a ação de mover um determinado arquivo
#
execMoveFile() {
  separator
  echo "Escolhido ação de mover arquivo."
  echo "Digite o path do arquivo que deseja mover:"
  read MVFILE
  echo "Digite o caminho para a pasta de destino do arquivo:"
  read DEST

  if [ -f "$MVFILE" ]
  then
    if [ -d "$DEST" ]
    then
      mv $MVFILE $DEST
      echo "Arquivo movido com sucesso"
    else
      echo "Erro: não é um destino válido"
    fi
  else
    echo "Não é um arquivo válido"
  fi
  separator
}

#
# Executa a ação do menu de renomear um arquivo
#
execRenameFile() {
  separator
  echo "Escolhido a ação de renomear um arquivo."
  echo "Digite o nome original do arquivo para renomear:"
  read MVORIG
  echo "Digite o nome para qual você deseja que o arquivo receba:"
  read MVDEST

  if [ -f "$MVORIG" ]
  then
    mv $MVORIG $MVDEST
    echo "Arquivo renomeado com sucesso"
  fi
  separator
}

#
# Mostra o diretório atual do programa
#
execShowCurrentDir() {
  separator
  echo "Escolhido a ação de mostrar na tela o diretório atual."
  echo "O diretório atual é:"
  echo ""
  pwd
  echo ""
  separator
}

#
# Muda o diretório de trabalho atual
#
execChangeCurrentDir() {
  separator
  echo "Escolhido ação de alterar o diretório de trabalho."
  echo "Digite o diretório para que deseja mudar:"
  read DESTDIR

  if [ -d "$DESTDIR" ]
  then
    cd $DESTDIR
    echo "Diretório de trabalho alterado com sucesso"
  else
    echo 'Diretório inválido'
  fi
  separator
}

#
# Mostra o conteúdo de um arquivo na tela
#
execCatFile() {
  separator
  echo "Escolhido ação de mostrar um arquivo na tela."
  echo "Digite o arquivo que deseja imprimir:"
  read READFILE

  if [ -f "$READFILE" ]
  then
    less < $READFILE
  else
    echo "Arquivo inválido"
  fi
  separator
}

#
# Conta linhas, palavras ou letras
#
execWordsLettersLines() {
  separator
  echo "Escolhido ação de contar palavras, linhas ou letras."
  echo "Não está implementado ainda"
  separator
}

#
# Remove um determinado arquivo
#
execRmFile() {
  separator
  echo "Escolhido ação de remover um arquivo."
  echo "Digite o arquivo a ser removido:"
  read RMFILE

  if [[ -f "$RMFILE" ]]; then
    rm $RMFILE
    echo "Arquivo removido"
  else
    echo "Arquivo inválido"
  fi
  separator
}

#
# Lista os terminais abertos
#
execListOpenTTY() {
  separator
  echo "Escolhido ação de listar os processos abertos"
  echo "Digite argumentos para alterar a listagem dos processos:"
  read ARGS

  ps $ARGS | less
  separator
}

# Executa o programa enquando a opção escolhida não for 11 "saída do programa"
while [[ "$OPTION" -ne 11 ]]
do
    menu
    comando
done
