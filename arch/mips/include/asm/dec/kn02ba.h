<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/dec/kn02ba.h
 *
 *	DECstation 5000/1xx (3min or KN02-BA) definitions.
 *
 *	Copyright (C) 2002, 2003  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MIPS_DEC_KN02BA_H
#घोषणा __ASM_MIPS_DEC_KN02BA_H

#समावेश <यंत्र/dec/kn02xa.h>		/* For common definitions. */

/*
 * CPU पूर्णांकerrupt bits.
 */
#घोषणा KN02BA_CPU_INR_HALT	6	/* HALT button */
#घोषणा KN02BA_CPU_INR_CASCADE	5	/* I/O ASIC cascade */
#घोषणा KN02BA_CPU_INR_TC2	4	/* TURBOchannel slot #2 */
#घोषणा KN02BA_CPU_INR_TC1	3	/* TURBOchannel slot #1 */
#घोषणा KN02BA_CPU_INR_TC0	2	/* TURBOchannel slot #0 */

/*
 * I/O ASIC पूर्णांकerrupt bits.  Star marks denote non-IRQ status bits.
 */
#घोषणा KN02BA_IO_INR_RES_15	15	/* unused */
#घोषणा KN02BA_IO_INR_NVRAM	14	/* (*) NVRAM clear jumper */
#घोषणा KN02BA_IO_INR_RES_13	13	/* unused */
#घोषणा KN02BA_IO_INR_BUS	12	/* memory, I/O bus पढ़ो/ग_लिखो errors */
#घोषणा KN02BA_IO_INR_RES_11	11	/* unused */
#घोषणा KN02BA_IO_INR_NRMOD	10	/* (*) NRMOD manufacturing jumper */
#घोषणा KN02BA_IO_INR_ASC	9	/* ASC (NCR53C94) SCSI */
#घोषणा KN02BA_IO_INR_LANCE	8	/* LANCE (Am7990) Ethernet */
#घोषणा KN02BA_IO_INR_SCC1	7	/* SCC (Z85C30) serial #1 */
#घोषणा KN02BA_IO_INR_SCC0	6	/* SCC (Z85C30) serial #0 */
#घोषणा KN02BA_IO_INR_RTC	5	/* DS1287 RTC */
#घोषणा KN02BA_IO_INR_PSU	4	/* घातer supply unit warning */
#घोषणा KN02BA_IO_INR_RES_3	3	/* unused */
#घोषणा KN02BA_IO_INR_ASC_DATA	2	/* SCSI data पढ़ोy (क्रम PIO) */
#घोषणा KN02BA_IO_INR_PBNC	1	/* ~HALT button debouncer */
#घोषणा KN02BA_IO_INR_PBNO	0	/* HALT button debouncer */


/*
 * Memory Error Register bits.
 */
#घोषणा KN02BA_MER_RES_27	(1<<27)		/* unused */

/*
 * Memory Size Register bits.
 */
#घोषणा KN02BA_MSR_RES_17	(0x3ff<<17)	/* unused */

/*
 * I/O ASIC System Support Register bits.
 */
#घोषणा KN02BA_IO_SSR_TXDIS1	(1<<14)		/* SCC1 transmit disable */
#घोषणा KN02BA_IO_SSR_TXDIS0	(1<<13)		/* SCC0 transmit disable */
#घोषणा KN02BA_IO_SSR_RES_12	(1<<12)		/* unused */

#घोषणा KN02BA_IO_SSR_LEDS	(0xff<<0)	/* ~diagnostic LEDs */

#पूर्ण_अगर /* __ASM_MIPS_DEC_KN02BA_H */
