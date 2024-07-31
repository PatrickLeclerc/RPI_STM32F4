clientPort  = aconnect -i | grep "KOMPLETE KONTROL M32" | awk '/^client.*:g$/' input.txt

all:
	make clean
	make build
	make flash

build:
	make -f Makefile.STM32

clean:
	rm -rf -v ./build

flash:
	st-flash --reset write build/F446re.bin 0x8000000

probe:
	st-info --probe

test:
	./test.cmd

uart:
	picocom -b 115200 /dev/ttyACM0
	#cat /dev/ttyACM0

midi:
	amidi -l
	amidi --dump -p hw:0,0,0

install:
	cd scripts; ./install.cmd