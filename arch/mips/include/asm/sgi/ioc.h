<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * ioc.h: Definitions क्रम SGI I/O Controller
 *
 * Copyright (C) 1996 David S. Miller
 * Copyright (C) 1997, 1998, 1999, 2000 Ralf Baechle
 * Copyright (C) 2001, 2003 Ladislav Michl
 */

#अगर_अघोषित _SGI_IOC_H
#घोषणा _SGI_IOC_H

#समावेश <linux/types.h>
#समावेश <यंत्र/sgi/pi1.h>

/*
 * All रेजिस्टरs are 8-bit wide aligned on 32-bit boundary. Bad things
 * happen अगर you try word access them. You have been warned.
 */

काष्ठा sgioc_uart_regs अणु
	u8 _ctrl1[3];
	अस्थिर u8 ctrl1;
	u8 _data1[3];
	अस्थिर u8 data1;
	u8 _ctrl2[3];
	अस्थिर u8 ctrl2;
	u8 _data2[3];
	अस्थिर u8 data2;
पूर्ण;

काष्ठा sgioc_keyb_regs अणु
	u8 _data[3];
	अस्थिर u8 data;
	u8 _command[3];
	अस्थिर u8 command;
पूर्ण;

काष्ठा sgपूर्णांक_regs अणु
	u8 _istat0[3];
	अस्थिर u8 istat0;		/* Interrupt status zero */
#घोषणा SGINT_ISTAT0_FFULL	0x01
#घोषणा SGINT_ISTAT0_SCSI0	0x02
#घोषणा SGINT_ISTAT0_SCSI1	0x04
#घोषणा SGINT_ISTAT0_ENET	0x08
#घोषणा SGINT_ISTAT0_GFXDMA	0x10
#घोषणा SGINT_ISTAT0_PPORT	0x20
#घोषणा SGINT_ISTAT0_HPC2	0x40
#घोषणा SGINT_ISTAT0_LIO2	0x80
	u8 _imask0[3];
	अस्थिर u8 imask0;		/* Interrupt mask zero */
	u8 _istat1[3];
	अस्थिर u8 istat1;		/* Interrupt status one */
#घोषणा SGINT_ISTAT1_ISDNI	0x01
#घोषणा SGINT_ISTAT1_PWR	0x02
#घोषणा SGINT_ISTAT1_ISDNH	0x04
#घोषणा SGINT_ISTAT1_LIO3	0x08
#घोषणा SGINT_ISTAT1_HPC3	0x10
#घोषणा SGINT_ISTAT1_AFAIL	0x20
#घोषणा SGINT_ISTAT1_VIDEO	0x40
#घोषणा SGINT_ISTAT1_GIO2	0x80
	u8 _imask1[3];
	अस्थिर u8 imask1;		/* Interrupt mask one */
	u8 _vmeistat[3];
	अस्थिर u8 vmeistat;		/* VME पूर्णांकerrupt status */
	u8 _cmeimask0[3];
	अस्थिर u8 cmeimask0;		/* VME पूर्णांकerrupt mask zero */
	u8 _cmeimask1[3];
	अस्थिर u8 cmeimask1;		/* VME पूर्णांकerrupt mask one */
	u8 _cmepol[3];
	अस्थिर u8 cmepol;		/* VME polarity */
	u8 _tclear[3];
	अस्थिर u8 tclear;
	u8 _errstat[3];
	अस्थिर u8 errstat;	/* Error status reg, reserved on INT2 */
	u32 _unused0[2];
	u8 _tcnt0[3];
	अस्थिर u8 tcnt0;		/* counter 0 */
	u8 _tcnt1[3];
	अस्थिर u8 tcnt1;		/* counter 1 */
	u8 _tcnt2[3];
	अस्थिर u8 tcnt2;		/* counter 2 */
	u8 _tcword[3];
	अस्थिर u8 tcword;		/* control word */
