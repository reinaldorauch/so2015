#!/bin/bash

saudacao="Hello"

echo $saudacao
echo "programa $0 em execucao"
echo "O primeiro parametro eh $1"
echo "O segundo parametro eh $2"
echo "O terceiro parametro eh $3"
echo "O quarto parametro eh $*"
echo "Diretorio home do usuario eh $HOME"

echo "Por faor entre com uma frase"
read saudacao
echo "$saudacao"
echo "O script sera finalizado"
