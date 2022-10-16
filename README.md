# Compilador para a linguagem C--
Trabalho da disciplina Teoria dos Compiladores da UFJF, do semestre 2022.3

Grupo formado por 
- Júlia Almeida Valadares
- Thiago de Almeida Lopes
- Yagho Mattos da Rocha

## Build

O compilador usado é para linguagem C foi o gcc, na versão 9.2.0 (MinGW.org GCC Build-2). Enquanto para C++ foi usado o g++, na versão 9.2.0 (MinGW.org GCC Build-2).

Foram exportados três arquivos Makefile do CodeBlocks que são especificos para os três
sistemas operacionais dominantes no mercado. O comando deve ser executado na raiz do repositório do trabalho.

Sistema Operacional | Makefile             | Comando
------------------- | -------------------- | ------------------------------------
Windows             | Makefile.windows.mak | mingw32-make -f Makefile.windows.mak
Unix (Linux)        | Makefile.unix.mak    | make -f Makefile.unix.mak
OSX (mac)           | Makefile.mac.mak     | make -f Makefile.mac.mak

## Debug

Para fazer o debug, basta usar o gdb com o comando abaixo, em um terminal aberto na raiz do repositório do trabalho.

Sistema Operacional | Comando
------------------- | ------------------------------------------------------------
Windows             | gdb -nx -fullname -quiet -args bin\Debug\Trabalho-DCC045.exe
Linux e OSX         | gdb -nx -fullname -quiet -args bin/Debug/Trabalho-DCC045.exe

Após aberto os seguintes comandos podem ser usados

Comando                       | Descrição
----------------------------- | ------------------------------------------------
run                           | Inicia a execução do programa
break [file_name]:line_number | Define um breakpoint em uma linha de um arquivo
print {variable}              | Mostra o valor de uma variável
step                          | Vai para a próxima linha do programa
continue                      | Continua até o próximo breakpoint
quit                          | Sai do debugger