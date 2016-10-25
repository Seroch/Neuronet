train: training.cpp neuronet.o
	g++ -o train.exe training.cpp neuronet.cpp -std=c++11

test: testing.cpp neuronet.o
	g++ -o test.exe testing.cpp neuronet.cpp -std=c++11

neuronet.o: neuronet.cpp neuronet.h
	g++ -c neuronet.cpp -std=c++11

debugtrain:
	g++ -g -o debugtrain.exe training.cpp neuronet.cpp -std=c++11

debugtest:
	g++ -g -o debugtest.exe testing.cpp neuronet.cpp -std=c++11

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups