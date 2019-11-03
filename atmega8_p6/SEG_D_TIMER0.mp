NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0026   00B0 =    176. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0026  __idata_start
       00D6  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00D6   0466 =   1126. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       006B  __start
       006B  __text_start
       008C  _exit
       008D  _btn1_count
       01C1  _btn2
       01F3  _key_scan
       0215  _delay_us
       021D  _delay_ms
       022E  _port_init
       0237  _timer0_open
       0242  _timer0_close
       024B  _init_devices
       0256  _timer0_ovf_isr
       0299  _main
       029E  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   00B0 =    176. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _seg
       0060  __data_start
       0076  _btn1_1
       0082  _btn1_2
       008E  _btn1_3
       0098  _btn1_4
       00A2  _btn1_5
       00AE  _btn1_6
       00BA  _btn1_7
       00C0  _btn1_8
       00C6  _btn1_9
       00DC  _btn1_10
       00F2  _btn1_index
       0106  _data
       0108  _data2
       010A  _i
       010C  _count
       010E  _count2
       0110  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0014 =     20. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtAVR.o	[ crtavr.s ]
main.o	[ main.c ]
<library>	

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x26
data = 0x60
eeprom:0.512

