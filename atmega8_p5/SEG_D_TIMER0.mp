NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0026   0022 =     34. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0026  __idata_start
       0048  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0048   0698 =   1688. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0024  __text_start
       0024  __start
       0045  _exit
       0046  _btn2_1
       0091  _btn2_2
       00DC  _btn2_3
       014E  _btn1_fuc
       0178  _btn1
       018D  _key_scan
       01CC  _delay_us
       01D4  _delay_ms
       01E5  _port_init
       01EE  _timer0_close
       01F7  _timer0_open
       0202  _timer2_close
       020B  _timer2_open
       0216  _init_devices
       0224  _timer0_ovf_isr
       0299  _timer2_ovf_isf
       030A  _main
       031A  mod16s
       031E  div16s
       0337  mod16u
       0339  div16u
       033A  xdiv16u
       0353  pop_xgsetF0FC
       035E  push_xgsetF0FC
       0360  push_xgset30FC
       0362  push_xgset00FC
       0364  push_xgset003C
       0369  lsl16
       0370  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0022 =     34. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _seg
       0074  _data
       0076  _data2
       0078  _count
       007A  _count_num
       007C  _btn2_count
       007E  _btn2_3_count
       0080  _btn2_3_flag
       0082  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0014 =     20. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtAVR.o	[ crtavr.s ]
main.o	[ main.c ]
<library>	[ div16s.s, div16u.s, gpop5.s, gpush.s, lsl16.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x26
data = 0x60
eeprom:0.512

