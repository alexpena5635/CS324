CPP = g++ -std=c++1y
OBJS = matrix.o canvas.o graphics.o plotGraphics.o cubeTest.o #plot2d.o

cube.pbm: graphic
	./$^

graphic: $(OBJS)
	$(CPP) $^ -o $@

# plot2d.o: plot2d.cpp
# 	$(CPP) -c $^

cubeTest.o: cubeTest.cpp
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
