all:
	make -C x32 
	make -C x64
clean:
	make -C x32  clean
	make -C x64  clean
run:
	bash start.sh
