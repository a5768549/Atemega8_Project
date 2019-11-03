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
                            text   004C   0598 =   1432. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0026  __start
       0026  __text_start
       0047  _exit
       0048  _key_scan
       00B3  _stop_fuc
       00E8  _speed_count
       0183  _up_count
       020A  _delay_us
       0212  _delay_ms
       0223  _port_init
       022C  _timer0_close
       0235  _timer0_open
       023E  _init_devices
       024A  _timer0_ovf_isr
       02AE  _main
       02B9  mod16s
       02BD  div16s
       02D6  mod16u
       02D8  div16u
       02D9  xdiv16u
       02F2  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0026 =     38. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _seg
       0074  _data
       0076  _flag
       0078  _th
       007A  _hu
       007C  _ten
       007E  _num
       0080  _i
       0082  _speed
       0084  _again
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