#घोषणा SGINT_TCWORD_BCD	0x01	/* Use BCD mode क्रम counters */
#घोषणा SGINT_TCWORD_MMASK	0x0e	/* Mode biपंचांगask. */
#घोषणा SGINT_TCWORD_MITC	0x00	/* IRQ on terminal count (करोesn't work) */
#घोषणा SGINT_TCWORD_MOS	0x02	/* One-shot IRQ mode. */
#घोषणा SGINT_TCWORD_MRGEN	0x04	/* Normal rate generation */
#घोषणा SGINT_TCWORD_MSWGEN	0x06	/* Square wave generator mode */
#घोषणा SGINT_TCWORD_MSWST	0x08	/* Software strobe */
#घोषणा SGINT_TCWORD_MHWST	0x0a	/* Hardware strobe */
#घोषणा SGINT_TCWORD_CMASK	0x30	/* Command mask */
#घोषणा SGINT_TCWORD_CLAT	0x00	/* Latch command */
#घोषणा SGINT_TCWORD_CLSB	0x10	/* LSB पढ़ो/ग_लिखो */
#घोषणा SGINT_TCWORD_CMSB	0x20	/* MSB पढ़ो/ग_लिखो */
#घोषणा SGINT_TCWORD_CALL	0x30	/* Full counter पढ़ो/ग_लिखो */
#घोषणा SGINT_TCWORD_CNT0	0x00	/* Select counter zero */
#घोषणा SGINT_TCWORD_CNT1	0x40	/* Select counter one */
#घोषणा SGINT_TCWORD_CNT2	0x80	/* Select counter two */
#घोषणा SGINT_TCWORD_CRBCK	0xc0	/* Readback command */
पूर्ण;

/*
 * The समयr is the good old 8254.  Unlike in PCs it's घड़ीed at exactly 1MHz
 */
#घोषणा SGINT_TIMER_CLOCK	1000000

/*
 * This is the स्थिरant we're using क्रम calibrating the counter.
 */
#घोषणा SGINT_TCSAMP_COUNTER	((SGINT_TIMER_CLOCK / HZ) + 255)

/* We need software copies of these because they are ग_लिखो only. */
बाह्य u8 sgi_ioc_reset, sgi_ioc_ग_लिखो;

काष्ठा sgioc_regs अणु
	काष्ठा pi1_regs pport;
	u32 _unused0[2];
	काष्ठा sgioc_uart_regs uart;
	काष्ठा sgioc_keyb_regs kbdmouse;
	u8 _gcsel[3];
	अस्थिर u8 gcsel;
	u8 _genctrl[3];
	अस्थिर u8 genctrl;
	u8 _panel[3];
	अस्थिर u8 panel;
#घोषणा SGIOC_PANEL_POWERON	0x01
#घोषणा SGIOC_PANEL_POWERINTR	0x02
#घोषणा SGIOC_PANEL_VOLDNINTR	0x10
#घोषणा SGIOC_PANEL_VOLDNHOLD	0x20
#घोषणा SGIOC_PANEL_VOLUPINTR	0x40
#घोषणा SGIOC_PANEL_VOLUPHOLD	0x80
	u32 _unused1;
	u8 _sysid[3];
	अस्थिर u8 sysid;
#घोषणा SGIOC_SYSID_FULLHOUSE	0x01
#घोषणा SGIOC_SYSID_BOARDREV(x) (((x) & 0x1e) >> 1)
#घोषणा SGIOC_SYSID_CHIPREV(x)	(((x) & 0xe0) >> 5)
	u32 _unused2;
	u8 _पढ़ो[3];
	अस्थिर u8 पढ़ो;
	u32 _unused3;
	u8 _dmasel[3];
	अस्थिर u8 dmasel;
