all:
	make py

make build:
	python3.11 -m venv .venv
		
make py:
	./midi.py

uart:
	picocom /dev/ttyACM0 -b 115200

midi:
	amidi -l
	amidi --dump -p hw:0,0,0
	
clean: 
	rm *.o *.s *.exe