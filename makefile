DIR_ENTRADA_1=./entrada/entrada10.csv
DIR_ENTRADA_2=./entrada/entrada50.csv
DIR_ENTRADA_3=./entrada/entrada100.csv

DIR_SAIDA_1=./saida/saida10.csv
DIR_SAIDA_2=./saida/saida50.csv
DIR_SAIDA_3=./saida/saida100.csv

DIR_RESP_1=./saida-esperada/saida10.csv
DIR_RESP_2=./saida-esperada/saida50.csv
DIR_RESP_3=./saida-esperada/saida100.csv

all: clean compile runAll diffAll # valAll

compile: vertice aresta grafo
	@ gcc -o trab2 vertice.o aresta.o grafo.o main.c

vertice:
	@ gcc -c vertice.c

aresta:
	@ gcc -c aresta.c

grafo:
	@ gcc -c grafo.c

run1: clean compile
	@ ./trab2 ${DIR_ENTRADA_1} ${DIR_SAIDA_1}

run2: clean compile
	@ ./trab2 ${DIR_ENTRADA_2} ${DIR_SAIDA_2}

run3: clean compile
	@ ./trab2 ${DIR_ENTRADA_3} ${DIR_SAIDA_3}

runAll: run1 run2 run3

val1: clean compile
	@ valgrentradad --leak-check=full ./trab2 ${DIR_ENTRADA_1} ${DIR_SAIDA_1}

val2: clean compile
	@ valgrentradad --leak-check=full ./trab2 ${DIR_ENTRADA_2} ${DIR_SAIDA_2}

val3: clean compile
	@ valgrentradad --leak-check=full ./trab2 ${DIR_ENTRADA_3} ${DIR_SAIDA_3}

valAll: val1 val2 val3

diff1: clean compile
	@ ./trab2 ${DIR_ENTRADA_1} ${DIR_SAIDA_1}
	@ diff ${DIR_SAIDA_1} ${DIR_RESP_1}

diff2: clean compile
	@ ./trab2 ${DIR_ENTRADA_2} ${DIR_SAIDA_2}
	diff ${DIR_SAIDA_2} ${DIR_RESP_2}

diff3: clean compile
	@ ./trab2 ${DIR_ENTRADA_3} ${DIR_SAIDA_3}
	diff ${DIR_SAIDA_3} ${DIR_RESP_3}

diffAll: diff1 diff2 diff3

clean:
	@ rm -f *.o trab2 saida/*