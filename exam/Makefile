default: finalexam

account.o:
	g++ -c account.cpp

checking.o:
	g++ -c checking.cpp

creditcard.o:
	g++ -c creditcard.cpp

saving.o:
	g++ -c saving.cpp

finalexam: account.o checking.o creditcard.o saving.o
	g++  -o finalexam main.cpp account.o checking.o creditcard.o saving.o

clean:
	rm -f account.o finalexam