#घोषणा SGIOC_DMASEL_SCLK10MHZ	0x00	/* use 10MHZ serial घड़ी */
#घोषणा SGIOC_DMASEL_ISDNB	0x01	/* enable isdn B */
#घोषणा SGIOC_DMASEL_ISDNA	0x02	/* enable isdn A */
#घोषणा SGIOC_DMASEL_PPORT	0x04	/* use parallel DMA */
#घोषणा SGIOC_DMASEL_SCLK667MHZ 0x10	/* use 6.67MHZ serial घड़ी */
#घोषणा SGIOC_DMASEL_SCLKEXT	0x20	/* use बाह्यal serial घड़ी */
	u32 _unused4;
	u8 _reset[3];
	अस्थिर u8 reset;
#घोषणा SGIOC_RESET_PPORT	0x01	/* 0=parport reset, 1=nornal */
#घोषणा SGIOC_RESET_KBDMOUSE	0x02	/* 0=kbdmouse reset, 1=normal */
#घोषणा SGIOC_RESET_EISA	0x04	/* 0=eisa reset, 1=normal */
#घोषणा SGIOC_RESET_ISDN	0x08	/* 0=isdn reset, 1=normal */
#घोषणा SGIOC_RESET_LC0OFF	0x10	/* guiness: turn led off (red, अन्यथा green) */
#घोषणा SGIOC_RESET_LC1OFF	0x20	/* guiness: turn led off (green, अन्यथा amber) */
	u32 _unused5;
	u8 _ग_लिखो[3];
	अस्थिर u8 ग_लिखो;
#घोषणा SGIOC_WRITE_NTHRESH	0x01	/* use 4.5db threshold */
#घोषणा SGIOC_WRITE_TPSPEED	0x02	/* use 100ohm TP speed */
#घोषणा SGIOC_WRITE_EPSEL	0x04	/* क्रमce cable mode: 1=AUI 0=TP */
#घोषणा SGIOC_WRITE_EASEL	0x08	/* 1=स्वतःselect 0=manual cable selection */
#घोषणा SGIOC_WRITE_U1AMODE	0x10	/* 1=PC 0=MAC UART mode */
#घोषणा SGIOC_WRITE_U0AMODE	0x20	/* 1=PC 0=MAC UART mode */
#घोषणा SGIOC_WRITE_MLO		0x40	/* 1=4.75V 0=+5V */
#घोषणा SGIOC_WRITE_MHI		0x80	/* 1=5.25V 0=+5V */
	u32 _unused6;
	काष्ठा sgपूर्णांक_regs पूर्णांक3;
	u32 _unused7[16];
	अस्थिर u32 extio;		/* FullHouse only */
#घोषणा EXTIO_S0_IRQ_3		0x8000	/* S0: vid.vsync */
#घोषणा EXTIO_S0_IRQ_2		0x4000	/* S0: gfx.fअगरofull */
#घोषणा EXTIO_S0_IRQ_1		0x2000	/* S0: gfx.पूर्णांक */
#घोषणा EXTIO_S0_RETRACE	0x1000
#घोषणा EXTIO_SG_IRQ_3		0x0800	/* SG: vid.vsync */
#घोषणा EXTIO_SG_IRQ_2		0x0400	/* SG: gfx.fअगरofull */
#घोषणा EXTIO_SG_IRQ_1		0x0200	/* SG: gfx.पूर्णांक */
#घोषणा EXTIO_SG_RETRACE	0x0100
#घोषणा EXTIO_GIO_33MHZ		0x0080
#घोषणा EXTIO_EISA_BUSERR	0x0040
#घोषणा EXTIO_MC_BUSERR		0x0020
#घोषणा EXTIO_HPC3_BUSERR	0x0010
#घोषणा EXTIO_S0_STAT_1		0x0008
#घोषणा EXTIO_S0_STAT_0		0x0004
#घोषणा EXTIO_SG_STAT_1		0x0002
#घोषणा EXTIO_SG_STAT_0		0x0001
पूर्ण;

बाह्य काष्ठा sgioc_regs *sgioc;
बाह्य काष्ठा sgपूर्णांक_regs *sgपूर्णांक;

#पूर्ण_अगर
