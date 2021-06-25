<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/dec/kn02ca.h
 *
 *	Personal DECstation 5000/xx (Maxine or KN02-CA) definitions.
 *
 *	Copyright (C) 2002, 2003  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MIPS_DEC_KN02CA_H
#घोषणा __ASM_MIPS_DEC_KN02CA_H

#समावेश <यंत्र/dec/kn02xa.h>		/* For common definitions. */

/*
 * CPU पूर्णांकerrupt bits.
 */
#घोषणा KN02CA_CPU_INR_HALT	6	/* HALT from ACCESS.Bus */
#घोषणा KN02CA_CPU_INR_CASCADE	5	/* I/O ASIC cascade */
#घोषणा KN02CA_CPU_INR_BUS	4	/* memory, I/O bus पढ़ो/ग_लिखो errors */
#घोषणा KN02CA_CPU_INR_RTC	3	/* DS1287 RTC */
#घोषणा KN02CA_CPU_INR_TIMER	2	/* ARC periodic समयr */

/*
 * I/O ASIC पूर्णांकerrupt bits.  Star marks denote non-IRQ status bits.
 */
#घोषणा KN02CA_IO_INR_FLOPPY	15	/* 82077 FDC */
#घोषणा KN02CA_IO_INR_NVRAM	14	/* (*) NVRAM clear jumper */
#घोषणा KN02CA_IO_INR_POWERON	13	/* (*) ACCESS.Bus/घातer-on reset */
#घोषणा KN02CA_IO_INR_TC0	12	/* TURBOchannel slot #0 */
#घोषणा KN02CA_IO_INR_TIMER	12	/* ARC periodic समयr (?) */
#घोषणा KN02CA_IO_INR_ISDN	11	/* Am79C30A ISDN */
#घोषणा KN02CA_IO_INR_NRMOD	10	/* (*) NRMOD manufacturing jumper */
#घोषणा KN02CA_IO_INR_ASC	9	/* ASC (NCR53C94) SCSI */
#घोषणा KN02CA_IO_INR_LANCE	8	/* LANCE (Am7990) Ethernet */
#घोषणा KN02CA_IO_INR_HDFLOPPY	7	/* (*) HD (1.44MB) floppy status */
#घोषणा KN02CA_IO_INR_SCC0	6	/* SCC (Z85C30) serial #0 */
#घोषणा KN02CA_IO_INR_TC1	5	/* TURBOchannel slot #1 */
#घोषणा KN02CA_IO_INR_XDFLOPPY	4	/* (*) XD (2.88MB) floppy status */
#घोषणा KN02CA_IO_INR_VIDEO	3	/* framebuffer */
#घोषणा KN02CA_IO_INR_XVIDEO	2	/* ~framebuffer */
#घोषणा KN02CA_IO_INR_AB_XMIT	1	/* ACCESS.bus transmit */
#घोषणा KN02CA_IO_INR_AB_RECV	0	/* ACCESS.bus receive */


/*
 * Memory Error Register bits.
 */
#घोषणा KN02CA_MER_INTR		(1<<27)		/* ARC IRQ status & ack */

/*
 * Memory Size Register bits.
 */
#घोषणा KN02CA_MSR_INTREN	(1<<26)		/* ARC periodic IRQ enable */
#घोषणा KN02CA_MSR_MS10EN	(1<<25)		/* 10/1ms IRQ period select */
#घोषणा KN02CA_MSR_PFORCE	(0xf<<21)	/* byte lane error क्रमce */
#घोषणा KN02CA_MSR_MABEN	(1<<20)		/* A side VFB address enable */
#घोषणा KN02CA_MSR_LASTBANK	(0x7<<17)	/* onboard RAM bank # */

/*
 * I/O ASIC System Support Register bits.
 */
#घोषणा KN03CA_IO_SSR_RES_14	(1<<14)		/* unused */
#घोषणा KN03CA_IO_SSR_RES_13	(1<<13)		/* unused */
#घोषणा KN03CA_IO_SSR_ISDN_RST	(1<<12)		/* ~ISDN (Am79C30A) reset */

#घोषणा KN03CA_IO_SSR_FLOPPY_RST (1<<7)		/* ~FDC (82077) reset */
#घोषणा KN03CA_IO_SSR_VIDEO_RST	(1<<6)		/* ~framebuffer reset */
#घोषणा KN03CA_IO_SSR_AB_RST	(1<<5)		/* ACCESS.bus reset */
#घोषणा KN03CA_IO_SSR_RES_4	(1<<4)		/* unused */
#घोषणा KN03CA_IO_SSR_RES_3	(1<<4)		/* unused */
#घोषणा KN03CA_IO_SSR_RES_2	(1<<2)		/* unused */
#घोषणा KN03CA_IO_SSR_RES_1	(1<<1)		/* unused */
#घोषणा KN03CA_IO_SSR_LED	(1<<0)		/* घातer LED */

#पूर्ण_अगर /* __ASM_MIPS_DEC_KN02CA_H */
