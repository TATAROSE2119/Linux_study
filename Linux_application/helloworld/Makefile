# 定义变量objects
objects := hello.o main.o

main: $(objects)
	gcc -o main $(objects)


main.o: main.c hello.h
# 	gcc -c main.c


hello.o: hello.c hello.h
# 	gcc -c hello.c

#声明伪目标
.PHONY: clean

clean:
	rm main $(objects)