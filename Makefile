all:
	g++ main.cpp -o xpvibes -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run:
	./xpvibes

clean:
	rm ./xpvibes