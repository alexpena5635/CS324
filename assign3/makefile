CPP = g++ -std=c++1y
OBJS = matrix.o canvas.o graphics.o
CUBETEST = cubeTest.o 
PLOT2D = plotGraphics.o plot2d.o
MODEL3D = modeling3d.o

modeling.pbm: modeling
	./$^

cubeTest.pbm: cube
	./$^

plot2.pbm: plot2
	./$^

modeling: $(OBJS) $(MODEL3D)
	$(CPP) $^ -o $@

cube: $(OBJS) $(CUBETEST)
	$(CPP) $^ -o $@

plot2: $(OBJS) $(PLOT2D)
	$(CPP) $^ -o $@

modeling3d.o : modeling3d.cpp
	$(CPP) -c $^

cubeTest.o: cubeTest.cpp
	$(CPP) -c $^

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
	rm -f a.out a.exe modeling cube plot2 $(OBJS) $(CUBETEST) $(PLOT2D) $(MODEL3D)
