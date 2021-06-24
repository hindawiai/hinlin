<शैली गुरु>
/*
 * Hardware info about DECstation 5000/200 प्रणालीs (otherwise known as
 * 3max or KN02).
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions
 * are by courtesy of Chris Fraser.
 * Copyright (C) 2002, 2003, 2005  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MIPS_DEC_KN02_H
#घोषणा __ASM_MIPS_DEC_KN02_H

#घोषणा KN02_SLOT_BASE	0x1fc00000
#घोषणा KN02_SLOT_SIZE	0x00080000

/*
 * Address ranges decoded by the "system slot" logic क्रम onboard devices.
 */
#घोषणा KN02_SYS_ROM	(0*KN02_SLOT_SIZE)	/* प्रणाली board ROM */
#घोषणा KN02_RES_1	(1*KN02_SLOT_SIZE)	/* unused */
#घोषणा KN02_CHKSYN	(2*KN02_SLOT_SIZE)	/* ECC syndrome */
#घोषणा KN02_ERRADDR	(3*KN02_SLOT_SIZE)	/* bus error address */
#घोषणा KN02_DZ11	(4*KN02_SLOT_SIZE)	/* DZ11 (DC7085) serial */
#घोषणा KN02_RTC	(5*KN02_SLOT_SIZE)	/* DS1287 RTC */
#घोषणा KN02_CSR	(6*KN02_SLOT_SIZE)	/* प्रणाली ctrl & status reg */
#घोषणा KN02_SYS_ROM_7	(7*KN02_SLOT_SIZE)	/* प्रणाली board ROM (alias) */


/*
 * System Control & Status Register bits.
 */
#घोषणा KN02_CSR_RES_28		(0xf<<28)	/* unused */
#घोषणा KN02_CSR_PSU		(1<<27)		/* घातer supply unit warning */
#घोषणा KN02_CSR_NVRAM		(1<<26)		/* ~NVRAM clear jumper */
#घोषणा KN02_CSR_REFEVEN	(1<<25)		/* mem refresh bank toggle */
#घोषणा KN02_CSR_NRMOD		(1<<24)		/* ~NRMOD manufact. jumper */
#घोषणा KN02_CSR_IOINTEN	(0xff<<16)	/* IRQ mask bits */
#घोषणा KN02_CSR_DIAGCHK	(1<<15)		/* diagn/norml ECC पढ़ोs */
#घोषणा KN02_CSR_DIAGGEN	(1<<14)		/* diagn/norml ECC ग_लिखोs */
#घोषणा KN02_CSR_CORRECT	(1<<13)		/* ECC correct/check */
#घोषणा KN02_CSR_LEDIAG		(1<<12)		/* ECC diagn. latch strobe */
#घोषणा KN02_CSR_TXDIS		(1<<11)		/* DZ11 transmit disable */
#घोषणा KN02_CSR_BNK32M		(1<<10)		/* 32M/8M stride */
#घोषणा KN02_CSR_DIAGDN		(1<<9)		/* DIAGDN manufact. jumper */
#घोषणा KN02_CSR_BAUD38		(1<<8)		/* DZ11 38/19kbps ext. rate */
#घोषणा KN02_CSR_IOINT		(0xff<<0)	/* IRQ status bits (r/o) */
#घोषणा KN02_CSR_LEDS		(0xff<<0)	/* ~diagnostic LEDs (w/o) */


/*
 * CPU पूर्णांकerrupt bits.
 */
#घोषणा KN02_CPU_INR_RES_6	6	/* unused */
#घोषणा KN02_CPU_INR_BUS	5	/* memory, I/O bus पढ़ो/ग_लिखो errors */
#घोषणा KN02_CPU_INR_RES_4	4	/* unused */
#घोषणा KN02_CPU_INR_RTC	3	/* DS1287 RTC */
#घोषणा KN02_CPU_INR_CASCADE	2	/* CSR cascade */

/*
 * CSR पूर्णांकerrupt bits.
 */
#घोषणा KN02_CSR_INR_DZ11	7	/* DZ11 (DC7085) serial */
#घोषणा KN02_CSR_INR_LANCE	6	/* LANCE (Am7990) Ethernet */
#घोषणा KN02_CSR_INR_ASC	5	/* ASC (NCR53C94) SCSI */
#घोषणा KN02_CSR_INR_RES_4	4	/* unused */
#घोषणा KN02_CSR_INR_RES_3	3	/* unused */
#घोषणा KN02_CSR_INR_TC2	2	/* TURBOchannel slot #2 */
#घोषणा KN02_CSR_INR_TC1	1	/* TURBOchannel slot #1 */
#घोषणा KN02_CSR_INR_TC0	0	/* TURBOchannel slot #0 */


#घोषणा KN02_IRQ_BASE		8	/* first IRQ asचिन्हित to CSR */
#घोषणा KN02_IRQ_LINES		8	/* number of CSR पूर्णांकerrupts */

#घोषणा KN02_IRQ_NR(n)		((n) + KN02_IRQ_BASE)
#घोषणा KN02_IRQ_MASK(n)	(1 << (n))
#घोषणा KN02_IRQ_ALL		0xff


#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

बाह्य u32 cached_kn02_csr;
बाह्य व्योम init_kn02_irqs(पूर्णांक base);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MIPS_DEC_KN02_H */
