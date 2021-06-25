<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SE7780_H
#घोषणा __ASM_SH_SE7780_H

/*
 * linux/include/यंत्र-sh/se7780.h
 *
 * Copyright (C) 2006,2007  Nobuhiro Iwamatsu
 *
 * Hitachi UL SolutionEngine 7780 Support.
 */
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <यंत्र/addrspace.h>

/* Box specअगरic addresses.  */
#घोषणा SE_AREA0_WIDTH	4		/* Area0: 32bit */
#घोषणा PA_ROM		0xa0000000	/* EPROM */
#घोषणा PA_ROM_SIZE	0x00400000	/* EPROM size 4M byte */
#घोषणा PA_FROM		0xa1000000	/* Flash-ROM */
#घोषणा PA_FROM_SIZE	0x01000000	/* Flash-ROM size 16M byte */
#घोषणा PA_EXT1		0xa4000000
#घोषणा PA_EXT1_SIZE	0x04000000
#घोषणा PA_SM501	PA_EXT1		/* Graphic IC (SM501) */
#घोषणा PA_SM501_SIZE	PA_EXT1_SIZE	/* Graphic IC (SM501) */
#घोषणा PA_SDRAM	0xa8000000	/* DDR-SDRAM(Area2/3) 128MB */
#घोषणा PA_SDRAM_SIZE	0x08000000

#घोषणा PA_EXT4		0xb0000000
#घोषणा PA_EXT4_SIZE	0x04000000
#घोषणा PA_EXT_FLASH	PA_EXT4		/* Expansion Flash-ROM */

#घोषणा PA_PERIPHERAL	PA_AREA6_IO	/* SW6-6=ON */

#घोषणा PA_LAN		(PA_PERIPHERAL + 0)		/* SMC LAN91C111 */
#घोषणा PA_LED_DISP	(PA_PERIPHERAL + 0x02000000)	/* 8words LED Display */
#घोषणा DISP_CHAR_RAM	(7 << 3)
#घोषणा DISP_SEL0_ADDR	(DISP_CHAR_RAM + 0)
#घोषणा DISP_SEL1_ADDR	(DISP_CHAR_RAM + 1)
#घोषणा DISP_SEL2_ADDR	(DISP_CHAR_RAM + 2)
#घोषणा DISP_SEL3_ADDR	(DISP_CHAR_RAM + 3)
#घोषणा DISP_SEL4_ADDR	(DISP_CHAR_RAM + 4)
#घोषणा DISP_SEL5_ADDR	(DISP_CHAR_RAM + 5)
#घोषणा DISP_SEL6_ADDR	(DISP_CHAR_RAM + 6)
#घोषणा DISP_SEL7_ADDR	(DISP_CHAR_RAM + 7)

#घोषणा DISP_UDC_RAM	(5 << 3)
#घोषणा PA_FPGA		(PA_PERIPHERAL + 0x03000000) /* FPGA base address */

/* FPGA रेजिस्टर address and bit */
#घोषणा FPGA_SFTRST		(PA_FPGA + 0)	/* Soft reset रेजिस्टर */
#घोषणा FPGA_INTMSK1		(PA_FPGA + 2)	/* Interrupt Mask रेजिस्टर 1 */
#घोषणा FPGA_INTMSK2		(PA_FPGA + 4)	/* Interrupt Mask रेजिस्टर 2 */
#घोषणा FPGA_INTSEL1		(PA_FPGA + 6)	/* Interrupt select रेजिस्टर 1 */
#घोषणा FPGA_INTSEL2		(PA_FPGA + 8)	/* Interrupt select रेजिस्टर 2 */
#घोषणा FPGA_INTSEL3		(PA_FPGA + 10)	/* Interrupt select रेजिस्टर 3 */
#घोषणा FPGA_PCI_INTSEL1	(PA_FPGA + 12)	/* PCI Interrupt select रेजिस्टर 1 */
#घोषणा FPGA_PCI_INTSEL2	(PA_FPGA + 14)	/* PCI Interrupt select रेजिस्टर 2 */
#घोषणा FPGA_INTSET		(PA_FPGA + 16)	/* IRQ/IRL select रेजिस्टर */
#घोषणा FPGA_INTSTS1		(PA_FPGA + 18)	/* Interrupt status रेजिस्टर 1 */
#घोषणा FPGA_INTSTS2		(PA_FPGA + 20)	/* Interrupt status रेजिस्टर 2 */
#घोषणा FPGA_REQSEL		(PA_FPGA + 22)	/* REQ/GNT select रेजिस्टर */
#घोषणा FPGA_DBG_LED		(PA_FPGA + 32)	/* Debug LED(D-LED[8:1] */
#घोषणा PA_LED			FPGA_DBG_LED
#घोषणा FPGA_IVDRID		(PA_FPGA + 36)	/* iVDR ID Register */
#घोषणा FPGA_IVDRPW		(PA_FPGA + 38)	/* iVDR Power ON Register */
#घोषणा FPGA_MMCID		(PA_FPGA + 40)	/* MMC ID Register */

/* FPGA INTSEL position */
/* INTSEL1 */
#घोषणा IRQPOS_SMC91CX          (0 * 4)
#घोषणा IRQPOS_SM501            (1 * 4)
/* INTSEL2 */
#घोषणा IRQPOS_EXTINT1          (0 * 4)
#घोषणा IRQPOS_EXTINT2          (1 * 4)
#घोषणा IRQPOS_EXTINT3          (2 * 4)
#घोषणा IRQPOS_EXTINT4          (3 * 4)
/* INTSEL3 */
#घोषणा IRQPOS_PCCPW            (0 * 4)

/* IDE पूर्णांकerrupt */
#घोषणा IRQ_IDE0                evt2irq(0xa60) /* iVDR */

/* SMC पूर्णांकerrupt */
#घोषणा SMC_IRQ                 evt2irq(0x300)

/* SM501 पूर्णांकerrupt */
#घोषणा SM501_IRQ               evt2irq(0x200)

/* पूर्णांकerrupt pin */
#घोषणा IRQPIN_EXTINT1          0 /* IRQ0 pin */
#घोषणा IRQPIN_EXTINT2          1 /* IRQ1 pin */
#घोषणा IRQPIN_EXTINT3          2 /* IRQ2 pin */
#घोषणा IRQPIN_SMC91CX          3 /* IRQ3 pin */
#घोषणा IRQPIN_EXTINT4          4 /* IRQ4 pin */
#घोषणा IRQPIN_PCC0             5 /* IRQ5 pin */
#घोषणा IRQPIN_PCC2             6 /* IRQ6 pin */
#घोषणा IRQPIN_SM501            7 /* IRQ7 pin */
#घोषणा IRQPIN_PCCPW            7 /* IRQ7 pin */

/* arch/sh/boards/se/7780/irq.c */
व्योम init_se7780_IRQ(व्योम);

#घोषणा __IO_PREFIX		se7780
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_SE7780_H */
