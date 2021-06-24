<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_FDREG_H
#घोषणा _LINUX_FDREG_H
/*
 * This file contains some defines क्रम the floppy disk controller.
 * Various sources. Mostly "IBM Microcomputers: A Programmers
 * Handbook", Sanches and Canton.
 */

/* 82077's auxiliary status रेजिस्टरs A & B (R) */
#घोषणा FD_SRA		0
#घोषणा FD_SRB		1

/* Digital Output Register */
#घोषणा FD_DOR		2

/* 82077's tape drive रेजिस्टर (R/W) */
#घोषणा FD_TDR		3

/* 82077's data rate select रेजिस्टर (W) */
#घोषणा FD_DSR		4

/* Fd controller regs. S&C, about page 340 */
#घोषणा FD_STATUS	4
#घोषणा FD_DATA		5

/* Digital Input Register (पढ़ो) */
#घोषणा FD_सूची		7

/* Diskette Control Register (ग_लिखो)*/
#घोषणा FD_DCR		7

/* Bits of मुख्य status रेजिस्टर */
#घोषणा STATUS_BUSYMASK	0x0F		/* drive busy mask */
#घोषणा STATUS_BUSY	0x10		/* FDC busy */
#घोषणा STATUS_DMA	0x20		/* 0- DMA mode */
#घोषणा STATUS_सूची	0x40		/* 0- cpu->fdc */
#घोषणा STATUS_READY	0x80		/* Data reg पढ़ोy */

/* Bits of FD_ST0 */
#घोषणा ST0_DS		0x03		/* drive select mask */
#घोषणा ST0_HA		0x04		/* Head (Address) */
#घोषणा ST0_NR		0x08		/* Not Ready */
#घोषणा ST0_ECE		0x10		/* Equipment check error */
#घोषणा ST0_SE		0x20		/* Seek end */
#घोषणा ST0_INTR	0xC0		/* Interrupt code mask */

/* Bits of FD_ST1 */
#घोषणा ST1_MAM		0x01		/* Missing Address Mark */
#घोषणा ST1_WP		0x02		/* Write Protect */
#घोषणा ST1_ND		0x04		/* No Data - unपढ़ोable */
#घोषणा ST1_OR		0x10		/* OverRun */
#घोषणा ST1_CRC		0x20		/* CRC error in data or addr */
#घोषणा ST1_EOC		0x80		/* End Of Cylinder */

/* Bits of FD_ST2 */
#घोषणा ST2_MAM		0x01		/* Missing Address Mark (again) */
#घोषणा ST2_BC		0x02		/* Bad Cylinder */
#घोषणा ST2_SNS		0x04		/* Scan Not Satisfied */
#घोषणा ST2_SEH		0x08		/* Scan Equal Hit */
#घोषणा ST2_WC		0x10		/* Wrong Cylinder */
#घोषणा ST2_CRC		0x20		/* CRC error in data field */
#घोषणा ST2_CM		0x40		/* Control Mark = deleted */

/* Bits of FD_ST3 */
#घोषणा ST3_HA		0x04		/* Head (Address) */
#घोषणा ST3_DS		0x08		/* drive is द्विगुन-sided */
#घोषणा ST3_TZ		0x10		/* Track Zero संकेत (1=track 0) */
#घोषणा ST3_RY		0x20		/* drive is पढ़ोy */
#घोषणा ST3_WP		0x40		/* Write Protect */
#घोषणा ST3_FT		0x80		/* Drive Fault */

