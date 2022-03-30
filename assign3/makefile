CPP = g++ -std=c++1y
OBJS = matrix.o canvas.o graphics.o plotGraphics.o plot2d.o

mytest.pbm: graphic
	./$^

graphic: $(OBJS)
	$(CPP) $^ -o $@

plot2d.o: plot2d.cpp
	$(CPP) -c $^

plotGraphics.o: plotGraphics.cpp
	$(CPP) -c $^

graphics.o: graphics.cpp
	$(CPP) -c $^

canvas.o: canvas.cpp
	$(CPP) -c $^

matrix.o: matrix.cpp
	$(CPP) -c $^
	
clean: 
	rm a.out a.exe graphic $(OBJS)
