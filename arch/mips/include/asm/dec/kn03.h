<शैली गुरु>
/*
 * Hardware info about DECstation 5000/2x0 प्रणालीs (otherwise known as
 * 3max+) and DECप्रणाली 5900 प्रणालीs (otherwise known as bigmax) which
 * dअगरfer mechanically but are otherwise identical (both are known as
 * KN03).
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions
 * are by courtesy of Chris Fraser.
 * Copyright (C) 2000, 2002, 2003, 2005  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MIPS_DEC_KN03_H
#घोषणा __ASM_MIPS_DEC_KN03_H

#समावेश <यंत्र/dec/ecc.h>
#समावेश <यंत्र/dec/ioasic_addrs.h>

#घोषणा KN03_SLOT_BASE		0x1f800000

/*
 * CPU पूर्णांकerrupt bits.
 */
#घोषणा KN03_CPU_INR_HALT	6	/* HALT button */
#घोषणा KN03_CPU_INR_BUS	5	/* memory, I/O bus पढ़ो/ग_लिखो errors */
#घोषणा KN03_CPU_INR_RES_4	4	/* unused */
#घोषणा KN03_CPU_INR_RTC	3	/* DS1287 RTC */
#घोषणा KN03_CPU_INR_CASCADE	2	/* I/O ASIC cascade */

/*
 * I/O ASIC पूर्णांकerrupt bits.  Star marks denote non-IRQ status bits.
 */
#घोषणा KN03_IO_INR_3MAXP	15	/* (*) 3max+/bigmax ID */
#घोषणा KN03_IO_INR_NVRAM	14	/* (*) NVRAM clear jumper */
#घोषणा KN03_IO_INR_TC2		13	/* TURBOchannel slot #2 */
#घोषणा KN03_IO_INR_TC1		12	/* TURBOchannel slot #1 */
#घोषणा KN03_IO_INR_TC0		11	/* TURBOchannel slot #0 */
#घोषणा KN03_IO_INR_NRMOD	10	/* (*) NRMOD manufacturing jumper */
#घोषणा KN03_IO_INR_ASC		9	/* ASC (NCR53C94) SCSI */
#घोषणा KN03_IO_INR_LANCE	8	/* LANCE (Am7990) Ethernet */
#घोषणा KN03_IO_INR_SCC1	7	/* SCC (Z85C30) serial #1 */
#घोषणा KN03_IO_INR_SCC0	6	/* SCC (Z85C30) serial #0 */
#घोषणा KN03_IO_INR_RTC		5	/* DS1287 RTC */
#घोषणा KN03_IO_INR_PSU		4	/* घातer supply unit warning */
#घोषणा KN03_IO_INR_RES_3	3	/* unused */
#घोषणा KN03_IO_INR_ASC_DATA	2	/* SCSI data पढ़ोy (क्रम PIO) */
#घोषणा KN03_IO_INR_PBNC	1	/* ~HALT button debouncer */
#घोषणा KN03_IO_INR_PBNO	0	/* HALT button debouncer */


/*
 * Memory Control Register bits.
 */
#घोषणा KN03_MCR_RES_16		(0xffff<<16)	/* unused */
#घोषणा KN03_MCR_DIAGCHK	(1<<15)		/* diagn/norml ECC पढ़ोs */
#घोषणा KN03_MCR_DIAGGEN	(1<<14)		/* diagn/norml ECC ग_लिखोs */
#घोषणा KN03_MCR_CORRECT	(1<<13)		/* ECC correct/check */
#घोषणा KN03_MCR_RES_11		(0x3<<12)	/* unused */
#घोषणा KN03_MCR_BNK32M		(1<<10)		/* 32M/8M stride */
#घोषणा KN03_MCR_RES_7		(0x7<<7)	/* unused */
#घोषणा KN03_MCR_CHECK		(0x7f<<0)	/* diagnostic check bits */

/*
 * I/O ASIC System Support Register bits.
 */
#घोषणा KN03_IO_SSR_TXDIS1	(1<<14)		/* SCC1 transmit disable */
#घोषणा KN03_IO_SSR_TXDIS0	(1<<13)		/* SCC0 transmit disable */
#घोषणा KN03_IO_SSR_RES_12	(1<<12)		/* unused */

#घोषणा KN03_IO_SSR_LEDS	(0xff<<0)	/* ~diagnostic LEDs */

#पूर्ण_अगर /* __ASM_MIPS_DEC_KN03_H */
