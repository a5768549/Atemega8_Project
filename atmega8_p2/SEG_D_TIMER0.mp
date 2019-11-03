NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0026   0026 =     38. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0026  __idata_start
       004C  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   004C   0640 =   1600. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0026  __text_start
       0026  __start
       0047  _exit
       0048  _key_scan
       007F  _btn1
       012E  _btn2
       01E2  _w
       0278  _delay_us
       0280  _delay_ms
       0291  _port_init
       029A  _timer0_int
       02A1  _init_devices
       02AA  _timer0_ovf_isr
       0304  _main
       030D  mod16s
       0311  div16s
       032A  mod16u
       032C  div16u
       032D  xdiv16u
       0346  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0026 =     38. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _seg
       0074  _data
       0076  _flag
       0078  _count
       007A  _th
       007C  _hu
       007E  _ten
       0080  _num
       0082  _i
       0084  _j
       0086  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0014 =     20. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtAVR.o	[ crtavr.s ]
main.o	[ main.c ]
<library>	[ div16s.s, div16u.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x26
data = 0x60
eeprom:0.512

