all: markov_chain_quotes

markov_chain_quotes: main.o word.o filterProfanity.o
	g++ main.o word.o filterProfanity.o -o markov_chain_quotes

main.o: main.cpp
	g++ -c main.cpp

word.o: word.cpp
	g++ -c word.cpp

filterProfanity.o: filterProfanity.cpp
	g++ -c filterProfanity.cpp

clean:
	rm *.o markov_chain_quotes