<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित TRIDENTFB_DEBUG
#घोषणा TRIDENTFB_DEBUG 0
#पूर्ण_अगर

#अगर TRIDENTFB_DEBUG
#घोषणा debug(f, a...)	prपूर्णांकk("%s:" f,  __func__ , ## a);
#अन्यथा
#घोषणा debug(f, a...)
#पूर्ण_अगर

#घोषणा output(f, a...) pr_info("tridentfb: " f, ## a)

#घोषणा Kb	(1024)
#घोषणा Mb	(Kb*Kb)

/* PCI IDS of supported cards temporarily here */

#घोषणा CYBER9320	0x9320
#घोषणा CYBER9388	0x9388
#घोषणा CYBER9382	0x9382		/* the real PCI id क्रम this is 9660 */
#घोषणा CYBER9385	0x9385		/* ditto */		
#घोषणा CYBER9397	0x9397
#घोषणा CYBER9397DVD	0x939A
#घोषणा CYBER9520	0x9520
#घोषणा CYBER9525DVD	0x9525
#घोषणा TGUI9440	0x9440
#घोषणा TGUI9660	0x9660
#घोषणा PROVIDIA9685	0x9685
#घोषणा IMAGE975	0x9750
#घोषणा IMAGE985	0x9850
#घोषणा BLADE3D		0x9880
#घोषणा CYBERBLADEE4	0x9540
#घोषणा CYBERBLADEi7	0x8400
#घोषणा CYBERBLADEi7D	0x8420
#घोषणा CYBERBLADEi1	0x8500
#घोषणा CYBERBLADEi1D	0x8520
#घोषणा CYBERBLADEAi1	0x8600
#घोषणा CYBERBLADEAi1D	0x8620
#घोषणा CYBERBLADEXPAi1 0x8820
#घोषणा CYBERBLADEXPm8  0x9910
#घोषणा CYBERBLADEXPm16 0x9930

/* these defines are क्रम 'lcd' variable */
#घोषणा LCD_STRETCH	0
#घोषणा LCD_CENTER	1
#घोषणा LCD_BIOS	2

/* General Registers */
#घोषणा SPR	0x1F		/* Software Programming Register (videoram) */

/* 3C4 */
#घोषणा RevisionID 0x09
#घोषणा OldOrNew 0x0B	
#घोषणा ConfPort1 0x0C
#घोषणा ConfPort2 0x0C
#घोषणा NewMode2 0x0D
#घोषणा NewMode1 0x0E
#घोषणा Protection 0x11
#घोषणा MCLKLow 0x16
#घोषणा MCLKHigh 0x17
#घोषणा ClockLow 0x18
#घोषणा ClockHigh 0x19
#घोषणा SSetup 0x20
#घोषणा SKey 0x37
#घोषणा SPKey 0x57

/* 3x4 */
#घोषणा CRTCModuleTest 0x1E
#घोषणा FIFOControl 0x20
#घोषणा LinearAddReg 0x21
#घोषणा DRAMTiming 0x23
#घोषणा New32 0x23
#घोषणा RAMDACTiming 0x25
#घोषणा CRTHiOrd 0x27
#घोषणा AddColReg 0x29
#घोषणा InterfaceSel 0x2A
#घोषणा HorizOverflow 0x2B
#घोषणा GETest 0x2D
#घोषणा Perक्रमmance 0x2F
#घोषणा GraphEngReg 0x36
#घोषणा I2C 0x37
#घोषणा PixelBusReg 0x38
#घोषणा PCIReg 0x39
#घोषणा DRAMControl 0x3A
#घोषणा MiscContReg 0x3C
#घोषणा CursorXLow 0x40
#घोषणा CursorXHigh 0x41
#घोषणा CursorYLow 0x42
#घोषणा CursorYHigh 0x43
#घोषणा CursorLocLow 0x44
#घोषणा CursorLocHigh 0x45
#घोषणा CursorXOffset 0x46
#घोषणा CursorYOffset 0x47
#घोषणा CursorFG1 0x48
#घोषणा CursorFG2 0x49
#घोषणा CursorFG3 0x4A
#घोषणा CursorFG4 0x4B
#घोषणा CursorBG1 0x4C
#घोषणा CursorBG2 0x4D
#घोषणा CursorBG3 0x4E
#घोषणा CursorBG4 0x4F
#घोषणा CursorControl 0x50
#घोषणा PCIRetry 0x55
#घोषणा PreEndControl 0x56
#घोषणा PreEndFetch 0x57
#घोषणा PCIMaster 0x60
#घोषणा Enhancement0 0x62
#घोषणा NewEDO 0x64
#घोषणा TVपूर्णांकerface 0xC0
#घोषणा TVMode 0xC1
#घोषणा ClockControl 0xCF


/* 3CE */
#घोषणा MiscExtFunc 0x0F
#घोषणा PowerStatus 0x23
#घोषणा MiscIntContReg 0x2F
#घोषणा CyberControl 0x30
#घोषणा CyberEnhance 0x31
#घोषणा FPConfig     0x33
#घोषणा VertStretch  0x52
#घोषणा HorStretch   0x53
#घोषणा BiosMode     0x5c
#घोषणा BiosReg      0x5d

/* Graphics Engine */
#घोषणा STATUS	0x2120
#घोषणा OLDCMD	0x2124
#घोषणा DRAWFL	0x2128
#घोषणा OLDCLR	0x212C
#घोषणा OLDDST	0x2138
#घोषणा OLDSRC	0x213C
#घोषणा OLDDIM	0x2140
#घोषणा CMD	0x2144
#घोषणा ROP	0x2148
#घोषणा COLOR	0x2160
#घोषणा BGCOLOR	0x2164
#घोषणा SRC1	0x2100
#घोषणा SRC2	0x2104
#घोषणा DST1	0x2108
#घोषणा DST2	0x210C

#घोषणा ROP_S	0xCC
#घोषणा ROP_P	0xF0
#घोषणा ROP_X	0x66
