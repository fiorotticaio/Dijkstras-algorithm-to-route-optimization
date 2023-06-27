DIR_ENTRADA_1=./entrada/in10.csv
DIR_ENTRADA_2=./entrada/in50.csv
DIR_ENTRADA_3=./entrada/in100.csv

DIR_SAIDA_1=./saida/out-in10.csv
DIR_SAIDA_2=./saida/out-in50.csv
DIR_SAIDA_3=./saida/out-in100.csv

DIR_RESP_1=./saida-esperada/out-in10.csv
DIR_RESP_2=./saida-esperada/out-in50.csv
DIR_RESP_3=./saida-esperada/out-in100.csv

all: clean compile run diff

compile: vertice aresta PQ grafo atualizacao
	@ gcc -o trab2 vertice.o aresta.o PQ.o grafo.o atualizacao.o main.c

vertice:
	@ gcc -c vertice.c

aresta:
	@ gcc -c aresta.c

PQ:
	@ gcc -c PQ.c

atualizacao:
	@ gcc -c atualizacao.c

grafo:
	@ gcc -c grafo.c
	

run: clean compile
	@ ./trab2 ./entrada/in100000.csv ./saida/out-in100000.csv

run1: clean compile
	@ ./trab2 ${DIR_ENTRADA_1} ${DIR_SAIDA_1}

run2: clean compile
	@ ./trab2 ${DIR_ENTRADA_2} ${DIR_SAIDA_2}

run3: clean compile
	@ ./trab2 ${DIR_ENTRADA_3} ${DIR_SAIDA_3}

runAll: run0 run1 run2 run3


val: clean compile
	@ valgrind --leak-check=full ./trab2 ./entrada/in100000.csv ./saida/out-in100000.csv

val1: clean compile
	@ valgrind --leak-check=full ./trab2 ${DIR_ENTRADA_1} ${DIR_SAIDA_1}

val2: clean compile
	@ valgrind --leak-check=full ./trab2 ${DIR_ENTRADA_2} ${DIR_SAIDA_2}

val3: clean compile
	@ valgrind --leak-check=full ./trab2 ${DIR_ENTRADA_3} ${DIR_SAIDA_3}

valAll: val0 val1 val2 val3


diff:
	diff ./saida/out-in100000.csv ./saida-esperada/out-in100000.csv

diff1: clean compile
	@ ./trab2 ${DIR_ENTRADA_1} ${DIR_SAIDA_1}
	@ diff ${DIR_SAIDA_1} ${DIR_RESP_1}

diff2: clean compile
	@ ./trab2 ${DIR_ENTRADA_2} ${DIR_SAIDA_2}
	diff ${DIR_SAIDA_2} ${DIR_RESP_2}

diff3: clean compile
	@ ./trab2 ${DIR_ENTRADA_3} ${DIR_SAIDA_3}
	diff ${DIR_SAIDA_3} ${DIR_RESP_3}

diffAll: diff0 diff1 diff2 diff3


clean:
	@ rm -f *.o trab2