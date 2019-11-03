NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0026   0023 =     35. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0026  __idata_start
       0049  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   004A   077E =   1918. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0025  __start
       0025  __text_start
       0046  _exit
       0047  _de_led
       00C2  _btn1
       015D  _btn2
       01FB  _key_scan
       0235  _delay_us
       023D  _delay_ms
       024E  _por_init
       0258  _display
       0261  _display1
       026B  _timer0_int
       0272  _init_devices
       0276  _ad_cat
       028C  _ad_chane
       02AF  _timer0_ovf_isr
       02EE  _main
       02F4  mod16u
       02F6  div16u
       02F7  xdiv16u
       0310  div32u
       0312  mod32u
       0316  div32s
       0318  mod32s
       0343  long_div_prolog
       0356  long_div_epilog
       0365  tst_R16_R19
       036A  tst_R24_R27
       036F  neg_R24_R27
       0378  empy32u
       0378  empy32s
       03A8  push_xgsetF00C
       03AF  pop_xgsetF00C
       03B6  neg32
       03BF  long_prolog
       03CD  long_epilog
       03D8  tstzero1
       03DE  tstzero2
       03E4  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0023 =     35. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _tab
       0070  _cnn
       0071  _i
       0072  _j
       0074  _ad
       0075  _ad_data2
       0077  _count
       0079  _flag
       007B  _th
       007D  _hu
       007F  _ten
       0081  _num
       0083  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0014 =     20. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtAVR.o	[ crtavr.s ]
main.o	[ main.c ]
<library>	[ div16u.s, div32.s, emul32.s, gpushz.s, lneg.s, longutil.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x26
data = 0x60
eeprom:0.512

