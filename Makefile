SRCS = $(wildcard *.cpp)
HDRS = $(wildcard *.h)
LIBS = -lncurses

make:
	g++ $(SRCS) $(LIBS) -o snake

clean:
	del /F /Q *.exe

