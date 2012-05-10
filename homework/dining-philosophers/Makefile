dine: dining-philosophers-runner.o sync.o philosopher.o chopstick.o utility.o
	gcc -o dine *.o -lpthread

dining-philosophers-runner.o: sync.h chopstick.h

chopstick.o: chopstick.h sync.h

sync.o: sync.h

philosopher.o: philosopher.h chopstick.h sync.h utility.h

utility.o: utility.h

clean:
	rm dine *.o
