CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATMega8  -l -g -MHasMul -MEnhanced -Wa-W 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x2000 -Wl-W -bfunc_lit:0x26.0x2000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = main.o 

ADC7:	$(FILES)
	$(CC) -o ADC7 $(LFLAGS) @ADC7.lk   -lstudio
main.o: C:\iccv7avr\include\iom8v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h
main.o:	main.c
	$(CC) -c $(CFLAGS) main.c