/* Values क्रम FD_COMMAND */
#घोषणा FD_RECALIBRATE		0x07	/* move to track 0 */
#घोषणा FD_SEEK			0x0F	/* seek track */
#घोषणा FD_READ			0xE6	/* पढ़ो with MT, MFM, SKip deleted */
#घोषणा FD_WRITE		0xC5	/* ग_लिखो with MT, MFM */
#घोषणा FD_SENSEI		0x08	/* Sense Interrupt Status */
#घोषणा FD_SPECIFY		0x03	/* specअगरy HUT etc */
#घोषणा FD_FORMAT		0x4D	/* क्रमmat one track */
#घोषणा FD_VERSION		0x10	/* get version code */
#घोषणा FD_CONFIGURE		0x13	/* configure FIFO operation */
#घोषणा FD_PERPENDICULAR	0x12	/* perpendicular r/w mode */
#घोषणा FD_GETSTATUS		0x04	/* पढ़ो ST3 */
#घोषणा FD_DUMPREGS		0x0E	/* dump the contents of the fdc regs */
#घोषणा FD_READID		0xEA	/* prपूर्णांकs the header of a sector */
#घोषणा FD_UNLOCK		0x14	/* Fअगरo config unlock */
#घोषणा FD_LOCK			0x94	/* Fअगरo config lock */
#घोषणा FD_RSEEK_OUT		0x8f	/* seek out (i.e. to lower tracks) */
#घोषणा FD_RSEEK_IN		0xcf	/* seek in (i.e. to higher tracks) */

/* the following commands are new in the 82078. They are not used in the
 * floppy driver, except the first three. These commands may be useful क्रम apps
 * which use the FDRAWCMD पूर्णांकerface. For करोc, get the 82078 spec sheets at
 * http://www.पूर्णांकel.com/design/archives/periphrl/करोcs/29046803.hपंचांग */

#घोषणा FD_PARTID		0x18	/* part id ("extended" version cmd) */
#घोषणा FD_SAVE			0x2e	/* save fdc regs क्रम later restore */
#घोषणा FD_DRIVESPEC		0x8e	/* drive specअगरication: Access to the
					 * 2 Mbps data transfer rate क्रम tape
					 * drives */

#घोषणा FD_RESTORE		0x4e    /* later restore */
#घोषणा FD_POWERDOWN		0x27	/* configure FDC's घातersave features */
#घोषणा FD_FORMAT_N_WRITE	0xef    /* क्रमmat and ग_लिखो in one go. */
#घोषणा FD_OPTION		0x33	/* ISO क्रमmat (which is a clean way to
					 * pack more sectors on a track) */

/* DMA commands */
#घोषणा DMA_READ	0x46
#घोषणा DMA_WRITE	0x4A

/* FDC version वापस types */
#घोषणा FDC_NONE	0x00
#घोषणा FDC_UNKNOWN	0x10	/* DO NOT USE THIS TYPE EXCEPT IF IDENTIFICATION
				   FAILS EARLY */
#घोषणा FDC_8272A	0x20	/* Intel 8272a, NEC 765 */
#घोषणा FDC_765ED	0x30	/* Non-Intel 1MB-compatible FDC, can't detect */
#घोषणा FDC_82072	0x40	/* Intel 82072; 8272a + FIFO + DUMPREGS */
#घोषणा FDC_82072A	0x45	/* 82072A (on Sparcs) */
#घोषणा FDC_82077_ORIG	0x51	/* Original version of 82077AA, sans LOCK */
#घोषणा FDC_82077	0x52	/* 82077AA-1 */
#घोषणा FDC_82078_UNKN	0x5f	/* Unknown 82078 variant */
#घोषणा FDC_82078	0x60	/* 44pin 82078 or 64pin 82078SL */
#घोषणा FDC_82078_1	0x61	/* 82078-1 (2Mbps fdc) */
#घोषणा FDC_S82078B	0x62	/* S82078B (first seen on Adaptec AVA-2825 VLB
				 * SCSI/EIDE/Floppy controller) */
#घोषणा FDC_87306	0x63	/* National Semiconductor PC 87306 */

/*
 * Beware: the fdc type list is roughly sorted by increasing features.
 * Presence of features is tested by comparing the FDC version id with the
 * "oldest" version that has the needed feature.
 * If during FDC detection, an obscure test fails late in the sequence, करोn't
 * assign FDC_UNKNOWN. Else the FDC will be treated as a dumb 8272a, or worse.
 * This is especially true अगर the tests are unneeded.
 */

#घोषणा FD_RESET_DELAY 20
#पूर्ण_अगर
