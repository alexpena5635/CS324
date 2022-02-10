CPP = g++ -std=c++1y
OBJS = canvas.o testLine.o

graphic: $(OBJS)
	$(CPP) $^ -o $@

testLine.o: testLine.cpp
	$(CPP) -c $^

canvas.o: canvas.cpp
	$(CPP) -c $^

clean: 
	rm graphic $(OBJS)
