# Matriz-primos


## O objetivo do programa a ser desenvolvido é: dada uma matriz de números naturais aleatórios (dentro do intervalo 0 a 29999) verificar quantos números primos existem, indicar suas posições na matriz e contabilizar o tempo necessário para realizar esta computação. Isso deve feito de duas formas:
1. De modo sequencial, ou seja, a contagem dos primos e inclusão em uma
estrutura de dados das posições dos números primos encontrados na
matriz de primos deve ser feita um número após o outro. O tempo para
realizar essa computação ser ́a considerado seu tempo de referência.
2. De modo concorrente. Para tanto, o programa deve subdividir a matriz
em “blocos” (submatrizes) sem efetuar cópias da mesma, baseando-se
apenas em  ́ındices. A verificação dos números primos de cada subma-
triz bem como o registro de suas posições deve ser realizada por uma
thread independente.
