<शैली गुरु>
/*-*- linux-c -*-
 *  linux/drivers/video/i810_regs.h -- Intel 810/815 Register List
 *
 *      Copyright (C) 2001 Antonino Daplas<adaplas@pol.net>
 *      All Rights Reserved      
 *
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */


/*
 * Intel 810 Chipset Family PRM 15 3.1 
 * GC Register Memory Address Map 
 *
 * Based on:
 * Intel (R) 810 Chipset Family 
 * Programmer s Reference Manual 
 * November 1999 
 * Revision 1.0 
 * Order Number: 298026-001 R
 *
 * All GC रेजिस्टरs are memory-mapped. In addition, the VGA and extended VGA रेजिस्टरs 
 * are I/O mapped. 
 */
 
#अगर_अघोषित __I810_REGS_H__
#घोषणा __I810_REGS_H__

/*  Inकाष्ठाion and Interrupt Control Registers (01000h 02FFFh) */
#घोषणा FENCE                 0x02000                
#घोषणा PGTBL_CTL             0x02020 
#घोषणा PGTBL_ER              0x02024               
#घोषणा    LRING              0x02030
#घोषणा    IRING              0x02040
#घोषणा HWS_PGA               0x02080 
#घोषणा IPEIR                 0x02088
#घोषणा IPEHR                 0x0208C 
#घोषणा INSTDONE              0x02090 
#घोषणा NOPID                 0x02094
#घोषणा HWSTAM                0x02098 
#घोषणा IER                   0x020A0
#घोषणा IIR                   0x020A4
#घोषणा IMR                   0x020A8 
#घोषणा ISR                   0x020AC 
#घोषणा EIR                   0x020B0 
#घोषणा EMR                   0x020B4 
#घोषणा ESR                   0x020B8 
#घोषणा INSTPM                0x020C0
#घोषणा INSTPS                0x020C4 
#घोषणा BBP_PTR               0x020C8 
#घोषणा ABB_SRT               0x020CC
#घोषणा ABB_END               0x020D0
#घोषणा DMA_FADD              0x020D4 
#घोषणा FW_BLC                0x020D8
#घोषणा MEM_MODE              0x020DC        

/*  Memory Control Registers (03000h 03FFFh) */
#घोषणा DRT                   0x03000
#घोषणा DRAMCL                0x03001
#घोषणा DRAMCH                0x03002
 

/* Span Cursor Registers (04000h 04FFFh) */
#घोषणा UI_SC_CTL             0x04008 

/* I/O Control Registers (05000h 05FFFh) */
#घोषणा HVSYNC                0x05000 
#घोषणा GPIOA                 0x05010
#घोषणा GPIOB                 0x05014 
#घोषणा GPIOC                 0x0501C

/* Clock Control and Power Management Registers (06000h 06FFFh) */
#घोषणा DCLK_0D               0x06000
#घोषणा DCLK_1D               0x06004
#घोषणा DCLK_2D               0x06008
#घोषणा LCD_CLKD              0x0600C
#घोषणा DCLK_0DS              0x06010
#घोषणा PWR_CLKC              0x06014

/* Graphics Translation Table Range Definition (10000h 1FFFFh) */
#घोषणा GTT                   0x10000  

/*  Overlay Registers (30000h 03FFFFh) */
#घोषणा OVOADDR               0x30000
#घोषणा DOVOSTA               0x30008
#घोषणा GAMMA                 0x30010
#घोषणा OBUF_0Y               0x30100
#घोषणा OBUF_1Y               0x30104
#घोषणा OBUF_0U               0x30108
#घोषणा OBUF_0V               0x3010C
#घोषणा OBUF_1U               0x30110
#घोषणा OBUF_1V               0x30114 
#घोषणा OVOSTRIDE             0x30118
#घोषणा YRGB_VPH              0x3011C
#घोषणा UV_VPH                0x30120
#घोषणा HORZ_PH               0x30124
#घोषणा INIT_PH               0x30128
#घोषणा DWINPOS               0x3012C 
#घोषणा DWINSZ                0x30130
#घोषणा SWID                  0x30134
#घोषणा SWIDQW                0x30138
#घोषणा SHEIGHT               0x3013F
#घोषणा YRGBSCALE             0x30140 
#घोषणा UVSCALE               0x30144
#घोषणा OVOCLRCO              0x30148
#घोषणा OVOCLRC1              0x3014C
#घोषणा DCLRKV                0x30150
#घोषणा DLCRKM                0x30154
#घोषणा SCLRKVH               0x30158
#घोषणा SCLRKVL               0x3015C
#घोषणा SCLRKM                0x30160
#घोषणा OVOCONF               0x30164
#घोषणा OVOCMD                0x30168
#घोषणा AWINPOS               0x30170
#घोषणा AWINZ                 0x30174

/*  BLT Engine Status (40000h 4FFFFh) (Software Debug) */
#घोषणा BR00                  0x40000
#घोषणा BRO1                  0x40004
#घोषणा BR02                  0x40008
#घोषणा BR03                  0x4000C
#घोषणा BR04                  0x40010
#घोषणा BR05                  0x40014
#घोषणा BR06                  0x40018
#घोषणा BR07                  0x4001C
#घोषणा BR08                  0x40020
#घोषणा BR09                  0x40024
#घोषणा BR10                  0x40028
#घोषणा BR11                  0x4002C
#घोषणा BR12                  0x40030
#घोषणा BR13                  0x40034
#घोषणा BR14                  0x40038
#घोषणा BR15                  0x4003C
#घोषणा BR16                  0x40040
#घोषणा BR17                  0x40044
#घोषणा BR18                  0x40048
#घोषणा BR19                  0x4004C
#घोषणा SSLADD                0x40074
#घोषणा DSLH                  0x40078
#घोषणा DSLRADD               0x4007C


