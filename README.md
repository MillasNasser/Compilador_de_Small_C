Compilador de CSmall

Para compilar execute make, no terminal $: make

Para executar, ./main.out [Nome do arquivo a ser processado]
Ex: $: ./main.out ./utils/cod.c

Para alterar o nome do arquivo de saida tanto da tabela de
símbolos quanto da árvore de sintaxe abstrata basta fazer:
./main.out [Arquivo a analisar] [Nome tabela de símbolos] [Nome arvore abstrata]
Ex: $: ./main.out ./utils/cod.c saidaTabela saidaArvore
    $: ./main.out ./utils/cod.c saidaTabela

obs: Não é necessário passar esses atributos, se for renomear
    apenas a tabela só o primeiro atributo é necessário, mas
    para renomear a árvore é necessário passar o nome da tabela
    e também antes do nome da árvore. Não é possível renomear
    apenas a árvore.
    
A arquivos que são gerados e que não podem ter seu nome alterado, 
tal como, o .txt e o cod3Addr.txt. O logErro.txt indica quais 
foram os erros no código-fonte disponibilizado. Já o cod3Addr.txt 
fornece o código de 3 endereços correspondente ao código-fonte
disponibilizado.
