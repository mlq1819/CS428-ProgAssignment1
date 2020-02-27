S=server
P=client
CFLAGS= -g -Wall

all: $(S) $(P)

$(S): $(S).cpp
	g++ $(CFLAGS) -o $(S).exe $(S).cpp
	
$(P): $(P).cpp
	g++ $(CFLAGS) -o $(P).exe $(P).cpp
	
run $(S): $(S)
	./$(S).exe

run $(P): $(P)
	./$(P).exe	
	
clean:
	rm -rf $(S)
	rm -rf $(P)