/* LCD/TV-Out and HW DVD Registers (60000h 6FFFFh) */
/* LCD/TV-Out */
#घोषणा HTOTAL                0x60000
#घोषणा HBLANK                0x60004
#घोषणा HSYNC                 0x60008
#घोषणा VTOTAL                0x6000C
#घोषणा VBLANK                0x60010
#घोषणा VSYNC                 0x60014
#घोषणा LCDTV_C               0x60018
#घोषणा OVRACT                0x6001C
#घोषणा BCLRPAT               0x60020

/*  Display and Cursor Control Registers (70000h 7FFFFh) */
#घोषणा DISP_SL               0x70000
#घोषणा DISP_SLC              0x70004
#घोषणा PIXCONF               0x70008
#घोषणा PIXCONF1              0x70009
#घोषणा BLTCNTL               0x7000C
#घोषणा SWF                   0x70014
#घोषणा DPLYBASE              0x70020
#घोषणा DPLYSTAS              0x70024
#घोषणा CURCNTR               0x70080
#घोषणा CURBASE               0x70084
#घोषणा CURPOS                0x70088


/* VGA Registers */

/* SMRAM Registers */
#घोषणा SMRAM                 0x10

/* Graphics Control Registers */
#घोषणा GR_INDEX              0x3CE
#घोषणा GR_DATA               0x3CF

#घोषणा GR10                  0x10
#घोषणा GR11                  0x11

/* CRT Controller Registers */
#घोषणा CR_INDEX_MDA          0x3B4
#घोषणा CR_INDEX_CGA          0x3D4
#घोषणा CR_DATA_MDA           0x3B5
#घोषणा CR_DATA_CGA           0x3D5

#घोषणा CR30                  0x30
#घोषणा CR31                  0x31
#घोषणा CR32                  0x32
#घोषणा CR33                  0x33
#घोषणा CR35                  0x35
#घोषणा CR39                  0x39
#घोषणा CR40                  0x40
#घोषणा CR41                  0x41
#घोषणा CR42                  0x42
#घोषणा CR70                  0x70
#घोषणा CR80                  0x80 
#घोषणा CR81                  0x82

/* Extended VGA Registers */

/* General Control and Status Registers */
#घोषणा ST00                  0x3C2
#घोषणा ST01_MDA              0x3BA
#घोषणा ST01_CGA              0x3DA
#घोषणा FRC_READ              0x3CA
#घोषणा FRC_WRITE_MDA         0x3BA
#घोषणा FRC_WRITE_CGA         0x3DA
#घोषणा MSR_READ              0x3CC
#घोषणा MSR_WRITE             0x3C2

/* Sequencer Registers */
#घोषणा SR_INDEX              0x3C4
#घोषणा SR_DATA               0x3C5

#घोषणा SR01                  0x01
#घोषणा SR02                  0x02
#घोषणा SR03                  0x03
#घोषणा SR04                  0x04
#घोषणा SR07                  0x07

/* Graphics Controller Registers */
#घोषणा GR00                  0x00   
#घोषणा GR01                  0x01
#घोषणा GR02                  0x02
#घोषणा GR03                  0x03
#घोषणा GR04                  0x04
#घोषणा GR05                  0x05
#घोषणा GR06                  0x06
#घोषणा GR07                  0x07
#घोषणा GR08                  0x08  

/* Attribute Controller Registers */
#घोषणा ATTR_WRITE              0x3C0
#घोषणा ATTR_READ               0x3C1

/* VGA Color Palette Registers */

/* CLUT */
#घोषणा CLUT_DATA             0x3C9        /* DACDATA */
#घोषणा CLUT_INDEX_READ       0x3C7        /* DACRX */
#घोषणा CLUT_INDEX_WRITE      0x3C8        /* DACWX */
#घोषणा DACMASK               0x3C6

/* CRT Controller Registers */
#घोषणा CR00                  0x00
#घोषणा CR01                  0x01
#घोषणा CR02                  0x02
#घोषणा CR03                  0x03
#घोषणा CR04                  0x04
#घोषणा CR05                  0x05
#घोषणा CR06                  0x06
#घोषणा CR07                  0x07
#घोषणा CR08                  0x08
#घोषणा CR09                  0x09
#घोषणा CR0A                  0x0A
#घोषणा CR0B                  0x0B
#घोषणा CR0C                  0x0C
#घोषणा CR0D                  0x0D
#घोषणा CR0E                  0x0E
#घोषणा CR0F                  0x0F
#घोषणा CR10                  0x10
#घोषणा CR11                  0x11
#घोषणा CR12                  0x12
#घोषणा CR13                  0x13
#घोषणा CR14                  0x14
#घोषणा CR15                  0x15
#घोषणा CR16                  0x16
#घोषणा CR17                  0x17
#घोषणा CR18                  0x18

#पूर्ण_अगर /* __I810_REGS_H__ */
