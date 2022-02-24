CPP = g++ -std=c++1y
OBJS = matrix.o canvas.o testLine.o 

graphic: $(OBJS)
	$(CPP) $^ -o $@

testLine.o: testLine.cpp
	$(CPP) -c $^

canvas.o: canvas.cpp
	$(CPP) -c $^

matrix.o: matrix.cpp
	$(CPP) -c $^
	
clean: 
	rm graphic $(OBJS)
